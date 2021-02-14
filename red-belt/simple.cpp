#include <iostream>
#include <vector>

class People {
public:
  People(int name, int last_name) {
    name_ = name;
    last_name_ = last_name;
  }
  int name_;
  int last_name_;
};

int main(void) {
  std::vector<People> vec;
  vec.push_back(People(1, 2));
  vec.push_back(People(3, 4));
  for(const People& p : vec) {
    std::cout << "name = " << p.name_ << " last_name = " << p.last_name_ << std::endl;
  }

  return 0;
}
