#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "match.h"

#define ARRAY_SIZE(x) ((sizeof x) / (sizeof *x))

struct test_match {
  char *s;
  int expected;
};

void run_tests(
  char message[],
  struct test_match tests[],
  int n,
  struct state *initial,
  struct state *accepting_state
) {
  printf("\n============================\n");
  printf("%s\n", message);
  printf("\n============================\n");
  for (int i = 0; i < n; i++) {
    char *s = tests[i].s;
    int expected = tests[i].expected;

    int actual = match_string(s, initial, accepting_state);
    printf("Test case %d: s=%s, expected=%d, got=%d\n", i, s, expected, actual);
    assert(actual == expected);
  }
}

// "ab"
void test_match_1() {
  struct state q0, q1, q2;
  q0 = (struct state){
    .t1 = { .sym = 'a', .to = &q1 },
    .t2 = { .to = NULL }
  };
  
  q1 = (struct state){
    .t1 = { .sym = 'b', .to = &q2 },
    .t2 = { .to = NULL }
  };

  q2 = (struct state){
    .t1 = { .to = NULL },
    .t2 = { .to = NULL }
  };
  
  struct state *initial = &q0;
  struct state *accepting_state = &q2;
 
  struct test_match tests[] = {
    {"ab", 1},
    {"", 0},
    {"a", 0},
    {"b", 0},
    {"aa", 0},
    {"ac", 0},
    {"fg", 0},
    {"bb", 0},
    {"ba", 0},
    {"aab", 0},
    {"abb", 0},
    {"aaa", 0},
    {"bbb", 0},
    {"aaaabbbaaaabab", 0}
  };
  
  run_tests(
    "test_match_1: \"ab\"",
    tests,
    ARRAY_SIZE(tests),
    initial,
    accepting_state
  );
}

// "ab*"
void test_match_2() {
  struct state q0, q1, q2, q3, q4;

  q0 = (struct state){
    .t1 = { .sym = 'a', .to = &q1 },
    .t2 = { .to = NULL }
  };
  
  q1 = (struct state){
    .t1 = { .sym = EPS, .to = &q2 },
    .t2 = { .sym = EPS, .to = &q4 }
  };
  
  q2 = (struct state){
    .t1 = { .sym = 'b', .to = &q3 },
    .t2 = { .to = NULL }
  };
  
  q3 = (struct state){
    .t1 = { .sym = EPS, .to = &q2 },
    .t2 = { .sym = EPS, .to = &q4 }
  };

  q4 = (struct state) {
    .t1 = { .to = NULL },
    .t2 = { .to = NULL },
  };
  
  struct state *initial = &q0;
  struct state *accepting_state = &q4;

  struct test_match tests[] = {
    {"a", 1},
    {"ab", 1},
    {"abb", 1},
    {"abbbbbb", 1},
    {"", 0},
    {"b", 0},
    {"ba", 0},
    {"aab", 0},
    {"abba", 0},
    {"abc", 0},
  };

  run_tests(
    "test_match_2: \"ab*\"",
    tests,
    ARRAY_SIZE(tests),
    initial,
    accepting_state
  );
}

// "a|b"
void test_match_3() {
  struct state q0, q1, q2, q3, q4, q5;
  
  q0 = (struct state){
    .t1 = { .sym = EPS, .to = &q1 },
    .t2 = { .sym = EPS, .to = &q3 }
  };

  q1 = (struct state) {
    .t1 = { .sym = 'a', .to = &q2 },
    .t2 = { .to = NULL }
  };
  
  q2 = (struct state) {
    .t1 = { .sym = EPS, .to = &q5 },
    .t2 = { .to = NULL }
  };
  
  q3 = (struct state) {
    .t1 = { .sym = 'b', .to = &q4 },
    .t2 = { .to = NULL }
  };
  
  q4 = (struct state) {
    .t1 = { .sym = EPS, .to = &q5 },
    .t2 = { .to = NULL }
  };

  q5 = (struct state) {
    .t1 = { .to = NULL },
    .t2 = { .to = NULL }
  };
  
  struct state *initial = &q0;
  struct state *accepting_state = &q5;
 
  struct test_match tests[] = {
    {"a", 1},
    {"b", 1},
    {"", 0},
    {"c", 0},
    {"aa", 0},
    {"ab", 0},
    {"ba", 0},
    {"bb", 0},
    {"aaa", 0},
    {"aab", 0},
    {"baa", 0},
    {"bbb", 0},
    {"baaaaaa", 0},
    {"aba", 0},
    {"aaaaabaaaaa", 0}
  };

  run_tests(
    "test_match_3: \"a|b\"",
    tests,
    ARRAY_SIZE(tests),
    initial,
    accepting_state
  );
}

