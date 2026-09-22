#include "compile_regex.h"

int regex_to_nfa(const char *regex, struct nfa *nfa, char error[MAX_ERROR]) {
  struct token_array raw_tokens = {0};
  struct token_array processed = {0};
  struct token_array postfix = {0};
  int ret = 1;

  if (lexer(regex, &raw_tokens, error) != 0) goto cleanup;
  if (preproc(&raw_tokens, &processed, error) != 0) goto cleanup;
  if (to_postfix(&processed, &postfix, error) != 0) goto cleanup;
  if (thompson(&postfix, nfa, error) != 0) goto cleanup;
  ret = 0;

cleanup:
  token_array_free(&raw_tokens);
  token_array_free(&processed);
  token_array_free(&postfix);
  return ret;
}
