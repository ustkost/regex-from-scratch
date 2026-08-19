#ifndef PARSER_H
#define PARSER_H

#define MAX_PARSER_OUTPUT 4096
#define MAX_PARSER_ERROR 256

int is_lit(char c);
int is_op(char c);
void preprocess(const char *regex, char *output);
int parser(const char *regex, char *output, char *error);

#endif
