//
// Created by Manan hora on 10/17/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"

char* string_from_token(token t) {
    switch(t) {
        case (t_SL): return "t_SL";
        case (t_S): return "t_S";
        case (t_D): return "t_D";
        case (t_E): return "t_E";
        case (t_T): return "t_T";
        case (t_F): return "t_F";
        case (t_TT): return "t_TT";
        case (t_FT): return "t_FT";
        case (t_ao): return "t_ao";
        case (t_mo): return "t_mo";
        case (t_none): return "t_none";
        case (t_id): return "t_id";
        case (t_literal): return "t_literal";
        case (t_gets): return "t_gets";
        case (t_add): return "t_add";
        case (t_sub): return "t_sub";
        case (t_mul): return "t_mul";
        case (t_div): return "t_div";
        case (t_lparen): return "t_lparen";
        case (t_rparen): return "t_rparen";
        case (t_eof): return "t_eof";
        case (t_let): return "t_let";
        case (t_newline): return "t_newline";
        default: return "not implemented";
    }
}

int isProduction(token t) {
    switch(t) {
        case (t_SL):
        case (t_S):
        case (t_D):
        case (t_E):
        case (t_T):
        case (t_F):
        case (t_TT):
        case (t_FT):
        case (t_ao):
        case (t_mo):
            return 1;
        default:
            return 0;
    }
}

list* tokens;
                      //   N/a     lit      +       *      (       $$      \n
                      //       id      :=       -       /       )      let
int parseTable[10][13] = {{-1,  1,  1, -1, -1, -1, -1, -1,  1, -1,  2,  1, -1} , // SL
                          {-1,  4,  4, -1, -1, -1, -1, -1,  4, -1, -1,  3, -1} , // S
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  5, -1} , // D
                          {-1,  6,  6, -1, -1, -1, -1, -1,  6, -1, -1, -1, -1} , // E
                          {-1,  7,  7, -1, -1, -1, -1, -1,  7, -1, -1, -1, -1} , // T
                          {-1,  9, 10, -1, -1, -1, -1, -1,  8, -1, -1, -1, -1} , // F
                          {-1, 12, 12, -1, 11, 11, -1, -1, 12, 12, 12, 12, -1} , // TT
                          {-1, 14, 14, -1, 14, 14, 13, 13, 14, 14, 14, 14, -1} , // FT
                          {-1, -1, -1, -1, 15, 16, -1, -1, -1, -1, -1, -1, -1} , // ao
                          {-1, -1, -1, -1, -1, -1, 17, 18, -1, -1, -1, -1, -1}   // mo

};

token Productions[19][5] =  {{t_eof, t_SL},
                             {t_SL, t_S},
                             {},
                             {t_D},
                             {t_E},
                             {t_E, t_gets, t_id, t_let},
                             {t_TT, t_T},
                             {t_FT, t_F},
                             {t_rparen, t_E, t_lparen},
                             {t_id},
                             {t_literal},
                             {t_TT, t_T, t_ao},
                             {},
                             {t_FT, t_F, t_mo},
                             {},
                             {t_add},
                             {t_sub},
                             {t_mul},
                             {t_div},
};

void ProgramTD(list* tokens) {

    list* currentToken = tokens;

    stack* tokenStack = (stack*) malloc(sizeof(stack));
    tokenStack->type = t_none;
    stack* currentStack = (stack*) malloc(sizeof(stack));
    currentStack->prev = tokenStack;
    currentStack->type = t_SL;

    while ((currentToken->type != NULL) && (currentStack->type != t_none)) {

        if (isProduction(currentStack->type)) {

            token currentNonT = currentStack->type;
            currentStack = currentStack->prev;
            int prod = parseTable[((int) currentNonT) - 13][(int) currentToken->type];

            token expansion[5] = {0, 0, 0, 0, 0};
            memcpy(expansion, Productions[prod], 5*sizeof(int));

            int i = 0;
            token temp = expansion[0];
            while (temp != t_none) {
                stack* pushed = (stack*) malloc(sizeof(stack));
                pushed->type = temp;
                pushed->prev = currentStack;
                currentStack = pushed;
                i++;
                temp = expansion[i];
            }

        } else {

            if (currentStack->type == currentToken->type) {

                printf("%s\n", string_from_token(currentStack->type));
                currentStack = currentStack->prev;
                currentToken = currentToken->rest;

            }

        }

    }

}





