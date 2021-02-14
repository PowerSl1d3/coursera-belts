#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  if (range_end - range_begin < 2) {
    return;
  }
  std::vector<typename RandomIt::value_type> elements(range_begin, range_end);
  auto border = begin(elements) + (end(elements) - begin(elements)) / 2;
  MergeSort(begin(elements), border);
  MergeSort(border, end(elements));
  std::merge(begin(elements), border, border, end(elements), range_begin);
}

int main(void) {
  using namespace std;

  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  
  return 0;
}
