#include <iostream>
#include <string>
#include <vector>
#include <map>

class Person {
public:
  void ChangeFirstName(int year, const std::string& first_name) {
    // добавить факт изменения имени на first_name в год year
    people[year].resize(2);
    people[year][0] = first_name;
  }
  void ChangeLastName(int year, const std::string& last_name) {
    // добавить факт изменения фамилии на last_name в год year
    people[year].resize(2);
    people[year][1] = last_name;
  }
  std::string GetFullName(int year) {
    // получить имя и фамилию по состоянию на конец года year
    std::string first_name = "", last_name = "";
    for (const auto& [key, value] : people) {
      if (key <= year) {
	if (value[0] != "") {
	  first_name = value[0];
	}
	if (value[1] != "") {
	  last_name = value[1];
	}
      } else {
	break;
      }
    }

    if (first_name == "" && last_name == "") {
      return "Incognito";
    } else if (first_name.empty()) {
      return last_name + " with unknown first name";
    } else if (last_name.empty()) {
      return first_name + " with unknown last name";
    } else {
      return first_name + ' ' + last_name;
    }
  }
private:
  // приватные поля
  std::map<int, std::vector<std::string>> people;
};

int main(void) {
  using namespace std;
  Person person;
  
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  return 0;
  return 0;
}
