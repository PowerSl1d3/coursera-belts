#include <iostream>

int main(void) {

  int A, B;

  std::cin >> A >> B;

  int mod;
  
  if (A >= B) {
    do {

      mod = A % B;
      if (mod == 0) {
	std::cout << B;
	break;
      }
      A = B;
      B = mod;
      
    } while (mod != 0);
    
  } else {
    do {
      
      mod = B % A;
      if (mod == 0) {
	std::cout << A;
	break;
      }
      B = A;
      A = mod;
      
    } while (mod != 0);
  }
  
  return 0;
}
