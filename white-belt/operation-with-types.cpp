#include <iostream>
#include <string>

int main(void) {

  int x = 4;
  int y = 5;

  std::cout << (x + y) * (x - y) << std::endl;

  if (x ==y) {
    std::cout << "equal" << std::endl;
  } else {
    std::cout << "not equal" << std::endl;
  }

  std::string x1 = "abc";
  std::string y2 = "def";

  if (x1 < y2) {
    std::cout << "x1 < y2" << std::endl;
  } else {
    std::cout << "x1 >= y2" << std::endl;
  }
  
  return 0;
}
