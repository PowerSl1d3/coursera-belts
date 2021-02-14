#include <iostream>
#include <set>

std::set<int>::const_iterator FindNearestElement(const std::set<int>& numbers, int border) {
  if (numbers.empty()) {
    return numbers.end();
  }
  
  auto it = numbers.lower_bound(border);

  if (it != numbers.end()) {
    if (it == prev(numbers.end())) {
      auto it2 = prev(it);
      return abs(*it - border) < abs(*it2 - border) ? it : it2;
    } else if (it == numbers.begin()) {
      auto it2 = next(it);
      return abs(*it - border) < abs(*it2 - border) ? it : it2;
    } else {
      auto it2 = prev(it);
      return abs(*it - border) < abs(*it2 - border) ? it : it2;
    }
  } else {
    return prev(it);
  }
  
}

int main(void) {
  using namespace std;

  set<int> numbers = {1, 4, 6};
  cout <<
    *FindNearestElement(numbers, 0) << " " <<
    *FindNearestElement(numbers, 3) << " " <<
    *FindNearestElement(numbers, 5) << " " <<
    *FindNearestElement(numbers, 6) << " " <<
    *FindNearestElement(numbers, 100) << endl;
      
  set<int> empty_set;
  
  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
  return 0;
}
