#include <iostream>
#include <string>

struct Specialization {
  explicit Specialization(std::string new_value) {
    value = new_value;
  }
  std::string value;
};


struct Course {
  explicit Course(std::string new_value) {
    value = new_value;
  }
  std::string value;
};


struct Week {
  explicit Week(std::string new_value) {
    value = new_value;
  }
  std::string value;
};

struct LectureTitle {
  LectureTitle(Specialization s, Course c, Week w) {
    specialization = s.value;
    course = c.value;
    week = w.value;
  }
  std::string specialization;
  std::string course;
  std::string week;
};

int main(void) {

  LectureTitle title(
    Specialization("C++"),
    Course("White belt"),
    Week("4th"));
  
  return 0;
}
