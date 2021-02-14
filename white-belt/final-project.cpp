#include <iostream>
#include <exception>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <iomanip>
#include <cctype>

class Date {
public:
  Date() {}
  Date(int new_year, int new_month, int new_day) {
    if (new_month < 1 || new_month > 12) {
      throw std::runtime_error("Month value is invalid: " + std::to_string(new_month));
    }
    if (new_day < 1 || new_day > 31) {
      throw std::runtime_error("Day value is invalid: " + std::to_string(new_day));
    }
    year = new_year;
    month = new_month;
    day = new_day;
  }
  int GetYear() const {
    return year;
  }
  int GetMonth() const {
    return month;
  }
  int GetDay() const {
    return day;
  }
private:
  int year;
  int month;
  int day;
};

void CheckStreamAndSkipSymbol(std::istream& is) {
  if (!is || is.peek() != '-') {
    throw std::invalid_argument("");
  } else {
    is.ignore(1);
  }
}

std::istream& operator>>(std::istream& is, Date& date) {
  int day, month, year;

  is >> year;
  CheckStreamAndSkipSymbol(is);
  is >> month;
  CheckStreamAndSkipSymbol(is);
  is >> day;

  if (!is || is.peek() != EOF) {
    throw std::invalid_argument("");
  }
  
  date = {year, month, day};
  return is;
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
  os << std::setfill('0') << std::setw(4) << date.GetYear()
     << "-" << std::setw(2) << date.GetMonth()
     << "-" << std::setw(2) << date.GetDay();
  return os;
}

bool operator<(const Date& lhs, const Date& rhs) {
  if (lhs.GetYear() < rhs.GetYear()) {
    return true;
  } else if (lhs.GetYear() == rhs.GetYear() &&
	     lhs.GetMonth() < rhs.GetMonth()) {
    return true;
  } else if (lhs.GetYear() == rhs.GetYear() &&
	     lhs.GetMonth() == rhs.GetMonth() &&
	     lhs.GetDay() < rhs.GetDay()) {
    return true;
  } else {
    return false;
  }
}

class Database {
public:
  void AddEvent(const Date& date, const std::string& event) {
    base[date].insert(event);
  }
  bool DeleteEvent(const Date& date, const std::string& event){
    if (base.count(date) && base.at(date).count(event)) {
      base[date].erase(event);
      if (base.at(date).size() == 0) {
	base.erase(date);
      }
      return true;
    } else {
      return false;
    }
  }
  int  DeleteDate(const Date& date) {
    if (base.count(date)) {
      int N = base.at(date).size();
      base.erase(date);
      return N;
    } else {
      return 0;
    }
  }
  bool Find(const Date& date) const {
    if (base.count(date) && base.at(date).size()) {
      for (const std::string& i : base.at(date)) {
	std::cout << i << std::endl;
      }
      return true;
    } else {
      return false;
    }
  }
  
  void Print() const {
    for (const auto& [key, value] : base) {
      for (const std::string& i : value) {
	std::cout << key << " " << i << std::endl;
      }
    }
  }
private:
  std::map<Date, std::set<std::string>> base;
};

int main() {
  Database db;
    
  std::string command;
  while (getline(std::cin, command)) {
    if (command.empty()) {
      continue;
    }
    std::stringstream stream(command);
    stream >> command;
    try {
      if (command == "Add") {
       	std::string string_date;
	std::string event;
	Date date;
	
	try {
	  stream >> string_date;
	  std::stringstream dstream(string_date);
	  dstream >> date;
	} catch (std::invalid_argument& ex) {
	  std::cout << "Wrong date format: " << string_date << std::endl;
	  exit(0);
	}

	stream >> event;
	
	db.AddEvent(date, event);
      } else if (command == "Del") {
	Date date;
	std::string event;
	std::string string_date;
	
	try {
	  stream >> string_date;
	  std::stringstream dstream(string_date);
	  dstream >> date;
	} catch (std::invalid_argument& ex) {
	  std::cout << "Wrong date format: " << string_date << std::endl;
	  exit(0);
	}

	stream >> event;
	
	if (event.empty()) {
	  std::cout << "Deleted " << db.DeleteDate(date) << " events" << std::endl;
	} else {
	  if (db.DeleteEvent(date, event)) {
	    std::cout << "Deleted successfully" << std::endl;
	  } else {
	    std::cout << "Event not found" << std::endl;
	  }
	}
      } else if (command == "Find") {
	Date date;
	std::string string_date;
	
	try {
	  stream >> string_date;
	  std::stringstream dstream(string_date);
	  dstream >> date;
	} catch (std::invalid_argument& ex) {
	  std::cout << "Wrong date format: " << string_date << std::endl;
	  exit(0);
	}
	
	db.Find(date);
      } else if (command == "Print") {
	db.Print();
      } else {
	throw std::runtime_error("Unknown command: " + command);
      }
    } catch (std::exception& ex) {
      std::cout << ex.what();
      exit(0);
    }
  }

  return 0;
}
