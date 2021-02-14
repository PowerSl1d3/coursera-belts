#include <iostream>
#include <string>
#include <map>
#include <set>

std::set<std::string> BuildMapValuesSet(const std::map<int, std::string>&  m) {
  std::set<std::string> s;
  for (const auto& [key, value] : m) {
    s.insert(value);
  }
  return s;
}
