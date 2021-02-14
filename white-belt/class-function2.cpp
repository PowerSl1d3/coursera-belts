#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class FunctionParts {
public:
  FunctionParts(const char& c, const double& new_value) {
    operation = c;
    value = new_value;
  }
  double Apply(double source_value) const {
    if (operation == '+') {
      return source_value + value;
    } else if (operation == '-')  {
      return source_value - value;
    } else if (operation == '*') {
      return source_value * value;
    } else {
      return source_value / value;
    }
  }
  void Invert(void) {
    if (operation == '+') {
      operation = '-';
    } else if (operation == '-') {
      operation = '+';
    } else if (operation == '*') {
      operation = '/';
    } else {
      operation = '*';
    }
  }
private:
  char operation;
  double value;
};

class Function {
public:
  void AddPart(const char& c, const double& source) {
    parts.push_back({c, source});
  }
  double Apply(double value) const {
    for (const FunctionParts& f : parts) {
      value = f.Apply(value);
    }
    return value;
  }
  void Invert(void) {
    for (FunctionParts& f : parts) {
      f.Invert();
    }
    reverse(begin(parts), end(parts));
  }
private:
  std::vector<FunctionParts> parts;
};
