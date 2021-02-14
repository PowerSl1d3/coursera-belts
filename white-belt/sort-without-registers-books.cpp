#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

int main(void) {
  
  int N;
  std::vector<std::string> words;
  std::string word;
  std::cin >> N;

  for (int i = 0; i < N; i++) {
    std::cin >> word;
    words.push_back(word);
  }

  sort(begin(words), end(words), [](std::string left, std::string right) {
				   for (char& c : left) {
				     c = tolower(c);
				   }
				   for (char& c: right) {
				     c = tolower(c);
				   }
				   return left < right;
					   });

  for (std::string& i : words) {
    std::cout << i << ' ';
  }
  
  return 0;
}
