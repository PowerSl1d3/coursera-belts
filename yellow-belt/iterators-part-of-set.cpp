#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

template <typename T>
std::vector<T> FindGreaterElements(const std::set<T>& elements, const T& border) {
  auto it = find_if(begin(elements), end(elements), [border](T element) {
						      return element > border;
						    });
  std::vector<T> greatest_elements;
  for (; it != end(elements); it++) {
    greatest_elements.push_back(*it);
  }
    
  return greatest_elements;
}

int main() {

  using namespace std;
  
  for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
    cout << x << " ";
  }
  cout << endl;
  
  string to_find = "Python";
  cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
  return 0;
}
