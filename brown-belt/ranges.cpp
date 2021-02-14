#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

template <std::ranges::input_range Range>
void Print(const Range& range) {
  for (const auto& x : range) {
    std::cout << x << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::vector v = {4, 1, 7, 2, 3, 8};
  std::ranges::sort(v);
  std::ranges::reverse(v);
  Print(v);
  
  return 0;
}
