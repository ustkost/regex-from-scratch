#include "stack.h"

struct stack *stack_create() {
  struct stack *stack = malloc(sizeof(struct stack));
  stack->top = 0;
  return stack;
}

void stack_push(struct stack *stack, const void *item) {
  if (stack->top == MAX_STACK_SIZE - 1) {
    if (DEBUG) {
      printf("stack_push: stack is full\n");
    }
    return;
  }
  stack->items[stack->top++] = item;
}

void *stack_pop(struct stack *stack) {
  if (stack->top == 0) {
    if (DEBUG) {
      printf("stack_pop: stack is empty\n");
    }
    return NULL;
  }
  return stack->items[--stack->top];
}

void *stack_peek(const struct stack *stack) {
  if (stack->top == 0) {
    if (DEBUG) {
      printf("stack_peek: stack is empty\n");
    }
    return NULL;
  }
  return stack->items[stack->top - 1];
}

void stack_free_items(struct stack *stack) {
  for (int i = 0; i < stack->top; i++) {
    free(stack->items[i]);
  }
}

int stack_empty(const struct stack *stack) { return stack->top == 0; }
