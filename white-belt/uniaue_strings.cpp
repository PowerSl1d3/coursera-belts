#include <iostream>
#include <string>
#include <set>

int main(void) {

  int n;
  std::string input;
  std::set<std::string> words;
  std::cin >> n;

  for (int i = 0; i < n; i++) {
    std::cin >> input;
    words.insert(input);
  }

  std::cout << words.size();
  
  return 0;
}