// "(a|b)c"
void test_match_4() {
  struct state q0, q1, q2, q3, q4, q5, q6;
  
  q0 = (struct state){
    .t1 = { .sym = EPS, .to = &q1 },
    .t2 = { .sym = EPS, .to = &q3 }
  };

  q1 = (struct state) {
    .t1 = { .sym = 'a', .to = &q2 },
    .t2 = { .to = NULL }
  };
  
  q2 = (struct state) {
    .t1 = { .sym = EPS, .to = &q5 },
    .t2 = { .to = NULL }
  };
  
  q3 = (struct state) {
    .t1 = { .sym = 'b', .to = &q4 },
    .t2 = { .to = NULL }
  };
  
  q4 = (struct state) {
    .t1 = { .sym = EPS, .to = &q5 },
    .t2 = { .to = NULL }
  };

  q5 = (struct state) {
    .t1 = { .sym = 'c', .to = &q6 },
    .t2 = { .to = NULL }
  };

  q6 = (struct state) {
    .t1 = { .to = NULL },
    .t2 = { .to = NULL }
  };
  
  struct state *initial = &q0;
  struct state *accepting_state = &q6;
 
  struct test_match tests[] = {
    {"ac", 1},
    {"bc", 1},
    {"a", 0},
    {"b", 0},
    {"c", 0},
    {"", 0},
    {"abc", 0},
    {"acc", 0},
    {"aac", 0},
  };

  run_tests(
    "test_match_4: \"(a|b)c\"",
    tests,
    ARRAY_SIZE(tests),
    initial,
    accepting_state
  );
}

// "(a|b)*"
void test_match_5() {
  struct state q0, q1, q2, q3, q4, q5, q6, q7;
  
  q0 = (struct state) {
    .t1 = { .sym = EPS, .to = &q1 },
    .t2 = { .sym = EPS, .to = &q7 }
  };

  q1 = (struct state){
    .t1 = { .sym = EPS, .to = &q2 },
    .t2 = { .sym = EPS, .to = &q4 }
  };

  q2 = (struct state) {
    .t1 = { .sym = 'a', .to = &q3 },
    .t2 = { .to = NULL }
  };
  
  q3 = (struct state) {
    .t1 = { .sym = EPS, .to = &q6 },
    .t2 = { .to = NULL }
  };
  
  q4 = (struct state) {
    .t1 = { .sym = 'b', .to = &q5 },
    .t2 = { .to = NULL }
  };
  
  q5 = (struct state) {
    .t1 = { .sym = EPS, .to = &q6 },
    .t2 = { .to = NULL }
  };

  q6 = (struct state) {
    .t1 = { .sym = EPS, .to = &q1 },
    .t2 = { .sym = EPS, .to = &q7 }
  };
  
  q7 = (struct state) {
    .t1 = { .to = NULL },
    .t2 = { .to = NULL }
  };
 
  struct state *initial = &q0;
  struct state *accepting_state = &q7;
 
  struct test_match tests[] = {
    {"", 1},
    {"a", 1},
    {"b", 1},
    {"ab", 1},
    {"ba", 1},
    {"aabbab", 1},
    {"aaaa", 1},
    {"bbbb", 1},
    {"c", 0},
    {"abc", 0},
    {"aabbc", 0},
  };

  run_tests(
    "test_match_5: \"(a|b)*\"",
    tests,
    ARRAY_SIZE(tests),
    initial,
    accepting_state
  );
}

void test() {
  printf("Running tests...\n");

  test_match_1();
  test_match_2();
  test_match_3();
  test_match_4();
  test_match_5();

  printf("\nAll tests pass!\n");
}
