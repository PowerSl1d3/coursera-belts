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
    if (new_numerator < 0 && new_denominator < 0) {
      numerator = -new_numerator;
      denominator = -new_denominator;
    } else if (new_numerator < 0) {
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
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}
