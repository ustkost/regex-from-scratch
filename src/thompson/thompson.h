#ifndef THOMPSON_H
#define THOMPSON_H

#define EPS 256
#define MAX_FRAG_COUNT 1024

#include <stdlib.h>
#include <stdio.h>
#include "../token/token.h"
#include "../stack/stack.h"
#include "../postfix/postfix.h"

struct transition {
  int sym;
  struct state *to;
};

struct state {
  struct transition t1;
  struct transition t2;
};

struct fragment {
  struct state start;
  struct state end;
};

struct nfa {
  struct fragment *root;
  struct fragment *frags[MAX_FRAG_COUNT];
  int frag_count;
};

void free_nfa(struct nfa *nfa);
int thompson(const struct token_array *ta, struct nfa *nfa, char *error);

#endif
