#ifndef STATE_H
#define STATE_H

struct state {
    char symbol;
    struct state *out;
    struct state *eps_out;
};

#endif
