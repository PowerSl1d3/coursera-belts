#include <iostream>
#include <map>

std::map<char, int> BuildCharCounters(const std::string& s) {

  std::map<char,int> m;
  
  for (char c : s) {
    m[c]++;
  }

  return m;
}

int main(void) {

  int n;
  std::cin >> n;

  for (int i = 0; i < n; i++) {

    std::string first, second;
    std::cin >> first >> second;
    std::map<char, int> first_word_map = BuildCharCounters(first);
    std::map<char, int> second_word_map = BuildCharCounters(second);

    if (first_word_map == second_word_map) {
      std::cout << "YES" << std::endl;
    } else {
      std::cout << "NO" << std::endl;
    }

  }
  
  return 0;
}
