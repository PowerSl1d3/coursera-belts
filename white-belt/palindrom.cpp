#include <iostream>
#include <string>

bool IsPalindrom (std::string);

int main(void) {

  std::string line;

  std::cin >> line;

  std::cout << IsPalindrom(line);
  
  return 0;
}

bool IsPalindrom(std::string s) {

  std::string t = s;
  
  for (int i = 0, j = s.size() - 1; i < j; i++, j--) {
    std::swap(s[i], s[j]);
  }

  if (s == t) {
    return true;
  } else {
    return false;
  }
}
