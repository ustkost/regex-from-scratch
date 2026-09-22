#include "postfix.h"

struct operator {
  enum token_type op;
  int prec;
};

struct operator ops[] = {{T_STAR, 3}, {T_CAT, 2}, {T_OR, 1}};

int is_op(struct token t) {
  for (int i = 0; i < sizeof(ops) / sizeof(ops[0]); i++) {
    if (t.type == ops[i].op) return 1;
  }
  return 0;
}

static int get_op_prec(struct token t) {
  for (int i = 0; i < sizeof(ops) / sizeof(ops[0]); i++) {
    if (t.type == ops[i].op) {
      return ops[i].prec;
    }
  }
  return -1;
}

static struct token peek_token(const struct stack *s) {
  return *(struct token *)stack_peek(s);
}

static struct token pop_token(struct stack *s) {
  return *(struct token *)stack_pop(s);
}

int to_postfix(const struct token_array *src, struct token_array *dst,
               char *error) {
  int j = 0;
  dst->tokens = malloc(sizeof(struct token) * src->size);

  struct stack *stack = stack_create();

  for (int i = 0; i < src->size; i++) {
    dst->size = j;
    struct token t = src->tokens[i];

    if (t.type == T_LIT) {
      dst->tokens[j++] = t;
    } else if (is_op(t)) {
      while (!stack_empty(stack) && is_op(peek_token(stack)) &&
             get_op_prec(peek_token(stack)) >= get_op_prec(t)) {
        dst->tokens[j++] = pop_token(stack);
      }
      stack_push(stack, &src->tokens[i]);
    } else if (t.type == T_LPAR) {
      stack_push(stack, &src->tokens[i]);
    } else if (t.type == T_RPAR) {
      while (!stack_empty(stack) && peek_token(stack).type != T_LPAR) {
        dst->tokens[j++] = pop_token(stack);
      }
      if (!stack_empty(stack) && peek_token(stack).type == T_LPAR) {
        stack_pop(stack);
      } else {
        sprintf(error, "parse: unmatched ')' at position %d", t.pos);
        free(stack);
        return -1;
      }
    }
  }

  while (!stack_empty(stack)) {
    struct token t = pop_token(stack);
    if (t.type == T_LPAR) {
      sprintf(error, "parse: unmatched '(' at position %d", t.pos);
      free(stack);
      return -1;
    }
    dst->tokens[j++] = t;
  }

  dst->size = j;
  free(stack);
  return 0;
}
