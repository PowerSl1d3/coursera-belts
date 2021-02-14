#include <iostream>
#include <string>
#include <set>
#include <map>

int main(void) {

  std::set<std::set<std::string>> synonyms;
  std::map<std::string, int> words;
  int n;
  std::cin >> n;
  std::string command, word1, word2;

  for (int i = 0; i < n; i++) {
    std::cin >> command;
    if (command == "ADD") {
      std::set<std::string> two_synonyms;
      std::cin >> word1 >> word2;
      two_synonyms.insert(word1);
      two_synonyms.insert(word2);
      if (synonyms.count(two_synonyms) == 0) {
	words[word1]++;
	words[word2]++;
	synonyms.insert(two_synonyms);
      }
    } else if (command == "COUNT") {
      std::cin >> word1;
      std::cout << words[word1] << std::endl;
    } else if (command == "CHECK") {
      std::set<std::string> two_synonyms;
      std::cin >> word1 >> word2;
      two_synonyms.insert(word1);
      two_synonyms.insert(word2);
      if (synonyms.count(two_synonyms) == 1) {
	std::cout << "YES" << std::endl;
      } else {
	std::cout << "NO" << std::endl;
      }
    }
  }
  
  return 0;
}
