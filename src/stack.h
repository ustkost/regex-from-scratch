#ifndef STACK_H
#define STACK_H

#include "match.h"

#define MAX_STACK_SIZE 4096

struct backtrack_entry {
  struct state *state;
  int i;
};

struct backtrack_entry *backtrack_entry_create(int i, struct state *state);

struct stack {
  void *items[MAX_STACK_SIZE];
  int top;
  void *to_free[MAX_STACK_SIZE];
  int to_free_top;
};

struct stack *stack_create();
void stack_push(struct stack *stack, void *item);
void *stack_pop(struct stack *stack);
void *stack_peek(struct stack *stack);
int stack_empty(struct stack *stack);
void stack_free_items(struct stack *stack);

#endif
