# svhl/s7

Make changes to comments, file names, etc. if you're gonna use these.

## Contents

| Day                                                       | Date      | Question                              |
| :-                                                        | :-        | :-                                    |
| [1](https://github.com/svhl/s7/tree/main/day-01)          | 04 Jul '25| Implement a lexical analyzer          |
| [2](https://github.com/svhl/s7/tree/main/day-02)          | 11 Jul '25| Lex programs                          |

## How to use

- C

`cc [filename].c` or `cc [filename].c -o [name]`\
`./a.out` or `./[name].out`

- Lex

`lex [filename].l`\
`cc lex.yy.c -lfl` or `cc lex.yy.c -o [name] -lfl`\
`./a.out` or `./[name]`

- YACC

`yacc -d [filename].y`\
`flex [filename].l`\
`cc y.tab.c lex.yy.c -lfl` or `cc y.tab.c lex.yy.c -o [name] -lfl`\
`./a.out` or `./[name]`
