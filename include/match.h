#ifndef MATCH_H
#define MATCH_H

#include "thompson.h"

int match_string(
  const char s[],
  const struct state *initial,
  const struct state *accepting_state
);

#endif
