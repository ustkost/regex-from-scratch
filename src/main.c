#include <string.h>
#include <stdio.h>
#include "match.h"
#include "test.h"
#include "parser.h"
#include "thompson.h"
#include "print.h"

int main(int argc, char **argv) {
  if (argc == 2 && strcmp(argv[1], "test") == 0) {
    test();
    return 0;
  }

  char regex[] = "ab";
  char postfix_regex[MAX_PARSER_OUTPUT];
  char error[MAX_PARSER_ERROR];
  int i = parser(regex, postfix_regex, error);
  if (i == -1) {
    printf("%s\n", error);
    return 1;
  }

  struct fragment *f = thompson(postfix_regex);
  print(f);

  char s[] = "ab";
  int res = match_string(s, &f->s, &f->t);
  if (res) {
    printf("Accepts\n");
  } else {
    printf("Rejects\n");
  }
  return 0;
}
