#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include "../src/match/match.h"
#include "../src/thompson/thompson.h"
#include "../src/parse/parse.h"

struct test_e2e {
  char *regex;
  char *s;
  int expected;
};

void test_e2e() {
  struct test_e2e tests[] = {
    {"ab", "ab", 1},
    {"ab", "", 0},
    {"ab", "a", 0},
    {"ab", "b", 0},
    {"ab", "aa", 0},
    {"ab", "ac", 0},
    {"ab", "fg", 0},
    {"ab", "bb", 0},
    {"ab", "ba", 0},
    {"ab", "aab", 0},
    {"ab", "abb", 0},
    {"ab", "aaa", 0},
    {"ab", "bbb", 0},
    {"ab", "aaaabbbaaaabab", 0},

    {"ab*", "a", 1},
    {"ab*", "ab", 1},
    {"ab*", "abb", 1},
    {"ab*", "abbbbbb", 1},
    {"ab*", "", 0},
    {"ab*", "b", 0},
    {"ab*", "ba", 0},
    {"ab*", "aab", 0},
    {"ab*", "abba", 0},
    {"ab*", "abc", 0},

    {"a|b", "a", 1},
    {"a|b", "b", 1},
    {"a|b", "", 0},
    {"a|b", "c", 0},
    {"a|b", "aa", 0},
    {"a|b", "ab", 0},
    {"a|b", "ba", 0},
    {"a|b", "bb", 0},
    {"a|b", "aaa", 0},
    {"a|b", "aab", 0},
    {"a|b", "baa", 0},
    {"a|b", "bbb", 0},
    {"a|b", "baaaaaa", 0},
    {"a|b", "aba", 0},
    {"a|b", "aaaaabaaaaa", 0},
    
    {"(a|b)c", "ac", 1},
    {"(a|b)c", "bc", 1},
    {"(a|b)c", "a", 0},
    {"(a|b)c", "b", 0},
    {"(a|b)c", "c", 0},
    {"(a|b)c", "", 0},
    {"(a|b)c", "abc", 0},
    {"(a|b)c", "acc", 0},
    {"(a|b)c", "aac", 0},
    
    {"(a|b)*", "", 1},
    {"(a|b)*", "a", 1},
    {"(a|b)*", "b", 1},
    {"(a|b)*", "ab", 1},
    {"(a|b)*", "ba", 1},
    {"(a|b)*", "aabbab", 1},
    {"(a|b)*", "aaaa", 1},
    {"(a|b)*", "bbbb", 1},
    {"(a|b)*", "c", 0},
    {"(a|b)*", "abc", 0},
    {"(a|b)*", "aabbc", 0},
  };

  printf("\n============================\n");
  printf("test_e2e\n");
  printf("============================\n\n");
  for (int i = 0; i < sizeof(tests)/sizeof(tests[0]); i++) {
    char *s = tests[i].s;
    char *regex = tests[i].regex;
    int expected = tests[i].expected;

    char postfix_regex[MAX_PARSER_OUTPUT];
    char error[MAX_ERROR];
    parse(regex, postfix_regex, error);
    
    struct nfa *nfa = thompson(postfix_regex, error);
    struct fragment *root = nfa->root;
    int actual = match_string(s, &root->start, &root->end);
    free_nfa(nfa);

    printf("Test case %d: regex=%s, s=%s, expected=%d, got=%d\n", i, regex, s, expected, actual);
    assert(actual == expected);
  }
}
