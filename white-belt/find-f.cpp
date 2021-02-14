#include <iostream>
#include <string>

int main(void) {

  std::string line;

  std::cin >> line;

  int count = 0;

  for (int i = 0; i < line.size(); i++) {
    if (line[i] == 'f') {
      count++;
    }

    if (count == 2) {
      std::cout << i;
      break;
    }
  }

  if (count == 1) {
    std::cout << -1;
  } else if (count == 0) {
    std::cout << -2;
  }
  
  return 0;
}
