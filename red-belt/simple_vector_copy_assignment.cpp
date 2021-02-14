#include "simple_vector.h"
#include "test_runner.h"

#include <numeric>
#include <vector>
#include <tuple>

using namespace std;

template <typename T>
void SimpleVector<T>::operator=(const SimpleVector<T>& other) {
  this->~SimpleVector();
  data = new T[other.capacity_];
  std::copy(other.begin(), other.end(), begin());
  size_ = other.size_;
  capacity_ = other.capacity_;
}

void TestCopyAssignment() {
  SimpleVector<int> numbers(10);
  iota(numbers.begin(), numbers.end(), 1);

  SimpleVector<int> dest;
  ASSERT_EQUAL(dest.Size(), 0u);

  dest = numbers;
  ASSERT_EQUAL(dest.Size(), numbers.Size());
  ASSERT(dest.Capacity() >= dest.Size());
  ASSERT(equal(dest.begin(), dest.end(), numbers.begin()));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCopyAssignment);
}
