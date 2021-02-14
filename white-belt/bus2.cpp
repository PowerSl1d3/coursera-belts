#include <iostream>
#include <vector>
#include <map>
#include <string>

int main(void) {

  std::map<std::vector<std::string>, int> stop_to_bus;
  std::vector<std::string> route;
  int n, count, route_number = 1;
  std::cin >> n;

  for (int i = 0; i < n; i++) {
    std::cin >> count;
    route.assign(count, "");
    for (auto& s: route) {
      std::cin >> s;
    }
    if (stop_to_bus.count(route) == 0) {
      stop_to_bus[route] = route_number;
      std::cout << "New bus " << route_number++ << std::endl;
    } else {
      std::cout << "Already exists for " << stop_to_bus[route] << std::endl;
    }
  }
  
  return 0;
}
