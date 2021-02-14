#include <iostream>
#include <vector>

int main(void) {

  int N;
  std::vector<int> bitset;

  std::cin >> N;

  if (N == 0) {
    std::cout << 0;
  }

  while ( N > 0 ) {

    bitset.push_back(N % 2);
    N /= 2;
    
  }

  for(int i = bitset.size() - 1; i >= 0; i--) {
    std::cout << bitset[i];
  }
  
  return 0;
}
