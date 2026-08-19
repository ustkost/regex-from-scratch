#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "match.h"
#include "test.h"
#include "parser.h"
#include "thompson.h"
#include "print.h"

int main(int argc, char **argv) {
  if (argc == 2 && strcmp(argv[1], "--test") == 0) {
    test();
    return 0;
  } else if (argc == 3) {
    char *regex = argv[1];
    char *s = argv[2];

    char postfix_regex[MAX_PARSER_OUTPUT];
    char error[MAX_PARSER_ERROR];
    int i = parser(regex, postfix_regex, error);
    if (i == -1) {
      printf("%s\n", error);
      return 1;
    }

    struct nfa *nfa = thompson(postfix_regex);
    struct fragment *root = nfa->root;
    print(root);

    int res = match_string(s, &root->start, &root->end);
    if (res) {
      printf("Accepted\n");
    } else {
      printf("Rejected\n");
    }
    
    free_nfa(nfa);
  } else {
    printf("usage something bla bla\n");
  } 
  return 0;
}
