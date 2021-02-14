#include <iostream>
#include <cmath>
#include <numeric>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <vector>

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

  bool operator<(const Rational& rhs) const {
    int lcm = std::lcm(this->denominator, rhs.denominator);
    int lhs_numerator = this->numerator * ( lcm / this->denominator );
    int rhs_numerator = rhs.numerator * ( lcm / rhs.denominator );
    if (lhs_numerator < rhs_numerator) {
      return true;
    } else {
      return false;
    }
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
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
