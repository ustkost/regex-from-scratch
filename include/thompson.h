#ifndef THOMPSON_H
#define THOMPSON_H

#define EPS 256

struct transition {
  int sym;
  struct state *to;
};

struct state {
  struct transition t1;
  struct transition t2;
};

struct fragment {
  struct state s;
  struct state t;
};

struct fragment *thompson(const char *postfix_regex);

#endif
