#include <map>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
// если имя неизвестно, возвращает пустую строку
string FindNameByYear(const map<int, string>& names, int year) {
  string name;  // изначально имя неизвестно
  
  // перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
  for (const auto& item : names) {
    // если очередной год не больше данного, обновляем имя
    if (item.first <= year) {
      name = item.second; 
    } else {
      // иначе пора остановиться, так как эта запись и все последующие относятся к будущему
      break;
    }
  }
  
  return name;
}

vector<string> GetHistory(const map<int, string>& names, int year, string current_name) {
  vector<string> history;

  for (const auto& item : names) {
    if (item.first <= year) {
      if (history.size() == 0) {
	history.push_back(item.second);
      } else if (item.second != history.back()) {
	history.push_back(item.second);
      }
    } else {
      break;
    }
  }

  if (history.size() != 0 && history.back() == current_name) {
    history.resize(history.size() - 1);
  }
  
  return history;
}

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    last_names[year] = last_name;
  }
  string GetFullName(int year) {
    // получаем имя и фамилию по состоянию на год year
    const string first_name = FindNameByYear(first_names, year);
    const string last_name = FindNameByYear(last_names, year);
    
    // если и имя, и фамилия неизвестны
    if (first_name.empty() && last_name.empty()) {
      return "Incognito";
    
    // если неизвестно только имя
    } else if (first_name.empty()) {
      return last_name + " with unknown first name";
      
    // если неизвестна только фамилия
    } else if (last_name.empty()) {
      return first_name + " with unknown last name";
      
    // если известны и имя, и фамилия
    } else {
      return first_name + " " + last_name;
    }
  }
  string GetFullNameWithHistory(int year) {
     // получаем имя и фамилию по состоянию на год year
    const string first_name = FindNameByYear(first_names, year);
    const string last_name = FindNameByYear(last_names, year);
    const vector<string> first_name_history = GetHistory(first_names, year, first_name);
    const vector<string> last_name_history = GetHistory(last_names, year, last_name);
    string answer_first_name, answer_last_name;

    for (int i = first_name_history.size() - 1; i >= 0; i--) {
      answer_first_name += first_name_history[i];
      if (i - 1 >= 0) {
	answer_first_name += ", ";
      }
    }

    for (int i = last_name_history.size() - 1; i >= 0; i--) {
      answer_last_name += last_name_history[i];
      if (i - 1 >= 0) {
	answer_last_name += ", ";
      }
    }

    if (first_name.empty() && last_name.empty()) {
      return "Incognito";
    
    // если неизвестно только имя
    } else if (first_name.empty()) {
      
      if (answer_last_name.empty()) {
	 return last_name + " with unknown first name";
      }
      return last_name + " (" + answer_last_name + ")" + " with unknown first name";
      
    // если неизвестна только фамилия
    } else if (last_name.empty()) {
      
      if (answer_first_name.empty()) {
	 return first_name + " with unknown last name";
      }
      return first_name + " (" + answer_first_name + ")" + " with unknown last name";
      
    // если известны и имя, и фамилия
    } else {
      if (answer_first_name.empty() && answer_last_name.empty()) {
	return first_name + " " + last_name;
      } else if (answer_first_name.empty()) {
	return first_name + " " + last_name + " (" + answer_last_name + ")";
      } else if (answer_last_name.empty()) {
	return first_name + " (" + answer_first_name + ")" +  " " + last_name;
      } else {
	return first_name + " (" + answer_first_name + ")" +  " " + last_name + " (" + answer_last_name + ")";
      }
    }
  }

private:
  map<int, string> first_names;
  map<int, string> last_names;
};

int main() {
  Person person;
  
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1990, "Polina");
  person.ChangeLastName(1990, "Volkova-Sergeeva");
  cout << person.GetFullNameWithHistory(1990) << endl;
  
  person.ChangeFirstName(1966, "Pauline");
  cout << person.GetFullNameWithHistory(1966) << endl;
  
  person.ChangeLastName(1960, "Sergeeva");
  for (int year : {1960, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeLastName(1961, "Ivanova");
  cout << person.GetFullNameWithHistory(1967) << endl;
  
  return 0;
}

