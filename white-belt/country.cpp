#include <iostream>
#include <string>
#include <map>

int main(void) {

  std::map<std::string, std::string> countries;
  int q;
  std::cin >> q;
  
  std::string command, country, new_country, old_country, new_capital;
  for (int i = 0; i < q; i++) {
    std::cin >> command;
    
    if (command == "CHANGE_CAPITAL") {
      std::cin >> country >> new_capital;
      if (countries.count(country) == 0) {
	countries[country] = new_capital;
	std::cout << "Introduce new country " << country << " with capital " << new_capital << std::endl;
      } else if (countries[country] == new_capital) {
	std::cout << "Country " << country << " hasn't changed its capital" << std::endl;
      } else {
	std::cout << "Country " << country << " has changed its capital from " << countries[country] << " to " << new_capital << std::endl;
	countries[country] = new_capital;
      }
    } else if (command == "RENAME") {
      std::cin >> old_country >> new_country;
      if (old_country == new_country || countries.count(old_country) == 0 || countries.count(new_country) != 0) {
	std::cout << "Incorrect rename, skip" << std::endl;
      } else {
	std::cout << "Country " << old_country << " with capital " << countries[old_country] << " has been renamed to " << new_country << std::endl;
	countries[new_country] = countries[old_country];
	countries.erase(old_country);
      }
    } else if (command == "ABOUT") {
      std::cin >> country;
      if (countries.count(country) == 0) {
	std::cout << "Country " << country << " doesn't exist" << std::endl;
      } else {
	std::cout << "Country " << country << " has capital " << countries[country] << std::endl;
      }
    } else if (command == "DUMP") {
      if (countries.size() == 0) {
	std::cout << "There are no countries in the world" << std::endl;
      } else {
	for (const auto& [key,value] : countries) {
	  std::cout << key << '/' <<  value << ' ';
	}
	std::cout << std::endl;
      }
    }
    
  }
  
  return 0;
}
