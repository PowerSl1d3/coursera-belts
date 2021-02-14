#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <list>

using namespace std;

struct Record {
  string id;
  string title;
  string user;
  int timestamp;
  int karma;
};

// Реализуйте этот класс
class Database {
public:
  bool Put(const Record& record) {
    if (data_.count(record.id)) {
      return false;
    }
    storage_.push_front(record);
    data_[record.id] = storage_.begin();
    id_to_iterators[record.id] = {
			   data_by_timestamp.insert({record.timestamp, storage_.begin()}),
			   data_by_karma.insert({record.karma, storage_.begin()}),
			   data_by_user.insert({record.user, storage_.begin()})
    };
    return true;
  }
  const Record* GetById(const string& id) const {
    auto it = data_.find(id);
    
    if (it == data_.end()) {
      return nullptr;
    }

    return &(*it->second);
    
  }
  
  bool Erase(const string& id) {
    auto it = data_.find(id);
    if (it != data_.end()) {
      auto find_all_iterators = id_to_iterators.find(id);
      data_by_timestamp.erase(find_all_iterators->second.data_by_timestamp_iterator);
      data_by_karma.erase(find_all_iterators->second.data_by_karma_iterator);
      data_by_user.erase(find_all_iterators->second.data_by_user_iterator);
      id_to_iterators.erase(find_all_iterators);
      storage_.erase(it->second);
      data_.erase(it);
      return true;
    }

    return false;
  }

  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const {
    auto start_iterator = data_by_timestamp.lower_bound(low);
    auto end_iterator = data_by_timestamp.upper_bound(high);
    for(; start_iterator != end_iterator; start_iterator++) {
      if (!callback(*start_iterator->second)) {
	break;
      }
    }
  }

  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const {
    auto start_iterator = data_by_karma.lower_bound(low);
    auto end_iterator = data_by_karma.upper_bound(high);
    for(; start_iterator != end_iterator; start_iterator++) {
      if (!callback(*start_iterator->second)) {
	break;
      }
    }
  }

  template <typename Callback>
  void AllByUser(const string& user, Callback callback) const {
    auto [start, end] = data_by_user.equal_range(user);
    for(; start != end; start++) {
      if (!callback(*start->second)) {
	break;
      }
    }
  }

private:

  using ListIter = std::list<Record>::iterator;

  struct Iterators {

    std::multimap<int, Database::ListIter>::iterator data_by_timestamp_iterator;
    std::multimap<int, Database::ListIter>::iterator data_by_karma_iterator;
    std::multimap<std::string, Database::ListIter>::iterator data_by_user_iterator;
    
  };

  std::list<Record> storage_;
  std::unordered_map<std::string, ListIter> data_;
  std::multimap<int, ListIter> data_by_timestamp;
  std::multimap<int, ListIter> data_by_karma;
  std::multimap<std::string, ListIter> data_by_user;
  std::unordered_map<std::string, Iterators> id_to_iterators;
};

void TestRangeBoundaries() {
  const int good_karma = 1000;
  const int bad_karma = -10;

  Database db;
  db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
  db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

  int count = 0;
  db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestSameUser() {
  Database db;
  db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
  db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

  int count = 0;
  db.AllByUser("master", [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestReplacement() {
  const string final_body = "Feeling sad";

  Database db;
  db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
  db.Erase("id");
  db.Put({"id", final_body, "not-master", 1536107260, -10});

  auto record = db.GetById("id");
  ASSERT(record != nullptr);
  ASSERT_EQUAL(final_body, record->title);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestRangeBoundaries);
  RUN_TEST(tr, TestSameUser);
  RUN_TEST(tr, TestReplacement);
  return 0;
}
