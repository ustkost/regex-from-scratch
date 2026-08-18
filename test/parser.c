#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "parser.h"

struct test_parser {
  char *s;
  char *expected;
  int expected_status;
};

void test_parser() {
  struct test_parser tests[] = {
    {"ab",      "ab.",    0},
    {"a|b",     "ab|",    0},
    {"a*",      "a*",     0},
    {"a*b",     "a*b.",   0},
    {"ab|c",    "ab.c|",  0},
    {"(a|b)c",  "ab|c.",  0},
    {"a(b|c)",  "abc|.",  0},
    {"abc",     "ab.c.",  0},
    {"a|b|c",   "ab|c|",  0},
    {"(ab)*",   "ab.*",   0},
    {"(a|b)*c", "ab|*c.", 0},
    {"a(b|c)*", "abc|*.", 0},
    {"",        "",       0},
    {"a",       "a",      0},
    {"(a",       NULL,   -1},
    {"a)",       NULL,   -1},
    {"((a)",     NULL,   -1},
    {"a))",      NULL,   -1},
    {")(",       NULL,   -1},
    {"(",        NULL,   -1},
    {")",        NULL,   -1},
  };

  printf("\n============================\n");
  printf("test_parser\n");
  printf("============================\n\n");
  for (int i = 0; i < sizeof(tests)/sizeof(tests[0]); i++) {
    char *s = tests[i].s;
    char *expected = tests[i].expected;
    int expected_status = tests[i].expected_status;
    char actual[MAX_PARSER_OUTPUT];
    char error[MAX_PARSER_ERROR];

    int actual_status = parser(s, actual, error);
    printf("Test case %d: s=%s, expected_status=%d, got_status=%d\n", i, s, expected_status, actual_status);
    assert(expected_status == actual_status);
    if (actual_status == 0) {
      printf("expected=%s, got=%s\n", expected, actual);
      assert(strcmp(actual, expected) == 0);
    } else {
      printf("error=%s\n", error);
    }
  }
}
