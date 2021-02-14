#include <iostream>
#include <string>
#include <vector>

int main(void) {

  int x = 4;

  std::string y = "hello";

  std::cout << x << ' ' << y << std::endl;

  int a, b;

  std::cin >> a >> b;

  std::cout << a + b <<std::endl;

  std::string name;

  std::cin >> name;

  std::cout << "Hello, " << name << "!" <<std::endl;
  
  return 0;
}
