#include <string.h>
#include <stdio.h>
#include "match.h"
#include "test.h"

int main(int argc, char **argv) {
  if (argc == 2 && strcmp(argv[1], "test") == 0) {
    test();
    return 0;
  }

  struct state q0, q1, q2, q3, q4, q5, q6, q7;
  
  q0 = (struct state) {
    .t1 = { .sym = EPS, .to = &q1 },
    .t2 = { .sym = EPS, .to = &q7 }
  };

  q1 = (struct state){
    .t1 = { .sym = EPS, .to = &q2 },
    .t2 = { .sym = EPS, .to = &q4 }
  };

  q2 = (struct state) {
    .t1 = { .sym = 'a', .to = &q3 },
    .t2 = { .to = NULL }
  };
  
  q3 = (struct state) {
    .t1 = { .sym = EPS, .to = &q6 },
    .t2 = { .to = NULL }
  };
  
  q4 = (struct state) {
    .t1 = { .sym = 'b', .to = &q5 },
    .t2 = { .to = NULL }
  };
  
  q5 = (struct state) {
    .t1 = { .sym = EPS, .to = &q6 },
    .t2 = { .to = NULL }
  };

  q6 = (struct state) {
    .t1 = { .sym = EPS, .to = &q1 },
    .t2 = { .sym = EPS, .to = &q7 }
  };
  
  q7 = (struct state) {
    .t1 = { .to = NULL },
    .t2 = { .to = NULL }
  };
  
  struct state *initial = &q0;
  struct state *accepting_state = &q7;
  char s[] = "a";
  if (match_string(s, initial, accepting_state)) {
    printf("Accepted\n");
  } else {
    printf("Not accepted\n");
  }

  return 0;
}
