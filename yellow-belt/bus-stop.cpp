#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cassert>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

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

struct BusesForStopResponse {
  std::vector<std::string> buses;
};

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

struct StopsForBusResponse {
  std::string bus;
  std::vector<std::string> stops;
  std::map<std::string,std::vector<std::string>> buses_for_stop;
};

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

struct AllBusesResponse {
  std::map<std::string,std::vector<std::string>> stops_for_bus;
};

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

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    stops_for_bus[bus] = stops;
    for (const std::string& s : stops) {
      buses_for_stop[s].push_back(bus);
    }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    if (buses_for_stop.count(stop) == 0) {
      return {};
    }
    return {buses_for_stop.at(stop)};
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    if (stops_for_bus.count(bus) == 0) {
      return {};
    }
    return {bus, stops_for_bus.at(bus), buses_for_stop};
  }

  AllBusesResponse GetAllBuses() const {
    return {stops_for_bus};
  }
private:
  std::map<std::string,std::vector<std::string>> buses_for_stop;
  std::map<std::string,std::vector<std::string>> stops_for_bus;
  
};

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
