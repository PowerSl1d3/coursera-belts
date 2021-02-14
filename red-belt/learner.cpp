#include <algorithm>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Learner {
 private:
  set<string> dict;

 public:
  int Learn(const vector<string>& words) {
    int newWords = 0;
    for (const auto& word : words) {
      if (dict.count(word) == 0) {
        ++newWords;
        dict.insert(word);
      }
    }
    return newWords;
  }

  vector<string> KnownWords() {
    vector<string> known_word(dict.size());
    int i = 0;
    for (const auto& word : dict) {
      known_word[i++] = word;
    }
    return known_word;
  }
};
