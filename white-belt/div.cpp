#include <iostream>

int main(void) {

  int A, B;

  std::cin >> A >> B;

  if (B == 0) {
    
    std::cout << "Impossible";

  } else {
    
    std::cout << A / B;
    
  }

  return 0;
  
}
