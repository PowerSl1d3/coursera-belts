#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main(void) {

  std::string s = "abcdefg";
  std::vector<int> nums = {1, 5, 2, 3, 5};
  std::vector<std::string> snums = {"1", "5", "2", "3", "5"};
  
  for (char c : s) {
    std::cout << c << std::endl;
  }

  for (int i : nums) {
    std::cout << i << std::endl;
  }

  for (auto j : snums) {
    std::cout << j << std::endl;
  }

  int quantity = count(begin(nums), end(nums), 5);

  std::cout << "count of 5 in nums - " << quantity << std::endl;

  sort(begin(nums), end(nums));

  for (int i : nums) {
    std::cout << i << std::endl;
  }

  std::vector<std::string> words = {"hello", "world", "my", "name", "is", "oleg"};

  sort(begin(words), end(words));

  for (auto s : words) {
    std::cout << s << std::endl;
  }
  
  return 0;
}
