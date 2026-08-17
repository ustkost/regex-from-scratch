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
  struct state *accepting_states[MAX_ACCEPTING_SIZE]
) {
  printf("\n");
  printf("============================\n");
  printf("%s\n", message);
  printf("============================\n");
  printf("\n");
  for (int i = 0; i < n; i++) {
    char *s = tests[i].s;
    int expected = tests[i].expected;

    int actual = match_string(s, initial, accepting_states);
    printf("Test case %d: s=%s, expected=%d, got=%d\n", i, s, expected, actual);
    assert(actual == expected);
  }
}

// "ab"
void test_match_1() {
  struct state q0;
  struct state q1;
  struct state q2;
  
  q0.symbol = 'a';
  q0.out = &q1;
  q0.eps_out = NULL;
  
  q1.symbol = 'b';
  q1.out = &q2;
  q1.eps_out = NULL;
  
  q2.out = NULL;
  q2.eps_out = NULL;
  
  struct state *initial = &q0;
  struct state *accepting_states[MAX_ACCEPTING_SIZE] = {0};
  accepting_states[0] = &q2;
 
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
    "test_match_1: \"ab\". Simple concatenation",
    tests,
    ARRAY_SIZE(tests),
    initial,
    accepting_states
  );
}

// "a*"
void test_match_2() {
  struct state q0;
  
  q0.symbol = 'a';
  q0.out = &q0;
  q0.eps_out = NULL;
  
  struct state *initial = &q0;
  struct state *accepting_states[MAX_ACCEPTING_SIZE] = {0};
  accepting_states[0] = &q0;
 
  struct test_match tests[] = {
    {"", 1},
    {"a", 1},
    {"aa", 1},
    {"aaa", 1},
    {"aaaaaaaaaaa", 1},
    {"b", 0},
    {"ab", 0},
    {"ba", 0},
    {"aab", 0},
    {"baa", 0},
    {"bba", 0},
    {"baaaaaa", 0},
    {"aba", 0},
    {"aaaaabaaaaa", 0}
  };
  
  run_tests(
    "test_match_2: \"a*\". Looping state",
    tests,
    ARRAY_SIZE(tests),
    initial,
    accepting_states
  );
}

// "a|b"
void test_match_3() {
  struct state q0;
  struct state q1;
  struct state q2;
  struct state q3;
  
  q0.symbol = 'a';
  q0.out = &q1;
  q0.eps_out = &q2;

  q1.out = NULL;
  q1.eps_out = NULL;

  q3.out = NULL;
  q3.eps_out = NULL;

  q2.symbol = 'b';
  q2.out = &q3;
  q2.eps_out = NULL;
  
  struct state *initial = &q0;
  struct state *accepting_states[MAX_ACCEPTING_SIZE] = {0};
  accepting_states[0] = &q1;
  accepting_states[1] = &q3;
 
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
    "test_match_3: \"a|b\". Epsilon transitions",
    tests,
    ARRAY_SIZE(tests),
    initial,
    accepting_states
  );
}


// "ab*"
void test_match_4() {
  struct state q0;
  struct state q1;
  
  q0.symbol = 'a';
  q0.out = &q1;
  q0.eps_out = NULL;

  q1.symbol = 'b';
  q1.out = &q1;
  q1.eps_out = NULL;
  
  struct state *initial = &q0;
  struct state *accepting_states[MAX_ACCEPTING_SIZE] = {0};
  accepting_states[0] = &q1;
 
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
    "test_match_4: \"ab*\". Concatenation + star",
    tests,
    ARRAY_SIZE(tests),
    initial,
    accepting_states
  );
}

// "a+"
void test_match_5() {
  struct state q0;
  struct state q1;
  
  q0.symbol = 'a';
  q0.out = &q1;
  q0.eps_out = NULL;

  q1.symbol = 'a';
  q1.out = &q1;
  q1.eps_out = NULL;
  
  struct state *initial = &q0;
  struct state *accepting_states[MAX_ACCEPTING_SIZE] = {0};
  accepting_states[0] = &q1;
 
  struct test_match tests[] = {
    {"a", 1},
    {"aa", 1},
    {"aaaaa", 1},
    {"", 0},
    {"b", 0},
    {"ab", 0},
    {"ba", 0},
  };
  
  run_tests(
    "test_match_5: \"a+\". One or more",
    tests,
    ARRAY_SIZE(tests),
    initial,
    accepting_states
  );
}


// "(a|b)c"
void test_match_6() {
  struct state q0;
  struct state q1;
  struct state q2;
  struct state q3;
  struct state q4;
  
  q0.symbol = 'a';
  q0.out = &q1;
  q0.eps_out = &q2;

  q1.symbol = 'c';
  q1.out = &q4;
  q1.eps_out = NULL;

  q2.symbol = 'b';
  q2.out = &q3;
  q2.eps_out = NULL;
  
  q3.symbol = 'c';
  q3.out = &q4;
  q3.eps_out = NULL;

  q4.out = NULL;
  q4.eps_out = NULL;
  
  struct state *initial = &q0;
  struct state *accepting_states[MAX_ACCEPTING_SIZE] = {0};
  accepting_states[0] = &q4;
 
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
    "test_match_6: \"(a|b)c\". Epsilon transitions + concatenation",
    tests,
    ARRAY_SIZE(tests),
    initial,
    accepting_states
  );
}

// "(a|b)*"
void test_match_7() {
  struct state q0;
  struct state q1;
  struct state q2;
  struct state q3;
  
  q0.symbol = 'a';
  q0.out = &q3;
  q0.eps_out = &q1;

  q1.symbol = 'b';
  q1.out = &q2;
  q1.eps_out = NULL;

  q2.symbol = 'b';
  q2.out = &q2;
  q2.eps_out = &q3;
  
  q3.symbol = 'a';
  q3.out = &q3;
  q3.eps_out = &q2;
  
  struct state *initial = &q0;
  struct state *accepting_states[MAX_ACCEPTING_SIZE] = {0};
  accepting_states[0] = &q0;
  accepting_states[1] = &q2;
  accepting_states[2] = &q3;
 
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
    "test_match_7: \"(a|b)*\". Epsilon transitions + star",
    tests,
    ARRAY_SIZE(tests),
    initial,
    accepting_states
  );
}

void test() {
  printf("Running tests...\n");

  test_match_1();
  test_match_2();
  test_match_3();
  test_match_4();
  test_match_5();
  test_match_6();
  test_match_7();

  printf("\n");
  printf("All tests pass!\n");
}
