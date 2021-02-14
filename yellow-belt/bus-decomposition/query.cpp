#include "query.h"
#include <iostream>

using namespace std;

istream& operator >> (istream& is, Query& q) {
  std::string command, bus_stop;
  int stop_count = 0;
  q.stops.clear();
  is >> command;
  if (command == "NEW_BUS") {
    q.type = QueryType::NewBus;
    is >> q.bus;
    is >> stop_count;
    for (int i = 0; i < stop_count; i++) {
      is >> bus_stop;
      q.stops.push_back(bus_stop);
    }
  } else if (command == "BUSES_FOR_STOP") {
    q.type = QueryType::BusesForStop;
    is >> q.stop;
  } else if (command == "STOPS_FOR_BUS") {
    q.type = QueryType::StopsForBus;
    is >> q.bus;
  } else if (command == "ALL_BUSES") {
    q.type = QueryType::AllBuses;
  }
  return is;
}
