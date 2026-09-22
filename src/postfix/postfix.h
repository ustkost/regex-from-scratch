#ifndef PARSER_H
#define PARSER_H

#define MAX_ERROR 256

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../stack/stack.h"
#include "../token/token.h"

int is_op(struct token t);
int to_postfix(const struct token_array *src, struct token_array *dst, char *error);

#endif
