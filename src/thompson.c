#include <stdlib.h>
#include <stdio.h>
#include "match.h"
#include "stack.h"
#include "parser.h"
#include "thompson.h"

struct fragment {
  struct state s;
  struct state t;
};

struct fragment *create_fragment() {
  struct fragment *f = malloc(sizeof(struct fragment));
  f->s = (struct state){
    .t1 = { .to = NULL },
    .t2 = { .to = NULL }
  };
  f->t = (struct state){
    .t1 = { .to = NULL },
    .t2 = { .to = NULL }
  };
  return f;
}

struct fragment *thompson(const char *postfix_regex) {
  struct stack *stack = stack_create();
  for (int i = 0; postfix_regex[i] != '\0'; i++) {
    char c = postfix_regex[i];
    if (is_lit(c)) {
      // printf("hi im lit\n");
      struct fragment *f = create_fragment();
      f->s.t1 = (struct transition){ .sym = c, .to = &f->t };
      stack_push(stack, f);
    } else if (is_op(c)) {
      switch (c) {
        case '.': {
          // printf("this case\n");
          struct fragment *rhs = stack_pop(stack);
          struct fragment *lhs = stack_pop(stack);
          struct fragment *f = create_fragment();

          f->s.t1 = (struct transition){ .sym = EPS, .to = &lhs->s };
          lhs->t.t1 = (struct transition){ .sym = EPS, .to = &rhs->s };
          rhs->t.t1 = (struct transition){ .sym = EPS, .to = &f->t };
          stack_push(stack, f);
          break;
        } case '|': {
          // printf("that case\n");
          struct fragment *rhs = stack_pop(stack);
          struct fragment *lhs = stack_pop(stack);
          struct fragment *f = create_fragment();

          f->s = (struct state){
            .t1 = { .sym = EPS, .to = &lhs->s },
            .t2 = { .sym = EPS, .to = &rhs->s }
          };

          lhs->t.t1 = (struct transition){ .sym = EPS, .to = &f->t };
          rhs->t.t1 = (struct transition){ .sym = EPS, .to = &f->t };
          stack_push(stack, f);
          break;
        } case '*': {
          // printf(" case 3\n");
          struct fragment *p = stack_pop(stack);
          struct fragment *f = create_fragment();
          
          f->s = (struct state){
            .t1 = { .sym = EPS, .to = &p->s },
            .t2 = { .sym = EPS, .to = &f->t }
          };

          p->t = (struct state){
            .t1 = { .sym = EPS, .to = &p->s },
            .t2 = { .sym = EPS, .to = &f->t }
          };
          stack_push(stack, f);
          break;
        }
      }
    } else {
      printf("something is wrong i think\n");
    }
  }

  struct fragment *res = stack_pop(stack);
  free(stack);
  return res;
}
