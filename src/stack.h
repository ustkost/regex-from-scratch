#ifndef STACK_H
#define STACK_H

#include "match.h"

#define MAX_STACK_SIZE 4096

struct stack_item {
  struct state *state;
  int i;
};

struct stack_item *stack_item_create(int, struct state*);

struct stack {
  struct stack_item *items[MAX_STACK_SIZE];
  int top;
  int capacity;
};

struct stack *stack_create();
void stack_push(struct stack*, struct stack_item*);
struct stack_item *stack_pop(struct stack*);
int stack_size(struct stack*);
void stack_free(struct stack*);

#endif
