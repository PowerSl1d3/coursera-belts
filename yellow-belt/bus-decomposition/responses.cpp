#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "responses.h"

using namespace std;

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  if (r.buses.empty()) {
    return os << "No stop";
  }
  bool first = true;
  for (const std::string& i : r.buses) {
    if (!first) {
      os << " ";
    }
    first = false;
    os << i;
  }
  return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  if (r.stops.empty()) {
    return os << "No bus";
  }
  std::string last_stop = r.stops.back();
  for (const std::string& stop : r.stops) {
    os << "Stop " << stop << ":";
    if (r.buses_for_stop.at(stop).size() == 1) {
      os << " no interchange";
    } else {
      for (const std::string& bus : r.buses_for_stop.at(stop)) {
	if (bus == r.bus) {
	  continue;
	}
	os << " " <<  bus;
      }
    }
    if (stop != last_stop) {
      os << std::endl;
    }
  }
  return os;
}

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  if (r.stops_for_bus.size() == 0) {
    os << "No buses";
    return os;
  }
  std::string last_bus;
  for (const auto& [bus, stops] : r.stops_for_bus) {
    last_bus = bus;
  }
  for (const auto& [bus, stops] : r.stops_for_bus) {
    os << "Bus " << bus << ":";
    for (const std::string& stop : stops) {
      os << " " << stop;
    }
    if (bus != last_bus) {
      os << std::endl;
    }
  }
  return os;
}
