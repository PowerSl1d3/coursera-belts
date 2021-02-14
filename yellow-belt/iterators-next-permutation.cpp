#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <sstream>
#include <string>

template <typename Collection>
std::string Join(const Collection& c, const char& d) {
  std::stringstream ss;
  bool first = true;
  for (const auto& i : c) {
    if (!first) {
      ss << d;
    }
    first = false;
    ss << i;
  }

  return ss.str();
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
  return os << Join(vec, ' ');
}

void NumericPermutation(std::vector<int>& vec) {
  do {
    std::cout << vec << std::endl;
  } while (std::prev_permutation(begin(vec), end(vec)));
}

int main(void) {
  int N;
  std::cin >> N;
  std::vector<int> numbers(N);

  std::iota(begin(numbers), end(numbers), 1);
  std::sort(rbegin(numbers), rend(numbers));
  NumericPermutation(numbers);

  return 0;
}
