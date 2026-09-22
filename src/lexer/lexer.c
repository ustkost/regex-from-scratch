#include "lexer.h"

int lexer(const char *src, struct token_array *dst, char *error) {
  dst->tokens = malloc(sizeof(struct token) * strlen(src));
  dst->size = 0;

  for (int i = 0; src[i] != '\0'; i++) {
    char c = src[i];

    dst->tokens[i].val = c;
    dst->tokens[i].pos =  i + 1;

    switch (c) {
      case '(':
        dst->tokens[i].type = T_LPAR;
        break;
      case ')':
        dst->tokens[i].type = T_RPAR;
        break;
      case '*':
        dst->tokens[i].type = T_STAR;
        break;
      case '|':
        dst->tokens[i].type = T_OR;
        break;
      default:
        dst->tokens[i].type = T_LIT;
        break;
    }
  }

  dst->size = strlen(src);

  return 0;
}
