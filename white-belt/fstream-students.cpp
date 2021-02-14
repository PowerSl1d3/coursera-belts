#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Student {
  std::string first_name;
  std::string last_name;
  int day;
  int month;
  int year;
};

int main(void) {

  std::vector<Student> group;
  std::string command;
  int N, M, choise;

  std::cin >> N;
  group.resize(N);
  for (int i = 0; i < N; i++) {
    std::cin >> group[i].first_name >> group[i].last_name
	     >> group[i].day >> group[i].month >> group[i].year;
  }

  std::cin >> M;
  for (int i = 0; i < M; i++) {
    std::cin >> command >> choise;
    if (choise < 1 || choise > N) {
      std::cout << "bad request" << std::endl;
      continue;
    }
    if (command == "name") {
      std::cout << group[choise-1].first_name << " " << group[choise-1].last_name << std::endl;
    } else if (command == "date") {
      std::cout << group[choise-1].day << "." << group[choise-1].month << "." << group[choise-1].year << std::endl;
    } else {
      std::cout << "bad request" << std::endl;
    }
  }
  
  return 0;
}
