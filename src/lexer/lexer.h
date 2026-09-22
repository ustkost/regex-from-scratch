#ifndef LEXER_H
#define LEXER_H

#include <string.h>
#include "../token/token.h"

int lexer(const char *src, struct token_array *dst, char *error);

#endif
