#include <iostream>
#include <cmath>
#include <numeric>
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
    Rational r1(4, 6);
    Rational r2(2, 3);
    bool equal = r1 == r2;
    if (!equal) {
      cout << "4/6 != 2/3" << endl;
      return 1;
    }
  }

  {
    Rational a(2, 3);
    Rational b(4, 3);
    Rational c = a + b;
    bool equal = c == Rational(2, 1);
    if (!equal) {
      cout << "2/3 + 4/3 != 2" << endl;
      return 2;
    }
  }

  {
    Rational a(5, 7);
    Rational b(2, 9);
    Rational c = a - b;
    bool equal = c == Rational(31, 63);
    if (!equal) {
      cout << "5/7 - 2/9 != 31/63" << endl;
      return 3;
    }
  }

  cout << "OK" << endl;
  return 0;
}
