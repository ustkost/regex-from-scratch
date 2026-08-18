#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "test.h"

void test() {
  printf("Running tests...\n");

  test_match_1();
  test_match_2();
  test_match_3();
  test_match_4();
  test_match_5();

  test_preproc();

  test_parser();

  printf("\nAll tests pass!\n");
}
