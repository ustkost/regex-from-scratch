#include <string.h>
#include <stdio.h>
#include "match/match.h"
#include "compile_regex/compile_regex.h"
#include "print_nfa/print_nfa.h"
// #include "../test/test.h"

int main(int argc, char *argv[]) {
  if (argc == 2 && strcmp(argv[1], "--test") == 0) {
    // test();
    return 0;
  } else if (argc == 3) {
    char *regex = argv[1];
    char *str = argv[2];
    char error[MAX_ERROR];
 
    struct nfa nfa = {0};
    if (regex_to_nfa(regex, &nfa, error) != 0) {
      fprintf(stderr, "%s\n", error);
      free_nfa(&nfa);
      return 1;
    }
    struct fragment *root = nfa.root;
    print_nfa(root);

    int res = match_string(str, &root->start, &root->end);
    if (res) {
      printf("Accepted\n");
    } else {
      printf("Rejected\n");
    }

    free_nfa(&nfa);
    return 0;
  } else {
    fprintf(stderr, "usage: %s <regex> <string>\n", argv[0]);
    return 1;
  }
}
