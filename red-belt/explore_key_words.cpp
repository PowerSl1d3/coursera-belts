#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <future>
#include <vector>
#include <sstream>
#include <utility>
using namespace std;

template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end)
    : first(begin)
    , last(end)
    , size_(distance(first, last))
  {
  }

  Iterator begin() const {
    return first;
  }

  Iterator end() const {
    return last;
  }

  size_t size() const {
    return size_;
  }

private:
  Iterator first, last;
  size_t size_;
};

template <typename Iterator>
class Paginator {
private:
  vector<IteratorRange<Iterator>> pages;

public:
  Paginator(Iterator begin, Iterator end, size_t page_size) {
    for (size_t left = distance(begin, end); left > 0; ) {
      size_t current_page_size = min(page_size, left);
      Iterator current_page_end = next(begin, current_page_size);
      pages.push_back({begin, current_page_end});

      left -= current_page_size;
      begin = current_page_end;
    }
  }

  auto begin() const {
    return pages.begin();
  }

  auto end() const {
    return pages.end();
  }

  size_t size() const {
    return pages.size();
  }
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
  return Paginator(begin(c), end(c), page_size);
}

struct Stats {
  map<string, int> word_frequences;

  Stats() = default;

  Stats(std::map<std::string, int>&& other)
    : word_frequences(other)
  {}

  void operator += (const Stats& other) {
    for (auto it = other.word_frequences.begin(); it != other.word_frequences.end(); std::next(it)) {
      word_frequences[it->first] += it->second;
    }
  }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
  std::map<std::string, int> words_count;
  std::string word;
  std::istringstream stream(line);
  while (stream >> word) {
    auto it = key_words.find(word);
    if (it != key_words.end()) {
      words_count[*it]++;
    }
  }
  
  return {std::move(words_count)};
}

Stats ExploreKeyWordsSingleThread(
  const set<string>& key_words, istream& input
) {
  Stats result;
  for (string line; getline(input, line); ) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

template <typename T>
Stats ExploreKeyWordsMultyThread(
				 const set<string>& key_words, T& input
) {
  Stats result;
  for (const std::string& line : input) {
    //std::cout << line << std::endl;
    result += ExploreLine(key_words, line);
  }
  return result;
}

int line = 0;

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
  Stats stats;
  std::vector<future<Stats>> threads;
  std::vector<std::string> all_lines;
  std::string line;

  while(std::getline(input, line)) {
    all_lines.push_back(std::move(line));
  }

  for(auto& page : Paginate(all_lines, 2000)) {
    threads.push_back(std::async([&key_words, page] {
				   return ExploreKeyWordsMultyThread(key_words, page);
				 })
		      );
  }

  for (auto& th : threads) {
    stats += th.get();
  }

  return stats;
  
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWordsSingleThread(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
}
