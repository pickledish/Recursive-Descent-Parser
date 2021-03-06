//
// Created by Kyle Edgette on 10/16/16.
//

#ifndef PROJECT_02_MAIN_H
#define PROJECT_02_MAIN_H

typedef enum {	t_none, t_id, t_literal, t_gets, t_add, t_sub, t_mul, t_div, 
              	t_lparen, t_rparen, t_eof, t_let, t_newline,
              	t_SL, t_S, t_D, t_E, t_T, t_F, t_TT, t_FT, t_ao, t_mo} token;

typedef struct list {
    token type;
    char* value;
    struct list* rest;
} list;

typedef struct stack {
	token type;
    char* value;
    struct stack* prev;
} stack;

typedef struct NODE* TREE;

struct NODE {
    char* value;
    TREE leftmostChild, rightSibling;
};

TREE Program(list* tokens);

char* string_from_token(token t);

TREE ProgramTD(list* tokens);

int evaluateParseTree(TREE tree);


TREE findNode(TREE root, token desired);
void printTree(TREE result);

#endif //PROJECT_02_MAIN_H
