#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "parser.h"

#define ARRAY_SIZE(x) ((sizeof x) / (sizeof *x))

struct operator {
  char op;
  int prec;
};

struct operator operators[] = {
  {'*', 3},
  {'.', 2},
  {'|', 1}
};

int is_lit(char c) {
  char non_literals[] = "*.|()";
  for (int i = 0; non_literals[i] != '\0'; i++) {
    if (c == non_literals[i]) return 0;
  }
  return 1;
}

int is_op(char c) {
  for (int i = 0; i < ARRAY_SIZE(operators); i++) {
    if (c == operators[i].op) return 1;
  }
  return 0;
}

int op_prec(char c) {
 for (int i = 0; i < ARRAY_SIZE(operators); i++) {
    if (c == operators[i].op) {
      return operators[i].prec;
    }
  }
  return -1;
}

int can_start_expr(char c) {
  return is_lit(c) || c == '(';
}

int can_end_expr(char c) {
  return is_lit(c) || c == ')' || c == '*';
}

void preprocess(char *regex, char *output) {
  int j = 0;
  for (int i = 0; regex[i] != '\0'; i++) {
    char current = regex[i];
    char next = regex[i + 1];
    output[j++] = current;
    
    if (
      next != '\0' &&
      can_end_expr(current) &&
      can_start_expr(next)
    ) {
      output[j++] = '.';
    }
  }
  output[j] = '\0';
}

char stack_peek_char(struct stack *s) {
  return *(char*)stack_peek(s);
}
char stack_pop_char(struct stack *s) {
  return *(char*)stack_pop(s);
}

int parser(char *regex, char *output, char *error) {
  int j = 0;
  char s[MAX_PARSER_OUTPUT];
  preprocess(regex, s);
  struct stack *stack = stack_create();

  for (int i = 0; s[i] != '\0'; i++) {
    char c = s[i];
    if (is_lit(c)) {
      output[j++] = c;
    } else if (is_op(c)) {
      while (
        !stack_empty(stack) &&
        is_op(stack_peek_char(stack)) &&
        op_prec(stack_peek_char(stack)) >= op_prec(c)
      ) {
        output[j++] = stack_pop_char(stack);
      }
      stack_push(stack, &s[i]);
    } else if (c == '(') {
      stack_push(stack, &s[i]);
    } else if (c == ')') {
      while (!stack_empty(stack) && stack_peek_char(stack) != '(') {
        output[j++] = stack_pop_char(stack);
      }
      if (!stack_empty(stack) && stack_peek_char(stack) == '(') {
        stack_pop(stack);
      } else {
        sprintf(error, "unmatched ')' at position %d", i);
        free(stack);
        return -1;
      }
    }
  }
  
  while (!stack_empty(stack)) {
    char c = stack_pop_char(stack);
    if (c == '(') {
      sprintf(error, "unmatched '(' (unclosed at the end of expression)");
      free(stack);
      return -1;
    }
    output[j++] = c;
  }
  output[j] = '\0';

  free(stack);
  return 0;
}
