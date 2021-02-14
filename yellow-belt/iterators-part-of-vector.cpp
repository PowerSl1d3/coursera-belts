#include <iostream>
#include <vector>
#include <algorithm>

void PrintVectorPart(const std::vector<int>& numbers) {
  auto it = find_if(begin(numbers), end(numbers), [](int i) { return i < 0; });
  while (it != begin(numbers)) {
    it--;
    std::cout << *it << " ";
  }
}

int main(void) {
  using namespace std;
  PrintVectorPart({6, 1, 8, -5, 4});
  cout << endl;
  PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
  cout << endl;
  PrintVectorPart({6, 1, 8, 5, 4});
  cout << endl;
  return 0;
}
