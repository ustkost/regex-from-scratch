#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "parser.h"

struct test_preproc {
  char *s;
  char *expected;
};

void test_preproc() {
  struct test_preproc tests[] = {
    {"ab", "a.b"},
    {"abc", "a.b.c"},
    {"a|b", "a|b"},
    {"a|bc", "a|b.c"},
    {"a*", "a*"},
    {"a*b", "a*.b"},
    {"a*b*", "a*.b*"},
    {"(a)b", "(a).b"},
    {"(a|b)c", "(a|b).c"},
    {"a(b)", "a.(b)"},
    {"a(b|c)", "a.(b|c)"},
    {"(a)(b)", "(a).(b)"},
    {"a*(b)", "a*.(b)"},
    {"(a)", "(a)"},
    {"(ab)", "(a.b)"},
  };

  printf("\n============================\n");
  printf("%s\n", "test_preproc");
  printf("============================\n\n");
  for (int i = 0; i < sizeof(tests)/sizeof(tests[0]); i++) {
    char *s = tests[i].s;
    char *expected = tests[i].expected;
    char actual[MAX_PARSER_OUTPUT];

    preprocess(s, actual);
    printf("Test case %d: s=%s, expected=%s, got=%s\n", i, s, expected, actual);
    assert(strcmp(actual, expected) == 0);
  }
}
