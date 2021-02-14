#include "bus_manager.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
  stops_for_bus[bus] = stops;
  for (const std::string& s : stops) {
    buses_for_stop[s].push_back(bus);
  }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
  if (buses_for_stop.count(stop) == 0) {
    return {};
  }
  return {buses_for_stop.at(stop)};
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
  if (stops_for_bus.count(bus) == 0) {
    return {};
  }
  return {bus, stops_for_bus.at(bus), buses_for_stop};
}

AllBusesResponse BusManager::GetAllBuses() const {
  return {stops_for_bus};
}
