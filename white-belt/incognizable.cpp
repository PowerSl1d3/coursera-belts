#include <iostream>

class Incognizable {
public:
  Incognizable() {}
  Incognizable(int a) { first_value = a; }
  Incognizable(int a, int b) { first_value = a; second_value = b; }
private:
int first_value;
int second_value;
};

int main(void) {
  Incognizable a;
  Incognizable b = {};
  Incognizable c = {0};
  Incognizable d = {0, 1};
  return 0;
}
