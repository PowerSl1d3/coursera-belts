#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <utility>

template <typename Collection> std::string Join(const Collection& c, char d);

template <typename First, typename Second> std::ostream& operator<<(std::ostream& os, const std::pair<First, Second>& p);

template <typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec);

template <typename Key, typename Value> std::ostream& operator<<(std::ostream& os, const std::map<Key, Value> m);

template <typename T> T Sqr(T element);

template <typename T> std::vector<T> Sqr(std::vector<T> vec);

template <typename First, typename Second> std::pair<First, Second> Sqr(std::pair<First, Second> p);

template <typename Key, typename Value> std::map<Key, Value> Sqr(std::map<Key, Value> m);

template <typename Collection>
std::string Join(const Collection& c, const char& d) {
  std::stringstream ss;
  bool first = true;
  for (const auto& i : c) {
    if (!first) {
      ss << d;
    }
    first = false;
    ss << i;
  }

  return ss.str();
}

template <typename First, typename Second>
std::ostream& operator<<(std::ostream& os, const std::pair<First, Second>& p) {
  return os << '<' <<  p.first << ',' << p.second << '>';
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
  return os << '[' <<  Join(vec, ',') << ']';
}

template <typename Key, typename Value>
std::ostream& operator<<(std::ostream& os, const std::map<Key, Value> m) {
  return os << '{' << Join(m, ',') << '}';
}

template <typename T>
T Sqr(T element) {
  return element * element;
}

template <typename T>
std::vector<T> Sqr(std::vector<T> vec) {
  for (auto& i : vec) {
    i = Sqr(i);
  }

  return vec;
}

template <typename First, typename Second>
std::pair<First, Second> Sqr(std::pair<First, Second> p) {
  return {Sqr(p.first), Sqr(p.second)};
}

template <typename Key, typename Value>
std::map<Key, Value> Sqr(std::map<Key, Value> m) {
  for (auto& i : m) {
    i.second = Sqr(i.second);
  }

  return m;
}


int main(void) {

  using namespace std;
  
  vector<int> v = {1, 2, 3};
  cout << "vector:";
  for (int x : Sqr(v)) {
    cout << ' ' << x;
  }
  cout << endl;

  map<int, pair<int, int>> map_of_pairs = {
					   {4, {2, 2}},
					   {7, {4, 3}}
  };
  cout << "map of pairs:" << endl;
  for (const auto& x : Sqr(map_of_pairs)) {
    cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
  }
  
  return 0;
}
