//
// Created by Kyle Edgette on 10/16/16.
//

#ifndef PROJECT_02_MAIN_H
#define PROJECT_02_MAIN_H

typedef enum {t_none, t_id, t_literal, t_gets, t_add, t_sub, t_mul, t_div, t_lparen, t_rparen, t_eof, t_let, t_newline} token;

typedef struct list {
    token type;
    char* value;
    struct list* rest;
} list;

typedef struct NODE* TREE;

struct NODE {
    char* value;
    TREE leftmostChild, rightSibling;
};

TREE Program(list* tokens);



#endif //PROJECT_02_MAIN_H
