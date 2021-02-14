#include <iostream>
#include "test_runner.h"

void sumTest() {
  ASSERT_EQUAL(1, 0);
}

int main(void) {
  TestRunner tr;

  RUN_TEST(tr, sumTest);

  return 0;
}
