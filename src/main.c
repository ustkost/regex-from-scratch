#include <string.h>
#include <stdio.h>
#include "match.h"
#include "test.h"

int main(int argc, char **argv) {
  if (argc == 2 && strcmp(argv[1], "test") == 0) {
    test();
    return 0;
  }

  struct state q0;
  struct state q1;
  struct state q2;
  struct state q3;
  
  q0.symbol = 'a';
  q0.out = &q1;
  q0.eps_out = &q2;

  q1.out = NULL;
  q1.eps_out = NULL;

  q2.symbol = 'b';
  q2.out = &q3;
  q2.eps_out = NULL;

  q3.out = NULL;
  q3.eps_out = NULL;
  
  struct state *initial = &q0;
  struct state *accepting_states[MAX_ACCEPTING_SIZE] = {0};
  accepting_states[0] = &q1;
  accepting_states[1] = &q3;

  char s[] = "a";
  if (match_string(s, initial, accepting_states)) {
    printf("Accepted\n");
  } else {
    printf("Not accepted\n");
  }

  return 0;
}
