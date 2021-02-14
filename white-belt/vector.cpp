#include <iostream>
#include <vector>
#include <string>

int main(void) {

  int n;
  std::cin >> n;

  std::vector<std::string> v(n);

  for (std::string& s : v) {
    std::cin >> s;
  }

  for (std::string s : v) {
    std::cout << s << ' ';
  }
  
  return 0;
}
