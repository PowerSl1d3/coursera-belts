#include <iostream>
#include <string>
#include <fstream>

int main(void) {

  const std::string path_i = "input.txt";
  std::ifstream input(path_i);

  if (input.is_open()) {
    std::string path_o = "output.txt";
    std::ofstream output(path_o);
    std::string line;
    while (getline(input, line)) {
      output << line << std::endl;
    }
  }
  
  return 0;  
}
