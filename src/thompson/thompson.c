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
}

int thompson(const struct token_array *ta, struct nfa *nfa, char *error) {
  struct stack *stack = stack_create();
  nfa->frag_count = 0;

  for (int i = 0; i < ta->size ; i++) {
    struct token t = ta->tokens[i];

    if (t.type == T_LIT) { // frag = 'a'
      struct fragment *frag = create_fragment();
      frag->start.t1 = (struct transition){ .sym = t.val, .to = &frag->end };
      nfa->frags[nfa->frag_count++] = frag;

      stack_push(stack, frag);
    } else if (is_op(t)) {
      switch (t.type) {
        case T_CAT: { // frag = lhs.rhs
          struct fragment *rhs = stack_pop(stack);
          struct fragment *lhs = stack_pop(stack);

          if (!rhs || !lhs) {
            sprintf(error, "thompson: could not retrieve fragments for concatenation");
            free_nfa(nfa);
            free(stack);
            return -1;
          }
          struct fragment *frag = create_fragment();

          frag->start.t1 = (struct transition){ .sym = EPS, .to = &lhs->start };
          lhs->end.t1 = (struct transition){ .sym = EPS, .to = &rhs->start };
          rhs->end.t1 = (struct transition){ .sym = EPS, .to = &frag->end };
          nfa->frags[nfa->frag_count++] = frag;
          stack_push(stack, frag);

          break;
        } case T_OR: { // frag = lhs|rhs
          struct fragment *rhs = stack_pop(stack);
          struct fragment *lhs = stack_pop(stack);
          if (!rhs || !lhs) {
            sprintf(error, "thompson: could not retrieve fragments for union");
            free_nfa(nfa);
            free(stack);
            return -1;
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
        } case T_STAR: { // frag = prev*
          struct fragment *prev = stack_pop(stack);

          if (!prev) {
            sprintf(error, "thompson: could not retrieve fragment for kleene star");
            free_nfa(nfa);
            free(stack);
            return -1;
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
        } default: {
          sprintf(error, "thompson: unsupported operator type");
          free(nfa);
          free(stack);
          return -1;
        }
      }
    } else {
      sprintf(error, "thompson: unknown sym: %c", t.val);
      free_nfa(nfa);
      free(stack);
      return -1;
    }
  }

  struct fragment *res = stack_pop(stack);

  if (!stack_empty(stack) || !res) {
    sprintf(error, "thompson: stack is malformed");
    free_nfa(nfa);
    free(stack);
    return -1;
  }
  nfa->root = res;
  free(stack);
  return 0;
}
