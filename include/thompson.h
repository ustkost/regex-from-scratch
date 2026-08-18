#ifndef THOMPSON_H
#define THOMPSON_H

#include "match.h"

struct fragment {
  struct state s;
  struct state t;
};

struct fragment *thompson(const char *postfix_regex);

#endif
