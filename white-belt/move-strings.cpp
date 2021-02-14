#include <iostream>
#include <string>
#include <vector>

void MoveStrings(std::vector<std::string>& source, std::vector<std::string>& destination) {
  for (auto s : source) {
    destination.push_back(s);
  }
  source.clear();
}

int main(void) {

  
  
  return 0;
}
