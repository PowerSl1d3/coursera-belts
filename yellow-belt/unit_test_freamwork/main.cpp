#include <iostream>
#include "test_runner.h"

void sumTest() {
  AssertEqual(1, 0, "Error");
}

int main(void) {
  TestRunner tr;

  tr.RunTest(sumTest, "A+B");

  return 0;
}
