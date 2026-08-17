#include <string.h>
#include <stdio.h>
#include "match.h"

int main() {
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
  
  char s[] = "ab";
  struct state *initial = &q0;
  struct state *accepting_states[MAX_ACCEPTING_SIZE];
  accepting_states[0] = &q2;

  if (match_string(s, initial, accepting_states)) {
    printf("Accepted\n");
  } else {
    printf("Not accepted\n");
  }

  return 0;
}
