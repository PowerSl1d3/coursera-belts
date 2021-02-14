#include <iostream>
#include <cmath>

int main(void) {

  double a, b, c;

  std::cin >> a >> b >> c;

  if (a == 0 && b == 0) {

    return 0;
    
  }

  if (a == 0 && c == 0) {

    std::cout << 0;
    return 0;
    
  }

  if (b == 0 && c == 0) {

    std::cout << 0;
    return 0;
    
  }

  
  if (a == 0) {
    
    std::cout << (-c)/(double)b;

    return 0;
    
  }
  
  double D;

  if ((D = b * b - 4 * a * c) >= 0) {
    
    D = sqrt(D);
    
  } else {
    
    return 0;
    
  }
  
  if (abs(D) <= 0.00001) {

    std::cout << (-b) / (2 *(double)a);
    
  } else {

    std::cout << ((-b) + D) / (2 * a) << ' ' << ((-b) - D) / (2 * a); 
    
  }

  return 0;
}
