#ifndef PARSER_H
#define PARSER_H

#define MAX_PARSER_OUTPUT 4096
#define MAX_PARSER_ERROR 256

void preprocess(char *regex, char *output);
int parser(char *regex, char *output, char *error);

#endif
