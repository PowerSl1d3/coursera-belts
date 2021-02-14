#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int main(void) {

  int N;
  std::cin >> N;
  std::vector<int> array(N);

  for (int& i : array) {
    std::cin >> i;
  }

  sort(begin(array), end(array), [](int i, int j) {
					 return abs(i) < abs(j);
				 });

  for (const int& i : array) {
    std::cout << i << ' ';
  }
  
  return 0;
}
