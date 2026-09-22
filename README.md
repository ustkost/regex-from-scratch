# regex-from-scratch

A simple regular expression engine written in C from scratch.

## Overview

Takes a regex pattern and an input string, and checks if the string matches. Works as a
pipeline:

```
0) get the raw regex string from the input
1) lexer - tokenize the string
2) preproc - insert explicit concatenation tokens: ab becomes a CONCAT b
3) to_postfix - reorder the tokens to postfix notation with [Shunting yard algorithm](https://en.wikipedia.org/wiki/Shunting_yard_algorithm) ('a|b' becomes '|ab')
4) thompson - perform [Thompson's construction](https://en.wikipedia.org/wiki/Thompson%27s_construction) - build [NFA](https://en.wikipedia.org/wiki/Nondeterministic_finite_automaton) from the postfix token array
5) match - run the input string against the NFA, either accept or reject it (uses backtracking)
```

## Supported regex syntax
- `a`, `b`, ... - literals
- `|` - alternation
- `*` - Kleene star
- `(`, `)` - grouping

## Build

```sh
make # writes binary to ./build/regex
```

## Usage

```sh
./build/regex '<pattern>' '<string>'
```

Example:

```sh
$ ./regex 'ab|c' 'ab'
Accepted
$ ./regex 'ab|c' 'd'
Rejected
```

## Project structure

```
src/
├── token/ - token related types commonly used across the project
├── lexer/ - convert raw regex string to token array
├── preproc/ - insert concatenation into token array
├── postfix/ - convert the token array to postfix notation
├── thompson/ - construct the NFA with Thompson's construction
├── print_nfa/ - debug printing for NFAs
├── compile_regex/ - regex compilation pipeline; from lexer to thompson
├── match/ - check if a string is accepted by NFA
├── stack/ - stack data structure used by postfix/thompson
├── test/ - run tests with ./build/regex --test
└── main.c - entrypoint
```

## License
[MIT](./LICENSE)
