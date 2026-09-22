#ifndef REGEX_H
#define REGEX_H

#include "../token/token.h"
#include "../lexer/lexer.h"
#include "../preproc/preproc.h"
#include "../postfix/postfix.h"
#include "../thompson/thompson.h"

int regex_to_nfa(const char *regex, struct nfa *nfa, char error[MAX_ERROR]);

#endif
