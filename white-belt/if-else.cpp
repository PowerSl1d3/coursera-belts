#include <iostream>
#include <string>
#include <vector>

int main(void) {

  int x = 4;

  int y = 5;

  if (x == y) {
    std::cout << "equal" << std::endl;
  } else {
    std::cout << "not equal" << std:: endl;
  }

  std::vector<int> nums = {1, 2, 3};

  for (auto x : nums) {
    std::cout << x << std::endl;
  }

  int n = 5;
  int sum = 0;

  for (int i = 1; i <= n; i++) {
      sum += i;
  }

  std::cout << sum << std::endl;

  //simple comment

  std::vector<std::string> word = {"hello", "world"};

  for (int i = 0; i < word.size(); i++) {
    std::cout << word[i] << std::endl;
  }
	 
  
  return 0;
}
