#include <string.h>
#include "match.h"
#include "stack.h"

int can_take(struct transition t, char s[], int i) {
  if (!t.to) return 0;
  if (t.sym == EPS) return 1;
  return i < strlen(s) && t.sym == s[i];
}

int match_string(char s[], struct state *state, struct state *accepting_state) {
  int i = 0;
  struct state NOT_ACCEPTED = {0};
  struct stack *stack = stack_create();

  while (1) {
    struct transition t1 = state->t1;
    struct transition t2 = state->t2;

    if (can_take(t1, s, i)) {
      state = t1.to;
      if (i < strlen(s) && t1.sym == s[i]) i++;
      stack_push(stack, stack_item_create(i, t2.to));

    } else if (can_take(t2, s, i)) {
      state = t2.to;
      if (i < strlen(s) && t2.sym == s[i]) i++;

    } else {
      if (i == strlen(s) && state == accepting_state) break;
      if (stack_size(stack) == 0) {
        state = &NOT_ACCEPTED;
        break;
      }

      struct stack_item *stack_item = stack_pop(stack);
      state = stack_item->state;
      i = stack_item->i;
    }
  }

  stack_free(stack);
  return state == accepting_state;
}
