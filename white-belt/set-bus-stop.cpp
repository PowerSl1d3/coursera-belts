#include <iostream>
#include <set>
#include <string>
#include <map>

int main(void) {

  std::map<std::set<std::string>, int> bus_map;
  std::string bus_stop;
  int n, count;
  
  std::cin >> n;

  for (int i = 0; i < n; i++) {
    std::set<std::string> route;
    std::cin >> count;
    for (int j = 0; j < count; j++) {
      std::cin >> bus_stop;
      route.insert(bus_stop);
    }

    if (bus_map.count(route) == 0) {
      int size = bus_map.size() + 1;
      bus_map[route] = size;
      std::cout << "New bus " << size << std::endl;
    } else {
      std::cout << "Already exists for " << bus_map[route] << std::endl;
    }
  }
    
  return 0;
}
