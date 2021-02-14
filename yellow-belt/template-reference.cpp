#include <iostream>
#include <map>
#include <exception>

template <typename Key, typename Value> Value& GetRefStrict(std::map<Key, Value>& m, Key k);

template <typename Key, typename Value>
Value& GetRefStrict(std::map<Key, Value>& m, Key k) {
  if (m.count(k)) {
    return m[k];
  } else {
    throw std::runtime_error("");
  }
}

int main(void) {

  using namespace std;
  
  map<int, string> m = {{0, "value"}};
  string& item = GetRefStrict(m, 0);
  item = "newvalue";
  cout << m[0] << endl; // выведет newvalue
 
  return 0;
}
