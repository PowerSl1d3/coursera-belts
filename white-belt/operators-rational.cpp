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
      if (new_numerator == 0) {
	numerator = 0;
	denominator = 1;
      } else if (new_numerator < 0 && new_denominator < 0) {
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

    int Numerator() const {
        // Реализуйте этот метод
      int gcd2 = std::gcd(numerator, denominator);
      return numerator / gcd2;
    }

    int Denominator() const {
        // Реализуйте этот метод
      int gcd2 = std::gcd(numerator, denominator);
      return denominator / gcd2;
    }

private:
      // Добавьте поля
  int numerator;
  int denominator;
};

int main() {
    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    Rational p(-1, -2), q(0, -2), s(1, -2);

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    cout << "OK" << endl;
    return 0;
}
