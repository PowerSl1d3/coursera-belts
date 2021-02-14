#include <iostream>

int Factorial(int n);

int main(void) {

  int n;

  std::cin >> n;

  if (n < 0) {
    std::cout << 1;
  } else {
    std::cout << Factorial(n);
  }
  
  return 0;
}

int Factorial(int n) {

  if (n > 0)
    return n *Factorial(n - 1);
  else
    return 1;
}
