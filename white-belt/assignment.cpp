#include <iostream>
#include <vector>
#include <string>

int main(void) {

  std::string s = "hello";
  std::string t = s;

  t += ", world";

  std::cout << "s = " << s << std::endl;
  std::cout << "t = " << t << std::endl;

  std::vector<std::string> w = {"a", "b", "c"};
  std::vector<std::string> v;

  v = w;
  v[0] = "d";

  std::cout << w[0] << ' ' << w[1] << std::endl;
  std::cout << v[0] << ' ' << v[1] << std::endl;
  
  return 0;
  
}
