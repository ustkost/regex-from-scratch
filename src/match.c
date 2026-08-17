#include <string.h>
#include "match.h"
#include "stack.h"

int state_accepted(struct state *state, struct state *accepting_states[]) {
  int f = 0;
  for (int i = 0; i < MAX_ACCEPTING_SIZE; i++) {
    if (state == accepting_states[i]) {
      f = 1;
      break;
    }
  }
  return f;
}

int match_string(
  char s[],
  struct state *state,
  struct state *accepting_states[MAX_ACCEPTING_SIZE]
) {
  int i = 0;
  struct state NOT_ACCEPTED; // Sentinel value
  struct stack *stack = stack_create();

  while (i < strlen(s)) {
    /*
     * First try to change the state to `out` (and save `eps_out`
     * for backtracking), then try to change the state to `eps_out`
     * If none of that worked, try to backtrack. If the stack is empty,
     * exit the loop as the string is not accepted
     */
    if (state->out != NULL && state->symbol == s[i]) {
      if (state->eps_out != NULL) {
        stack_push(stack, stack_item_create(i, state->eps_out));
      }
      state = state->out;
      i++;

      if (i == strlen(s)) {
        if (state_accepted(state, accepting_states) || stack_size(stack) == 0) {
          break;
        } else {
          // Backtracking
          struct stack_item *stack_item = stack_pop(stack);
          state = stack_item->state;
          i = stack_item->i;
        }
      }
    } else if (state->eps_out != NULL) {
      // We do not increment `i` because this is an epsilon transition
      state = state->eps_out;
    } else {
      /*
       * There is still more string left but there is no state
       * to transition into; perhaps you are in a "trap" state?

       * It is possible that `state` is in `accepting_states` when
       * we are exiting the loop. Since such string can not be accepted,
       * it is explicitly marked with `NOT_ACCEPTED` sentinel value
       */
      if (stack_size(stack) == 0) {
        state = &NOT_ACCEPTED;
        break;
      }

      // Backtracking
      struct stack_item *stack_item = stack_pop(stack);
      state = stack_item->state;
      i = stack_item->i;
    }
  }

  stack_free(stack);

  return state_accepted(state, accepting_states);
}
