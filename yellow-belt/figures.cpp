#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <iomanip>
#include <cmath>

#define PI 3.14f

class Figure {
public:
  virtual std::string Name() = 0;
  virtual double Perimeter() = 0;
  virtual double Area() = 0;
};

class Rect : public Figure {
public:
  Rect(const std::string& name, const int& width, const int& height)
    : name_(name)
    , width_(width)
    , height_(height)
  {}
  std::string Name() override {
    return name_;
  }
  double Perimeter() override {
    return 2 * width_ + 2 * height_;
  }
  double Area() override {
    return static_cast<double>(width_ * height_);
  }
private:
  const std::string name_;
  const int width_;
  const int height_;
};

class Triangle : public Figure {
public:
  Triangle(const std::string& name, const int& a, const int& b, const int& c)
    : name_(name)
    , a_(a)
    , b_(b)
    , c_(c)
  {}
  std::string Name() override {
    return name_;
  }
  double Perimeter() override {
    return static_cast<double>(a_ + b_ + c_);
  }
  double Area() override {
    double p = static_cast<double>(a_ + b_ + c_) / 2;
    return sqrt(p * (p - a_) * (p - b_) * (p - c_));
  }
private:
  const std::string name_;
  const int a_;
  const int b_;
  const int c_;
};

class Circle : public Figure {
public:
  Circle(const std::string& name, const int& r)
    : name_(name)
    , r_(r)
  {}
  std::string Name() override {
    return name_;
  }
  double Perimeter() override {
    return static_cast<double>(static_cast<double>(r_) * 2 * PI);
  }
  double Area() override {
    return static_cast<double>(PI * static_cast<double>(r_) * r_);
  }
private:
  const std::string name_;
  const int r_;
};

std::shared_ptr<Figure> CreateFigure(std::istream& is) {
  std::string name;
  is >> name;
  if (name == "RECT") {
    int width, height;
    is >> width >> height;
    return std::make_shared<Rect>(name, width, height);
  } else if (name == "TRIANGLE") {
    int a, b, c;
    is >> a >> b >> c;
    return std::make_shared<Triangle>(name, a, b, c);
  } else if (name == "CIRCLE") {
    int r;
    is >> r;
    return std::make_shared<Circle>(name, r);
  }

  return {};
}

int main() {
  using namespace std;
  
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      // Пропускаем "лишние" ведущие пробелы.
      // Подробнее об std::ws можно узнать здесь:
      // https://en.cppreference.com/w/cpp/io/manip/ws
      is >> ws;
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
