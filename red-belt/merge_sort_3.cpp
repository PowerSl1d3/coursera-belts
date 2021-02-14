#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <iterator>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  if (range_end - range_begin < 2) {
    return;
  }
  std::vector<typename RandomIt::value_type> tmp(std::make_move_iterator(range_begin), std::make_move_iterator(range_end));
  auto border1 = tmp.begin() + (tmp.end() - tmp.begin()) / 3;
  auto border2 = tmp.begin() + 2 * (tmp.end() - tmp.begin()) / 3;
  MergeSort(tmp.begin(), border1);
  MergeSort(border1, border2);
  MergeSort(border2, tmp.end());
  std::vector<typename RandomIt::value_type> interim_result;
  std::merge(std::make_move_iterator(tmp.begin()), std::make_move_iterator(border1), std::make_move_iterator(border1), std::make_move_iterator(border2), std::back_inserter(interim_result));
  std::merge(std::make_move_iterator(interim_result.begin()), std::make_move_iterator(interim_result.end()), std::make_move_iterator(border2), std::make_move_iterator(tmp.end()), range_begin);
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
