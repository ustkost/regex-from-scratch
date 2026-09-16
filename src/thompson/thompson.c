#include "thompson.h"

static struct fragment *create_fragment() {
  struct fragment *frag = malloc(sizeof(struct fragment));
  frag->start = (struct state){
    .t1 = { .to = NULL },
    .t2 = { .to = NULL }
  };
  frag->end = (struct state){
    .t1 = { .to = NULL },
    .t2 = { .to = NULL }
  };
  return frag;
}

void free_nfa(struct nfa *nfa) {
  for (int i = 0; i < nfa->frag_count; i++) {
    free(nfa->frags[i]);
  }
  free(nfa);
}

struct nfa *thompson(const char *postfix_regex, char *error) {
  struct stack *stack = stack_create();
  struct nfa *nfa = malloc(sizeof(struct nfa));
  nfa->frag_count = 0;

  for (int i = 0; postfix_regex[i] != '\0'; i++) {
    char c = postfix_regex[i];

    if (is_lit(c)) { // frag = 'a'
      struct fragment *frag = create_fragment();
      frag->start.t1 = (struct transition){ .sym = c, .to = &frag->end };
      nfa->frags[nfa->frag_count++] = frag;

      stack_push(stack, frag);
    } else if (is_op(c)) {
      switch (c) {
        case '.': { // frag = lhs.rhs
          struct fragment *rhs = stack_pop(stack);
          struct fragment *lhs = stack_pop(stack);

          if (!rhs || !lhs) {
            sprintf(error, "thompson: could not retrieve fragments for concatenation");
            free_nfa(nfa);
            free(stack);
            return NULL;
          }
          struct fragment *frag = create_fragment();

          frag->start.t1 = (struct transition){ .sym = EPS, .to = &lhs->start };
          lhs->end.t1 = (struct transition){ .sym = EPS, .to = &rhs->start };
          rhs->end.t1 = (struct transition){ .sym = EPS, .to = &frag->end };
          nfa->frags[nfa->frag_count++] = frag;
          stack_push(stack, frag);

          break;
        } case '|': { // frag = lhs|rhs
          struct fragment *rhs = stack_pop(stack);
          struct fragment *lhs = stack_pop(stack);
          if (!rhs || !lhs) {
            sprintf(error, "thompson: could not retrieve fragments for union");
            free_nfa(nfa);
            free(stack);
            return NULL;
          }
          struct fragment *frag = create_fragment();

          frag->start = (struct state){
            .t1 = { .sym = EPS, .to = &lhs->start },
            .t2 = { .sym = EPS, .to = &rhs->start }
          };

          lhs->end.t1 = (struct transition){ .sym = EPS, .to = &frag->end };
          rhs->end.t1 = (struct transition){ .sym = EPS, .to = &frag->end };
          nfa->frags[nfa->frag_count++] = frag;
          stack_push(stack, frag);

          break;
        } case '*': { // frag = prev*
          struct fragment *prev = stack_pop(stack);

          if (!prev) {
            sprintf(error, "thompson: could not retrieve fragment for kleene star");
            free_nfa(nfa);
            free(stack);
            return NULL;
          }
          struct fragment *frag = create_fragment();

          frag->start = (struct state){
            .t1 = { .sym = EPS, .to = &prev->start },
            .t2 = { .sym = EPS, .to = &frag->end }
          };

          prev->end = (struct state){
            .t1 = { .sym = EPS, .to = &prev->start },
            .t2 = { .sym = EPS, .to = &frag->end }
          };
          nfa->frags[nfa->frag_count++] = frag;
          stack_push(stack, frag);

          break;
        }
      }
    } else {
      sprintf(error, "thompson: unknown sym: %c", c);
      free_nfa(nfa);
      free(stack);
      return NULL;
    }
  }



  struct fragment *res = stack_pop(stack);

  if (!stack_empty(stack) || !res) {
      sprintf(error, "thompson: stack is malformed");
      free_nfa(nfa);
      free(stack);
      return NULL;
  }
  nfa->root = res;
  free(stack);
  return nfa;
}
