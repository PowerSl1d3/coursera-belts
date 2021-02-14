#include <iostream>

void UpdateIfGreater(int first, int& second) {

  if (first > second) {
    second = first;
  }
  
}

int main(void) {

  int a, b;
  
  std::cin >> a >> b;

  UpdateIfGreater(a, b);

  std::cout << a << ' ' << b << std::endl;
  
  return 0;
}
