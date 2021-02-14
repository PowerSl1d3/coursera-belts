#include <iostream>
#include <vector>

std::vector<int> Reversed(const std::vector<int>& v) {

  std::vector l = v;
  for (int i = 0, j = l.size() - 1; i < j; i++, j--) {
    std::swap(l[i], l[j]);
  }
  return l;
  
}

int main(void) {

  return 0;
}
