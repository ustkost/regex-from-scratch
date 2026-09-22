#include "preproc.h"

int can_start_expr(struct token t) {
  enum token_type toks[] = {T_LIT, T_LPAR};
  for (int i = 0; i < sizeof(toks)/sizeof(toks[0]); i++) {
    if (t.type == toks[i]) {
      return 1;
    }
  }
  return 0;
}

int can_end_expr(struct token t) {
  enum token_type toks[] = {T_LIT, T_RPAR, T_STAR};
  for (int i = 0; i < sizeof(toks)/sizeof(toks[0]); i++) {
    if (t.type == toks[i]) {
      return 1;
    }
  }
  return 0;
}

int preproc(const struct token_array *src, struct token_array *dst, char *error) {
  dst->tokens = malloc(sizeof(struct token_array) * src->size * 2);

  int i = 0;
  int j = 0;
  while (i < src->size) {
    if (j && can_end_expr(dst->tokens[j - 1]) && can_start_expr(src->tokens[i])) {
      dst->tokens[j++] = (struct token){.type = T_CAT};
    }
    dst->tokens[j++] = src->tokens[i++];
  }
  dst->size = j;

  return 0;
}
