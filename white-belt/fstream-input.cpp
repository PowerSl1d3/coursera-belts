#include <iostream>
#include <fstream>
#include <string>

int main(void) {
  const std::string path = "input.txt";
  std::ifstream input(path);

  if (input.is_open()) {
    std::string line;
    while (getline(input, line)) {
      std::cout << line << std::endl;
    }
  }

  return 0;
  
}
