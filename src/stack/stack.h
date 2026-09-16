#ifndef STACK_H
#define STACK_H

#define MAX_STACK_SIZE 4096
#define DEBUG 1

#include <stdlib.h>
#include <stdio.h>

struct stack {
  void *items[MAX_STACK_SIZE];
  int top;
};

struct stack *stack_create();
void stack_push(struct stack *stack, const void *item);
void *stack_pop(struct stack *stack);
void *stack_peek(const struct stack *stack);
void stack_free_items(struct stack *stack);
int stack_empty(const struct stack *stack);

#endif
