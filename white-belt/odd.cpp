#include <iostream>

int main(void) {

  int A, B;

  std::cin >> A >> B;

  for (int i = A; i <= B; i++) {
    if (i % 2 == 0) {
      std::cout << i;
      if (i + 2 <= B)
	std::cout << ' ';
    }
  }
  
  return 0;
}
