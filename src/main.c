#include <string.h>
#include <stdio.h>

#include "state.h"

#define MAX_ACCEPTING_SIZE 1024

int is_accepted(struct state* accepting[], struct State* state) {
  int f = 0;
  for (int i = 0; i < MAX_ACCEPTING_SIZE; i++) {
    if (state == accepting[i]) {
      f = 1;
      break;
    }
  }
  return f;
}

int main() {
  struct state q0;
  struct state q1;
  struct state q2;
  struct state NOT_ACCEPTED; // Sentinel value
  
  q0.symbol = 'a';
  q0.out = &q1;
  q0.eps_out = NULL;
  
  q1.symbol = 'b';
  q1.out = &q2;
  q1.eps_out = NULL;
  
  q2.symbol = '\0'; // I honestly do not know what to put here
  q2.out = NULL;
  q2.eps_out = NULL;
  
  char s[] = "ab";
  int i = 0;
  struct state *state = &q0; // Set to initial state first
  struct state *accepting[MAX_ACCEPTING_SIZE];
  accepting[0] = &q2;

  while (i < strlen(s)) {
    /*
     * Currently a greedy approach is used: if the symbols match,
     * the state changes to `out`. If they do not match, the state
     * changes to `eps_out` instead.
     * In the future, however, we should consider using backtracking
     * or convertation of the NFA to the DFA instead
     */
    if (state->out != NULL && state->symbol == s[i]) {
      state = state->out;
      i++;
    } else if (state->eps_out != NULL) {
      // We do not increment `i` because this is an epsilon transition
      state = state->eps_out;
    } else {
      /*
       * There is still more string left but there is no state
       * to transition into; perhaps you are in a "trap" state?

       * It is possible that `state` is equal to `accepting` when
       * we are exiting the loop. Since such string can not be accepted,
       * it is explicitly marked with `NOT_ACCEPTED` sentinel value
       */
      state = &NOT_ACCEPTED;
      break;
    }
  }
  
  if (is_accepted(accepting, state)) {
    printf("Accepted\n");
  } else {
    printf("Not accepted\n");
  }

  return 0;
}
