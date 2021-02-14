#include <iostream>
#include <vector>
#include <string>
#include <map>

struct Person {
  std::string name;
  std::string surname;
  int age;
};

int main(void) {
  int x = -5;
  double pi = 3.14;
  bool logical_value = false;
  char symbol = 'Z';

  std::string hw = "Hello world";
  std::cout << hw << std::endl;

  std::vector<int> nums = {1, 3, 5, 7};
  std::cout << nums.size() << std::endl;

  std::map<std::string, int> name_to_value;
  name_to_value["one"] = 1;
  name_to_value["two"] = 2;
  
  std::cout << "two is " << name_to_value["two"] << std::endl;

  std::vector<Person> staff;
  staff.push_back({"Ivan", "Ivanov", 25});
  staff.push_back({"Petr", "Petrov", 32});

  std::cout << staff[0].name << std::endl;

  return 0;
}
