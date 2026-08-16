#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

struct stack_item *stack_item_create(int i, struct state *state) {
  struct stack_item *stack_item = malloc(sizeof(struct stack_item));
  stack_item->i = i;
  stack_item->state = state;
  return stack_item;
}

struct stack *stack_create() {
  struct stack *stack = malloc(sizeof(struct stack));
  stack->top = 0;
  stack->capacity = MAX_STACK_SIZE - 1;
  return stack;
}

void stack_push(struct stack *stack, struct stack_item *item) {
  if (stack->top == stack->capacity) {
    printf("stack_push: stack is full");
    return;
  }
  stack->items[stack->top++] = item;
}

struct stack_item *stack_pop(struct stack *stack) {
  if (stack->top == 0) {
    printf("stack_pop: stack is empty");
    return NULL;
  }
  return stack->items[--stack->top];
}

int stack_size(struct stack *stack) {
  return stack->top;
}

void stack_free(struct stack *stack) {
  for (int i = 0; i < stack->top; i++) {
    free(stack->items[i]);
  }
  free(stack);
}
