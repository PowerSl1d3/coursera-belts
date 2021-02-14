#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;


struct Email {
    string from;
    string to;
    string body;
};

std::istream& operator>> (std::istream& is, Email& email) {
    std::string from, to, body;

    std::getline(is, from);
    std::getline(is, to);
    std::getline(is, body);

    email = Email{std::move(from), std::move(to), std::move(body)};

    return is;
}

std::ostream& operator<<(std::ostream& os, const Email& email)
{
    os << email.from << '\n';
    os << email.to << '\n';
    os << email.body << '\n';

    return os;
}

class Worker {
public:
    virtual ~Worker() = default;
    virtual void Process(unique_ptr<Email> email) = 0;
    virtual void Run() {
        // только первому worker-у в пайплайне нужно это имплементировать
        throw logic_error("Unimplemented");
    }

protected:
    // реализации должны вызывать PassOn, чтобы передать объект дальше
    // по цепочке обработчиков
    void PassOn(unique_ptr<Email> email) const {
        if (next_) {
            next_->Process(std::move(email));
        }
    }

public:
    void SetNext(unique_ptr<Worker> next) {
        if (!next_) {
            next_ = std::move(next);
        } else {
            next_->SetNext(std::move(next));
        }
    }
private:
    std::unique_ptr<Worker> next_ = nullptr;
};


class Reader : public Worker {
public:
    explicit Reader(std::istream& input)
    {
        Email email;
        while (input >> email)
        {
            emails_.emplace_back(std::make_unique<Email>(std::move(email)));
        }
    }

    void Run() override
    {
        for (std::unique_ptr<Email>& email : emails_)
        {
            PassOn(std::move(email));
        }
    }

    void Process(std::unique_ptr<Email> email) override
    {
        Run();
    }

private:
    std::vector<std::unique_ptr<Email>> emails_;
};


class Filter : public Worker {
public:
    using Function = std::function<bool(const Email&)>;

    explicit Filter(const Function& function) : function_(function) {}

    void Process(std::unique_ptr<Email> email) override
    {
        if (function_(*email))
            PassOn(std::move(email));
    }

private:
    const Function function_;
};


class Copier : public Worker {
public:
    explicit Copier(const std::string& recipient) : recipient_(recipient) {}

    void Process(std::unique_ptr<Email> email) override
    {
        std::unique_ptr<Email> new_email = nullptr;
        if (recipient_ != email->to)
        {
            new_email = std::make_unique<Email>(Email{email->from, recipient_, email->body});
        }

        PassOn(std::move(email));

        if (new_email)
            PassOn(std::move(new_email));
    }

private:
    const std::string recipient_;
};


class Sender : public Worker {
public:
    explicit Sender(std::ostream& output) : output_(output) {}

    void Process(std::unique_ptr<Email> email) override
    {
        output_ << *email;
        PassOn(std::move(email));
    }

private:
    std::ostream& output_;
};


// реализуйте класс
class PipelineBuilder {
public:
    // добавляет в качестве первого обработчика Reader
    explicit PipelineBuilder(istream& in) {
        head_ = std::make_unique<Reader>(in);
    }

    // добавляет новый обработчик Filter
    PipelineBuilder& FilterBy(Filter::Function filter) {
        head_->SetNext(std::make_unique<Filter>(std::move(filter)));

        return *this;
    }

    // добавляет новый обработчик Copier
    PipelineBuilder& CopyTo(string recipient) {
        head_->SetNext(std::make_unique<Copier>(std::move(recipient)));

        return *this;
    }

    // добавляет новый обработчик Sender
    PipelineBuilder& Send(ostream& out) {
        head_->SetNext(std::make_unique<Sender>(out));

        return *this;
    }

    // возвращает готовую цепочку обработчиков
    unique_ptr<Worker> Build() {
        return std::move(head_);
    }

private:
    std::unique_ptr<Worker> head_;
};


void TestSanity() {
    string input = (
            "erich@example.com\n"
            "richard@example.com\n"
            "Hello there\n"

            "erich@example.com\n"
            "ralph@example.com\n"
            "Are you sure you pressed the right button?\n"

            "ralph@example.com\n"
            "erich@example.com\n"
            "I do not make mistakes of that kind\n"
    );
    istringstream inStream(input);
    ostringstream outStream;

    PipelineBuilder builder(inStream);
    builder.FilterBy([](const Email& email) {
        return email.from == "erich@example.com";
    });
    builder.CopyTo("richard@example.com");
    builder.Send(outStream);
    auto pipeline = builder.Build();

    pipeline->Run();

    string expectedOutput = (
            "erich@example.com\n"
            "richard@example.com\n"
            "Hello there\n"

            "erich@example.com\n"
            "ralph@example.com\n"
            "Are you sure you pressed the right button?\n"

            "erich@example.com\n"
            "richard@example.com\n"
            "Are you sure you pressed the right button?\n"
    );

    ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSanity);
    return 0;
}

