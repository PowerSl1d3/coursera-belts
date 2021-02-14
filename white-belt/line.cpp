#include <iostream>
#include <vector>
#include <string>

int ret_id(std::string command) {
  if (command == "WORRY") {
    return 0;
  } else if (command == "QUIET") {
    return 1;
  } else if (command == "COME") {
    return 2;
  } else if (command == "WORRY_COUNT") {
    return 3;
  }

  return -1;
}

int main(void) {

  int n;
  std::cin >> n;

  std::string command;
  std::vector<bool> people;
  
  for (int i = 0; i < n; i++) {
    int choise;
    int worry_count = 0;
    std::cin >> command;
    switch (ret_id(command)) {
    case 0:
      std::cin >> choise;
      people[choise] = true;
      break;
    case 1:
      std::cin >> choise;
      people[choise] = false;
      break;
    case 2:
      std::cin >> choise;
      people.resize(people.size() + choise, false);
      break;
    case 3:
      for (bool p : people) {
	if (p == true) {
	  worry_count++;
	}
      }
      std::cout << worry_count << std::endl;
      break;
    }
  }
  return 0;
}
