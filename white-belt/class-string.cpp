#include <iostream>
#include <string>
#include <algorithm>

class ReversibleString {
public:
  ReversibleString () {}
  ReversibleString (const std::string& t) {
    s = t;
  }
  std::string ToString() const {
    return s;
  }
  void Reverse() {
    return reverse(begin(s), end(s));
  }
private:
  std::string s;
};

int main(void) {
  using namespace std;
  ReversibleString s("live");
  s.Reverse();
  cout << s.ToString() << endl;
  
  s.Reverse();
  const ReversibleString& s_ref = s;
  string tmp = s_ref.ToString();
  cout << tmp << endl;
  
  ReversibleString empty;
  cout << '"' << empty.ToString() << '"' << endl;
  
  return 0;
}
