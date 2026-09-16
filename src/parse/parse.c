#include "parse.h"

struct operator {
  char op;
  int prec;
};

struct operator ops[] = {
  {'*', 3},
  {'.', 2},
  {'|', 1}
};

int is_op(char c) {
  for (int i = 0; i < sizeof(ops)/sizeof(ops[0]); i++) {
    if (c == ops[i].op) return 1;
  }
  return 0;
}

int is_lit(char c) {
  return !is_op(c) && c != '(' && c != ')';
}

static int get_op_prec(char c) {
 for (int i = 0; i < sizeof(ops)/sizeof(ops[0]); i++) {
    if (c == ops[i].op) {
      return ops[i].prec;
    }
  }
  return -1;
}

static int can_start_expr(char c) {
  return is_lit(c) || c == '(';
}

static int can_end_expr(char c) {
  return is_lit(c) || c == ')' || c == '*';
}

int preprocess(const char *regex, char *output, char *error) {
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

  if (j >= MAX_PARSER_OUTPUT) {
    sprintf(error, "preprocess: result string length (%d) exceeded maximum value (%d)", j, MAX_PARSER_OUTPUT);
    return -1;
  }
  return 0;
}

static char peek_char(const struct stack *s) {
  return *(char*)stack_peek(s);
}

static char pop_char(struct stack *s) {
  return *(char*)stack_pop(s);
}

int parse(const char *regex, char *output, char *error) {
  int j = 0;
  char s[MAX_PARSER_OUTPUT];
  int preproc_status = preprocess(regex, s, error);
  if (preproc_status == -1) {
    return -1;
  }
  struct stack *stack = stack_create();

  for (int i = 0; s[i] != '\0'; i++) {
    char c = s[i];
    if (is_lit(c)) {
      output[j++] = c;
    } else if (is_op(c)) {
      while (
        !stack_empty(stack) &&
        is_op(peek_char(stack)) &&
        get_op_prec(peek_char(stack)) >= get_op_prec(c)
      ) {
        output[j++] = pop_char(stack);
      }
      stack_push(stack, &s[i]);
    } else if (c == '(') {
      stack_push(stack, &s[i]);
    } else if (c == ')') {
      while (!stack_empty(stack) && peek_char(stack) != '(') {
        output[j++] = pop_char(stack);
      }
      if (!stack_empty(stack) && peek_char(stack) == '(') {
        stack_pop(stack);
      } else {
        sprintf(error, "parse: unmatched ')' at position %d", i);
        free(stack);
        return -1;
      }
    }
  }

  while (!stack_empty(stack)) {
    char c = pop_char(stack);
    if (c == '(') {
      sprintf(error, "parse: unmatched '(' (unclosed at the end of expression)");
      free(stack);
      return -1;
    }
    output[j++] = c;
  }

  output[j] = '\0';
  free(stack);

  if (j >= MAX_PARSER_OUTPUT) {
    sprintf(error, "parse: result string length (%d) exceeded maximum value (%d)", j, MAX_PARSER_OUTPUT);
    return -1;
  }
  return 0;
}
