#include <string.h>
#include <stdio.h>
#include "match.h"
#include "test.h"
#include "parser.h"

int main(int argc, char **argv) {
  if (argc == 2 && strcmp(argv[1], "test") == 0) {
    test();
    return 0;
  }

  char tst[] = "a|b";
  char res[1024];
  // parser(tst, res);
  // printf("%s\n", res);
  
  return 0;
}
