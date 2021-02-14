#include <iostream>
#include <string>
#include <map>
#include <vector>

int main(void) {

  std::map<std::string, std::vector<std::string>> bus_map;
  int q;
  std::cin >> q;

  std::string command, bus, stop;
  std::vector<std::string> bus_list;
  std::vector<std::string> bus_stop_list;
  int count;
  
  for (int i = 0; i < q; i++) {
    std::cin >> command;
    if (command == "NEW_BUS") {
      std::cin >> bus;
      bus_list.push_back(bus);
      std::cin >> count;
      for (int j = 0; j < count; j++) {
	std::cin >> stop;
	bus_map[bus].push_back(stop);
      }
    } else if (command == "BUSES_FOR_STOP") {
      std::cin >> stop;
      bool print = false;
      for (const auto& b : bus_list) {
	for (const auto& s : bus_map[b]) {
	  if (s == stop) {
	    print = true;
	    std::cout << b << ' ';
	  }
	}
      }
      if (print == false) {
	std::cout << "No stop" << std::endl;
      } else {
	std::cout << std::endl;
      }
    } else if (command == "STOPS_FOR_BUS") {
      std::cin >> bus;
      if (bus_map.count(bus) == 0) {
	std::cout << "No bus" << std::endl;
      } else {
	bool print = false;
	for (const auto& s : bus_map[bus]) {
	  std::cout << "Stop " << s << ": ";
	  for (const auto& b : bus_list) {
	    for (const auto& bus_stop : bus_map[b]) {
	      if (bus_stop == s && b != bus) {
		print = true;
		std::cout << b << ' ';
	      }
	    }
	  }
	  if (print == false) {
	      std::cout << "no interchange";
	  } else {
	      print = false;
	  }
	  std::cout << std::endl;
	}
      } 
    } else if (command == "ALL_BUSES") {
      if (bus_map.size() == 0) {
	std::cout << "No buses" << std::endl;
      } else {
	for (const auto& [key, value] : bus_map) {
	std::cout << "Bus " << key << ": ";
	for (const auto& s : value) {
	  std::cout << s << ' ';
	}
	std::cout << std::endl;
	}
      }
    }
  }
  
  return 0;
}
