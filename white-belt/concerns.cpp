#include <iostream>
#include <string>
#include <vector>

int main(void) {

  std::vector<std::vector<std::string>> year(31);
  int count = 1;

  std::string command, work;
  int n;
  int choise;
  
  std::cin >> n;

  for (int i = 0; i < n; i++) {

    std::cin >> command;

    if (command == "ADD") {
      std::cin >> choise >> work;
      year[choise-1].push_back(work);
    } else if (command == "DUMP") {
      std::cin >> choise;
      std::cout << year[choise-1].size() << ' ';
      for (auto s : year[choise - 1]) {
	std::cout << s << ' ';
      }
      std::cout << std::endl;
    } else {
      if (year.size() == 31 && count % 12 == 1) {
	count++;
	std::vector<std::string> new_last_days;
	for (int i = 27; i < year.size(); i++) {
	  for (int j = 0; j < year[i].size(); j++) {
	    new_last_days.push_back(year[i][j]);
	  }
	}
	year.resize(27);
	year.push_back(new_last_days);
      } else if (year.size() == 31 && (count % 12 == 7 || count % 12 == 0)) {
	count++;
	continue;
      } else if (year.size() == 31 && count % 12 != 1) {
	count++;
	std::vector<std::string> new_last_days;
	for (int i = 29; i < year.size(); i++) {
	  for (int j = 0; j < year[i].size(); j++) {
	    new_last_days.push_back(year[i][j]);
	  }
	}
	year.resize(29);
	year.push_back(new_last_days);
      } else {
	count++;
	year.resize(31);
      }
    }
    
  }
  
  return 0;
}
