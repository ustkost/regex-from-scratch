#ifndef PARSER_H
#define PARSER_H

#define MAX_PARSER_OUTPUT 4096
#define MAX_PARSER_ERROR 256

struct operator {
  char op;
  int prec;
};

int is_lit(char c);
int is_op(char c);
void preprocess(char *regex, char *output);
int parser(char *regex, char *output, char *error);

#endif
