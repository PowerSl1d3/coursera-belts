#include <iostream>
#include <vector>

void Reverse(std::vector<int>& v) {

  for (int i = 0, j = v.size() - 1; i < j; i++, j--) {
    std::swap(v[i], v[j]);
  }
  
}

int main(void) {
  return 0;
}
