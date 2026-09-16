#include "print.h"

#define MAX_STATE_COUNT 1024

static int is_visited(
  struct state *visited[MAX_STATE_COUNT],
  const struct state *item,
  int visitor_count
) {
  for (int i = 0; i < visitor_count; i++) {
    if (visited[i] == item) return 1;
  }
  return 0;
}

static int get_ind(
  struct state *visited[MAX_STATE_COUNT],
  const struct state *item,
  int visitor_count
) {
  for (int i = 0; i < visitor_count; i++) {
    if (visited[i] == item) return i;
  }
  return -1;
}

void print(const struct fragment *frag) {
  struct state *visited[MAX_STATE_COUNT] = {0};
  int visitor_count = 0;
  struct stack *stack = stack_create();
  stack_push(stack, &frag->start);

  while (!stack_empty(stack)) {
    struct state *state = stack_pop(stack);
    visited[visitor_count++] = state;
    if (visitor_count >= MAX_STATE_COUNT) {
      printf("print: state count exceeded maximum of %d\n", MAX_STATE_COUNT);
      free(stack);
      return;
    }
    if (state->t1.to && !is_visited(visited, state->t1.to, visitor_count)) {
      stack_push(stack, state->t1.to);
    }
    if (state->t2.to && !is_visited(visited, state->t2.to, visitor_count)) {
      stack_push(stack, state->t2.to);
    }
  }

  for (int i = 0; i < visitor_count; i++) {
    struct state *state = visited[i];
    if (state == &frag->start) printf("(initial)\n");
    if (state == &frag->end) printf("(accepting)\n");
    if (state->t1.to) {
      printf(
        "q%d ---%c--> q%d\n",
        i,
        state->t1.sym == EPS ? '~' : state->t1.sym,
        get_ind(visited, state->t1.to, visitor_count)
      );
    }
    if (state->t2.to) {
      printf(
        "q%d ---%c--> q%d\n",
        i,
        state->t2.sym == EPS ? '~' : state->t2.sym,
        get_ind(visited, state->t2.to, visitor_count)
      );
    }
    if (!state->t1.to && !state->t2.to) {
      printf("q%d - no transitions\n", i);
    }
    printf("\n");
  }

  free(stack);
}
