#include <iostream>
#include <cstdint>
#include <map>
#include <string>
#include <queue>
#include <exception>

struct Book_client {
  std::string hotel;
  int64_t time;
  uint32_t client_id;
  uint16_t room_count;
};

class Hotel {
private:
  std::queue<Book_client> queue_of_requered;
  std::map<std::string, uint32_t> hotels_to_count_of_room;
  std::map<std::string, std::map<uint32_t, uint32_t>> hotels_to_count_of_clients;

  int64_t current_time;

  void ClearOldRequared(void) {
    while (!queue_of_requered.empty() && queue_of_requered.front().time <= current_time - 86400) {
      Book_client old_book = queue_of_requered.front();
      
      hotels_to_count_of_clients[old_book.hotel][old_book.client_id]--;
      if (hotels_to_count_of_clients[old_book.hotel][old_book.client_id] == 0) {
	hotels_to_count_of_clients[old_book.hotel].erase(old_book.client_id);
      }

      hotels_to_count_of_room[old_book.hotel] -= old_book.room_count;

      queue_of_requered.pop();
    }
  }
  
public:
  void Book(const int64_t& time, const std::string& hotel_name, const uint32_t& client_id, const uint16_t& room_count) {
    queue_of_requered.push({hotel_name, time, client_id, room_count});

    hotels_to_count_of_clients[hotel_name][client_id]++;
    hotels_to_count_of_room[hotel_name] += room_count;

    current_time = time;
  }

  uint32_t Clients(const std::string& hotel) {
    ClearOldRequared();
    try {
     return hotels_to_count_of_clients.at(hotel).size(); 
    } catch (std::exception& ex) {
      return 0;
    }
  }
  
  uint32_t Rooms(const std::string& hotel) {
    ClearOldRequared();
    try {
      return hotels_to_count_of_room.at(hotel);
    } catch (std::exception& ex) {
      return 0;
    }
  }

  
};

/*class Hotel {
  private:
  /*int64_t time;
  std::string hotel_name;
  uint32_t client_id;
  uint16_t room_count;
  std::map<std::string, std::map<uint32_t, std::pair<int64_t, uint16_t>>> hotels;
  int64_t current_time;
  
  public:
  void Book(const int64_t& time, const std::string& hotel_name, const uint32_t& client_id, const uint16_t& room_count) {
  hotels[hotel_name][client_id] = std::make_pair(time, room_count);
  current_time = time;
  }
  uint64_t Clients(const std::string& hotel_name) {
  try {
  auto hotel = hotels.at(hotel_name);
  } catch (std::exception& e) {
  return 0;
  }
  auto hotel = hotels[hotel_name];
  std::set<uint32_t> clients_count;
  for (auto it = hotel.begin(), endit = hotel.end(); it != endit; it++) {
  int64_t t = it->second.first;
  if (current_time - 86400 < t && t <= current_time) {
  clients_count.insert(it->first);
  }
  }

  return static_cast<uint64_t>(clients_count.size());
  }

  uint64_t Rooms(const std::string& hotel_name) {
  try {
  auto hotel = hotels.at(hotel_name);
  } catch (std::exception& e) {
  return 0;
  }
  auto hotel = hotels[hotel_name];
  uint64_t room_count = 0;
  for (auto it = hotel.begin(), endit = hotel.end(); it != endit; it++) {
  int64_t t = it->second.first;
  if (current_time - 86400 < t && t <= current_time) {
  room_count += it->second.second;
  }
  }
  return room_count;
  }
  };*/

/*struct Booking {
  int64_t time;
  std::string hotel_name;
  uint32_t client_id;
  uint16_t room_count;
  };

  bool operator<(const Booking& lhs, const Booking& rhs) {
  return std::tie(lhs.time, lhs.hotel_name, lhs.client_id, lhs.room_count) <
  std::tie(rhs.time, rhs.hotel_name, rhs.client_id, rhs.room_count);
  }

  class Hotel {
  private:
  std::set<Booking> hotels;
  int64_t current_time;
  public:
  void Book(const int64_t& time, const std::string& hotel_name, const uint32_t& client_id, const uint16_t& room_count) {
  hotels.push_back({time, hotel_name, client_id, room_count});
  current_time = time;
  }
  uint64_t Clients(const std::string& hotel_name) {
  auto it = hotels.equal_range({current_time - 86400, hotel_name});
  uint64_t clients_count = 0;

  for (; it->first != it->second; it->first++) {
  client_count++;
  }

  return clients_count;
  }

  uint64_t Rooms(const std::string& hotel_name) {
  auto it = hotels.equal_range({current_time - 86400, hotel_name});
  uint64_t room_count = 0;

  for (; it->first != it->second; it->first++) {
  room_count += it->first.
  }
    
  return room_count;
  }
  }*/

      

int main(void) {

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Hotel h;

  int query_count;
  std::cin >> query_count;

  int64_t time;
  std::string hotel_name;
  uint32_t client_id;
  uint16_t room_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    std::string query_type;
    std::cin >> query_type;
    

    if (query_type == "BOOK") {
      std::cin >> time >> hotel_name >> client_id >> room_count;
      h.Book(time, hotel_name, client_id, room_count);
    } else if (query_type == "CLIENTS") {
      std::cin >> hotel_name;
      std::cout << h.Clients(hotel_name) << std::endl;
    } else if (query_type == "ROOMS") {
      std::cin >> hotel_name;
      std::cout << h.Rooms(hotel_name) << std::endl;
    }
  }

  return 0;
}
