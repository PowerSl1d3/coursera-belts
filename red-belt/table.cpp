#include <iostream>
#include <vector>
#include <utility>
#include "test_runner.h"

template <typename T>
class Table {
private:
  std::vector<std::vector<T>> table;
public:
  Table(size_t height, size_t width) {
    if (height == 0 || width == 0) {
      return;
    }
    table.resize(height, std::vector<T>(width));
  }
  const std::vector<T>& operator[](const int& index) const {
    return table.at(index);
  }
  std::vector<T>& operator[](const int& index) {
    return table.at(index);
  }
  void Resize(size_t new_height, size_t new_width) {
    if (new_height == 0 || new_width == 0) {
      table.resize(0, std::vector<T>(0));
      return;
    }
    table.resize(new_height);
    for (auto& i : table) {
      i.resize(new_width);
    }
  }
  std::pair<size_t, size_t> Size(void) const {
    if (table.size() == 0 || table.at(0).size() == 0) {
      return std::make_pair(0, 0);
    }
    return std::make_pair(table.size(), table.at(0).size());
  }
};

/*template <typename T, typename G>
std::ostream& operator<<(std::ostream& os, const std::pair<T, G>& p) {
  os << "<" << p.first << ", " << p.second << ">";
  return os;
}

void TestTable(void) {
  Table<int> t(5, 5);
  std::pair<size_t, size_t> p(5, 5);
  ASSERT_EQUAL(t.Size(), p);
  t.Resize(5, 6);
  p.second = 6;
  ASSERT_EQUAL(t.Size(), p);
  t.Resize(0, 5);
  p.first = p.second = 0;
  ASSERT_EQUAL(t.Size(), p);
}

int main(void) {
  TestRunner tr;

  RUN_TEST(tr, TestTable);
}
*/
