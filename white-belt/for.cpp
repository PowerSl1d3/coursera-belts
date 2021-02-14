#include <iostream>
#include <vector>
#include <map>

int main(void) {

  std::map<std::string, int> b = {{"a", 1}, {"b", 2}, {"c", 3}};

  int sum = 0;
  std::string concat;
  for (auto i : b) {
    sum += i.second;
    concat += i.first;
    std::cout << i.first << " --> " << i.second << std::endl;
  }

  std::cout << sum << ' ' << concat << std::endl;

  std::string a = "ngjdeafenfanfea";

  int i = 0;
  for(auto c : a) {
    if (c == 'a') {
      std::cout << i << std::endl;
    }
    i++;
  }

  std::cout << "##############" << std::endl;
  
  for(i = 0; i < a.size(); i++) {
    if (a[i] == 'a')
      std::cout << i << std::endl;
  }
  
  return 0;
}
