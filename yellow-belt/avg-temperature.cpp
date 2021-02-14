#include <iostream>
#include <vector>

int main(void) {

  size_t N;
  std::cin >> N;
  std::vector<int> temperatures(N);

  for (int &i : temperatures) {
    std::cin >> i;
  }

  int64_t sum = 0;
  for (const int& i : temperatures) {
    sum += i;
  }
  int64_t avg = sum / static_cast<int64_t>(temperatures.size());

  std::vector<int> new_temperatures;
  for (size_t i = 0, n = temperatures.size(); i < n; i++) {
    if (temperatures[i] > avg) {
      new_temperatures.push_back(i);
    }
  }

  std::cout << new_temperatures.size() << std::endl;
  for (const int& i : new_temperatures) {
    std::cout << i << " ";
  }

  return 0;
}
