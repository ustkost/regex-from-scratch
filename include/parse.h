#ifndef PARSER_H
#define PARSER_H

#define MAX_PARSER_OUTPUT 4096
#define MAX_ERROR 256

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int is_lit(char c);
int is_op(char c);
int preprocess(const char *regex, char *output, char *error);
int parse(const char *regex, char *output, char *error);

#endif
