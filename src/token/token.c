#include "token.h"

void token_array_free(struct token_array *ta) {
  free(ta->tokens);
  ta->size = 0;
}

void token_print(struct token *t) {
  printf("TOKEN type=%d; val=%c; pos=%d\n", t->type, t->val, t->pos);
}

void token_array_print(struct token_array *ta) {
  if (ta->size == 0) {
    puts("token array empty\n");
  } else {
    for (int i = 0; i < ta->size; i++) {
      token_print(&ta->tokens[i]);
    }
  }
}
