#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> PalindromFilter(std::vector<std::string> words, int minLength);

bool IsPalindrom (std::string);

int main(void) {

  std::string line;

  std::cin >> line;

  std::cout << IsPalindrom(line);
  
  return 0;
}

std::vector<std::string> PalindromFilter(std::vector<std::string> words, int minLength) {

  std::vector<std::string> pallindrom_array;

  for (auto w : words) {
    if (w.size() >= minLength && IsPalindrom(w)) {
      pallindrom_array.push_back(w);
    }
  }
  
  return pallindrom_array;
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
