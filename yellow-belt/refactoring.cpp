#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Role {
public:
  Role(const string& name, const string& type)
    : name_(name)
    , type_(type)
  {}
  
  virtual void Walk(const string& destination) const {
    cout << type_ << ": " << name_ << " walks to: " << destination << endl;
  }
  
  string GetName() {
    return name_;
  }
  
  string GetType() {
    return type_;
  }
  
protected:
  const string name_;
  const string type_;
};

class Student : public Role {
public:
  Student(const string& name, const string& favouriteSong)
    : Role(name, "Student")
    , FavouriteSong(favouriteSong)
  {}
  
  void Learn() {
    cout << "Student: " << name_ << " learns" << endl;
  }

  void Walk(const string& destination) const override {
    cout << "Student: " << name_ << " walks to: " << destination << endl;
    SingSong();
  }

  void SingSong() const {
    cout << "Student: " << name_ << " sings a song: " << FavouriteSong << endl;
  }

public:
  const string FavouriteSong;
};


class Teacher : public Role {
public:

  Teacher(const string& name, const string& subject)
    : Role(name, "Teacher")
    , Subject(subject)
  {}
  
  void Teach() {
    cout << "Teacher: " << name_ << " teaches: " << Subject << endl;
  }

public:
  const string Subject;
};


class Policeman : public Role {
public:
  Policeman(const string& name)
    : Role(name, "Policeman")
  {}

  void Check(Role& r) const {
    cout << "Policeman: " << name_ << " checks " << r.GetType() << ". " << r.GetType() << "'s name is: " << r.GetName() << endl;
  }
};


void VisitPlaces(const Role& r, vector<string> places) {
  for (auto p : places) {
    r.Walk(p);
  }
}


int main() {
  Teacher t("Jim", "Math");
  Student s("Ann", "We will rock you");
  Policeman p("Bob");

  VisitPlaces(t, {"Moscow", "London"});
  p.Check(s);
  VisitPlaces(s, {"Moscow", "London"});
  return 0;
}
