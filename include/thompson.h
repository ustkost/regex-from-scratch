#ifndef THOMPSON_H
#define THOMPSON_H

#define EPS 256
#define MAX_FRAG_COUNT 1024

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "parse.h"

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
struct nfa *thompson(const char *postfix_regex, char *error);

#endif
