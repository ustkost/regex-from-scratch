#include <stdio.h>
#include "print.h"
#include "stack.h"

#define MAX_TRANSITION_COUNT 1024

static int is_visited(
  struct state *visited[MAX_TRANSITION_COUNT],
  const struct state *item,
  int visitor_count
) {
  for (int i = 0; i < visitor_count; i++) {
    if (visited[i] == item) return 1;
  }
  return 0;
}

static int get_ind(
  struct state *visited[MAX_TRANSITION_COUNT],
  const struct state *item,
  int visitor_count
) {
  for (int i = 0; i < visitor_count; i++) {
    if (visited[i] == item) return i;
  }
  return -1;
}

void print(const struct fragment *f) {
  struct state *visited[MAX_TRANSITION_COUNT] = {0};
  int visitor_count = 0;
  struct stack *stack = stack_create();
  stack_push(stack, &f->s);

  while (!stack_empty(stack)) {
    struct state *s = stack_pop(stack);
    if (s->t1.to && !is_visited(visited, s->t1.to, visitor_count)) {
      stack_push(stack, s->t1.to);
    }
    if (s->t2.to && !is_visited(visited, s->t2.to, visitor_count)) {
      stack_push(stack, s->t2.to);
    }
    visited[visitor_count++] = s;
  }

  for (int i = 0; i < visitor_count; i++) {
    struct state *s = visited[i];
    printf("addr=%p\n", s);
    if (s == &f->s) printf("(initial)\n");
    if (s == &f->t) printf("(accepting)\n");
    if (s->t1.to) {
      printf(
        "q%d ---%c--> q%d\n",
        i,
        s->t1.sym == EPS ? '~' : s->t1.sym,
        get_ind(visited, s->t1.to, visitor_count)
      );
    }
    if (s->t2.to) {
      printf(
        "q%d ---%c--> q%d\n",
        i,
        s->t2.sym == EPS ? '~' : s->t2.sym,
        get_ind(visited, s->t2.to, visitor_count)
      );
    }
    if (!s->t1.to && !s->t2.to) {
      printf("q%d - no transitions\n", i);
    }
    printf("\n");
  }
}
