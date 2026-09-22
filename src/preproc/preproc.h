#ifndef PREPROC_H
#define PREPROC_H

#include <stdlib.h>
#include "../token/token.h"

int preproc(const struct token_array *src, struct token_array *dst, char *error);

#endif
