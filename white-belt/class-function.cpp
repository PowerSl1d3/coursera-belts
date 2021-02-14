#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Image {
  double quality;
  double freshness;
  double rating;
};

struct Params {
  double a;
  double b;
  double c;
};

class FunctionParts {
public:
  FunctionParts(const char& c, const double& new_value) {
    operation = c;
    value = new_value;
  }
  double Apply(double source_value) const {
    if (operation == '+') {
      return source_value + value;
    } else {
      return source_value - value;
    }
  }
  void Invert(void) {
    if (operation == '+') {
      operation = '-';
    } else {
      operation = '+';
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

Function MakeWeightFunction(const Params& params,
			    const Image& image) {
  Function function;
  function.AddPart('-', image.freshness * params.a + params.b);
  function.AddPart('+', image.rating * params.c);
  return function;
}

double ComputeImageWeight(const Params& params, const Image& image) {
  Function function = MakeWeightFunction(params, image);
  return function.Apply(image.quality);
}

double ComputeQualityByWeight(const Params& params,
                              const Image& image,
                              double weight) {
  Function function = MakeWeightFunction(params, image);
  function.Invert();
  return function.Apply(weight);
}

int main() {
  Image image = {10, 2, 6};
  Params params = {4, 2, 6};
  cout << ComputeImageWeight(params, image) << endl;
  cout << ComputeQualityByWeight(params, image, 46) << endl;
  return 0;
}
