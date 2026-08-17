#ifndef MATCH_H
#define MATCH_H

#define EPS 256

struct transition {
  int sym;
  struct state *to;
};

struct state {
  struct transition t1;
  struct transition t2;
};

int match_string(char s[], struct state *initial, struct state *accepting_state);

#endif
