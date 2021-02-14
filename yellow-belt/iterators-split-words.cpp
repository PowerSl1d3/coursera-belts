#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> SplitIntoWords(const std::string& s) {
  std::vector<std::string> words;
  auto it = begin(s);
  auto prev_it = begin(s);

  do {
    prev_it = it;
    it = find(it, end(s) , ' ');
    words.push_back({prev_it, it});
    if (it != end(s)) {
      it++;
    }
  } while (it != end(s));

  return words;
}

int main() {
  using namespace std;
  string s = "C";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;
  
  return 0;
}
