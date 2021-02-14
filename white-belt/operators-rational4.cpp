#include <iostream>
#include <cmath>
#include <numeric>
#include <string>
#include <sstream>
using namespace std;

class Rational {
public:
  Rational() {
    // Реализуйте конструктор по умолчанию
    numerator = 0;
    denominator = 1;
  }

  Rational(int new_numerator, int new_denominator) {
    // Реализуйте конструктор
    if (new_numerator < 0) {
      numerator = new_numerator;
      denominator = new_denominator;
    } else if (new_denominator < 0) {
      numerator = -new_numerator;
      denominator = -new_denominator;
    } else {
      numerator = new_numerator;
      denominator = new_denominator;
    }
  }

  bool operator==(const Rational& rhs) const {
    if (this->Numerator() == rhs.Numerator() &&
	this->Denominator() == rhs.Denominator()) {
      return true;
    } else {
      return false;
    }
  }
  Rational operator+(const Rational& rhs) const {
    int lcm = std::lcm(this->denominator, rhs.denominator);
    return {this->numerator * (lcm / this->denominator)
	    + rhs.numerator * (lcm / rhs.denominator), lcm};
  }

  Rational operator-(const Rational& rhs) const {
    int lcm = std::lcm(this->denominator, rhs.denominator);
    return {this->numerator * (lcm / this->denominator)
	    - rhs.numerator * (lcm / rhs.denominator), lcm};
  }

  Rational operator*(const Rational& rhs) const {
    return {this->numerator * rhs.numerator, this->denominator * rhs.denominator};
  }

  Rational operator/(const Rational& rhs) const {
    return {this->numerator * rhs.denominator, this->denominator * rhs.numerator};
  }

  friend istream& operator>>(istream& stream, Rational& r) {
    int numerator, denominator;
    stream >> numerator;
    if (!stream) {
      return stream;
    }
    char c;
    stream >> c;
    if (c != '/') {
      return stream;
    }
    stream >> denominator;
    if (!stream) {
      return stream;
    }
    Rational tmp = {numerator, denominator};
    r = {tmp.Numerator(), tmp.Denominator()};
    return stream;
  }

  friend ostream& operator<<(ostream& stream, const Rational& r) {
    stream << r.Numerator() << "/" << r.Denominator();
    return stream;
  }


  int Numerator() const {
    // Реализуйте этот метод
    int gcd = std::gcd(numerator, denominator);
    return numerator / gcd;
  }

  int Denominator() const {
    // Реализуйте этот метод
    int gcd = std::gcd(numerator, denominator);
    return abs(denominator / gcd);
  }

private:
  // Добавьте поля
  int numerator;
  int denominator;
};  

int main() {
  {
    ostringstream output;
    output << Rational(-6, 8);
    if (output.str() != "-3/4") {
      cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
      return 1;
    }
  }

  {
    istringstream input("5/7");
    Rational r;
    input >> r;
    bool equal = r == Rational(5, 7);
    if (!equal) {
      cout << "5/7 is incorrectly read as " << r << endl;
      return 2;
    }
  }

  {
    istringstream input("");
    Rational r;
    bool correct = !(input >> r);
    if (!correct) {
      cout << "Read from empty stream works incorrectly" << endl;
      return 3;
    }
  }

  {
    istringstream input("5/7 10/8");
    Rational r1, r2;
    input >> r1 >> r2;
    bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
    if (!correct) {
      cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
      return 4;
    }

    input >> r1;
    input >> r2;
    correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
    if (!correct) {
      cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
      return 5;
    }
  }

  {
    istringstream input1("1*2"), input2("1/"), input3("/4");
    Rational r1, r2, r3;
    input1 >> r1;
    input2 >> r2;
    input3 >> r3;
    bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
    if (!correct) {
      cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
	   << r1 << " " << r2 << " " << r3 << endl;

      return 6;
    }
  }

  cout << "OK" << endl;
  return 0;
}
