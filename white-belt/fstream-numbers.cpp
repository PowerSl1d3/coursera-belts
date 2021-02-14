#include <fstream>
#include <string>
#include <iomanip>
#include <iostream>

int main(void) {

  std::ifstream input("input.txt");
  double value;

  std::cout << std::fixed << std::setprecision(3);

  if (input.is_open()) {
    while (input >> value) {
      std::cout << value << std::endl;
    }
  }

  return 0;
}
