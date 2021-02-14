#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main(void) {

  std::vector<std::string> text;
  std::string input;
  
  while (std::cin >> input) {
    text.push_back(input);
  }

  sort(begin(text), end(text));

  std::cout << text[0];
  
  return 0;
}
