#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <stdlib.h>

enum token_type {
  T_LPAR,
  T_RPAR,
  T_STAR,
  T_OR,
  T_CAT,
  T_LIT,
};

struct token {
  enum token_type type;
  char val;
  int pos;
};

struct token_array {
  struct token *tokens;
  int size;
};

void token_array_free(struct token_array *ta);
void token_array_print(struct token_array *ta);
void token_print(struct token *t);

#endif
