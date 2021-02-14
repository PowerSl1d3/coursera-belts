#include "test_runner.h"
#include <vector>
#include <future>
#include <cstdint>

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end)
    : first(begin)
    , last(end)
    , size_(distance(first, last))
  {
  }

  Iterator begin() const {
    return first;
  }

  Iterator end() const {
    return last;
  }

  size_t size() const {
    return size_;
  }

private:
  Iterator first, last;
  size_t size_;
};

template <typename Iterator>
class Paginator {
private:
  vector<IteratorRange<Iterator>> pages;

public:
  Paginator(Iterator begin, Iterator end, size_t page_size) {
    for (size_t left = distance(begin, end); left > 0; ) {
      size_t current_page_size = min(page_size, left);
      Iterator current_page_end = next(begin, current_page_size);
      pages.push_back({begin, current_page_end});

      left -= current_page_size;
      begin = current_page_end;
    }
  }

  auto begin() const {
    return pages.begin();
  }

  auto end() const {
    return pages.end();
  }

  size_t size() const {
    return pages.size();
  }
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
  return Paginator(begin(c), end(c), page_size);
}

template <typename T>
int64_t SimpleThreadSum(const T& matrix) {
  int64_t sum = 0;
  for (const auto& line : matrix) {
    for (const auto& element : line) {
      sum += element;
    }
  }
  return sum;
}

int64_t CalculateMatrixSum(const std::vector<std::vector<int>>& matrix) {
  std::vector<std::future<int64_t>> threads;
  int64_t sum = 0;

  for (auto& page : Paginate(matrix, 2000)) {
    threads.push_back(std::async([page] {
				  return SimpleThreadSum(page);
				})
		     );
  }

  for (auto& f : threads) {
    sum += f.get();
  }
  return sum;
}

/*int64_t ThreadMatrixSum(const std::vector<std::vector<int>>& matrix, size_t i_lower, size_t i_upper) {
  int64_t sum = 0;
  for (size_t i = i_lower; i < i_upper; i++) {
  for (const auto& j : matrix[i]) {
  sum += j;
  }
  }

  return sum;
  }

  int64_t CalculateMatrixSum(const std::vector<std::vector<int>>& matrix) {
  std::vector<std::future<int64_t>> threads;
  int64_t sum = 0;
  for (size_t i = 0; i < matrix.size(); i += matrix.size() / 3) {
  threads.push_back(
  std::async([i, &matrix] {
  return ThreadMatrixSum(matrix, i, i + matrix.size() / 3);
  })
  );
  }

  for (auto& f : threads) {
  sum += f.get();
  }
  return sum;
  }*/

void TestCalculateMatrixSum() {
  const std::vector<std::vector<int>> matrix = {
						{1, 2, 3, 4},
						{5, 6, 7, 8},
						{9, 10, 11, 12},
						{13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

void GenerateMatrix(std::vector<std::vector<int>>& matrix, size_t size) {
  for (size_t i = 0; i < matrix.size(); i++) {
    matrix[i].reserve(size);
    for (size_t j = 0; j < size; j++) {
      matrix[i].push_back(i*j);
    }
  }
}

void PrintMatrix(const std::vector<std::vector<int>>& matrix) {
  for (const auto& line : matrix) {
    for (const auto& element : line) {
      std::cout << element << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);

  return 0;
}
