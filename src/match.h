#ifndef MATCH_H
#define MATCH_H

#define MAX_ACCEPTING_SIZE 1024

struct state {
  char symbol;
  struct state *out;
  struct state *eps_out;
};

int match_string(
  char s[],
  struct state *initial,
  struct state *accepting_states[MAX_ACCEPTING_SIZE]
);

#endif
