//
// Created by Kyle Edgette on 10/16/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"

list* tokens;

TREE multiplyOperation();
TREE declaration();
TREE printTree();
TREE statementList();
TREE statement();
TREE expression();
TREE term();
TREE termTail();
TREE factor();
TREE factorTail();
TREE addOperation();

TREE Program(list* tokens2) {

    tokens = tokens2;

    TREE result = statementList();

    if(result != NULL) {
        //printTree(result);
    }
}

void error() {
    while ( (token) tokens->item != t_newline ) {
        tokens = tokens->rest;
    }
}

TREE match(token expected){
    if (expected == tokens->item) {
        tokens = tokens->rest;
        TREE m = (TREE) malloc(sizeof(TREE));
        m->item = expected;
        return m;
    } else {
        // Throw Exception
    }
}

TREE statementList() {

    TREE returner = (TREE) malloc(sizeof(TREE));
    TREE t1, t2;

    switch((token) (tokens->item)) {

        case (t_lparen):
        case (t_id):
        case (t_literal):
        case (t_let):
            t1 = statement();
            match(t_newline);
            t2 = statementList();

            TREE returner = (TREE) malloc(sizeof(TREE));
            returner->item = "SL";
            returner->leftmostChild = t1;
            t1->rightSibling = t2;
            break;
        case (t_eof) : break;
        default:
            printf("ERROR! : statementList()");
            error();

    }
    return returner;
}


TREE statement() {

    TREE returner = (TREE) malloc(sizeof(TREE));
    TREE t0, t1;

    switch((token) (tokens->item)) {

        case (t_let):
            t0 = declaration();
            returner->item = "S";
            returner->leftmostChild = t0;
            break;
        case (t_lparen):
        case (t_id):
        case (t_literal):

            t1 = expression();
            returner->item = "S";
            returner->leftmostChild = t1;
            break;
        case (t_eof) : break;
        default:
            printf("ERROR! : statement()");
            error();

    }
    return returner;
}


TREE expression() {

    TREE returner = (TREE) malloc(sizeof(TREE));
    TREE t1, t2;

    switch((token) (tokens->item)) {

        case (t_lparen):
        case (t_id):
        case (t_literal):
            t1 = term();
            t2 = termTail();
            returner->item = "E";
            returner->leftmostChild = t1;
            t1->rightSibling = t2;
            break;
        case (t_eof) : break;
        default:
            printf("ERROR! : expression()");
            error();

    }
    return returner;


}

TREE term(){
    TREE returner = (TREE) malloc(sizeof(TREE));
    TREE t1, t2;

    switch((token) (tokens->item)) {

        case (t_lparen):
        case (t_id):
        case (t_literal):
            t1 = factor();
            t2 = factorTail();
            returner->item = "T";
            returner->leftmostChild = t1;
            t1->rightSibling = t2;
            break;
        case (t_eof) : break;
        default:
            printf("ERROR! : term()");
            error();

    }
    return returner;
}

TREE factorTail(){
    TREE returner = (TREE) malloc(sizeof(TREE));
    TREE t1, t2, t3;

    switch((token) (tokens->item)) {

        case (t_mul):
        case (t_div):
            t1 = multiplyOperation();
            t2 = factor();
            t3 = factorTail();
            returner->item = "FT";
            returner->leftmostChild = t1;
            t1->rightSibling = t2;
            t2->rightSibling = t3;
            break;
        case (t_eof) : break;
        default:
            printf("ERROR! : factorTail()");
            error();

    }
    return returner;
}

TREE termTail(){

    TREE returner = (TREE) malloc(sizeof(TREE));
    TREE t1, t2, t3;

    switch((token) (tokens->item)) {

        case (t_add):
        case (t_sub):
            t1 = addOperation();
            t2 = term();
            t3 = termTail();

            returner->item = "TT";
            returner->leftmostChild = t1;
            t1->rightSibling = t2;
            t2->rightSibling = t3;

            break;
        case (t_eof) : break;
        default:
            printf("ERROR! : factorTail()");
            error();

    }

}

TREE addOperation() {
    TREE returner = (TREE) malloc(sizeof(TREE));
    TREE t1;

    switch ((token) (tokens->item)) {

        case (t_add):
            t1 = match(t_add);
            returner->item = "A";
            returner->leftmostChild = t1;
            break;

        case (t_sub):
            t1 = match(t_sub);
            returner->item = "A";
            returner->leftmostChild = t1;
            break;

        default:
            printf("ERROR! addOperation()");
            error();
    }

    return t1;
}
TREE factor(){
    TREE returner = (TREE) malloc(sizeof(TREE));
    TREE t1, t2, t3;

    switch ((token) (tokens->item)) {

        case (t_lparen):
            t1 = match(t_lparen);
            t2 = expression();
            t3 = match(t_rparen);
            returner->item = "F";
            returner->leftmostChild = t1;
            t1->rightSibling = t2;
            t2->rightSibling = t3;
            break;

        case (t_id):
            t1 = match(t_id);
            returner->item = "ID";
            returner->leftmostChild = t1;
            break;

        case (t_literal):
            t1 = match(t_literal);
            returner->item = "N";
            returner->leftmostChild = t1;
            break;

        default:
            printf("ERROR! factor()");
            error();
    }
    return t1;
}

//TREE number(){
//    char* num = getNum(tokens);
//    if(isNumber(num)){
//        // match the number
//        //make a tree
//    }
//}

TREE multiplyOperation(){
    TREE returner = (TREE) malloc(sizeof(TREE));
    TREE t1;
    switch ((token) (tokens->item)) {
        case (t_mul):
            t1 = match(t_mul);
            returner->item = "M";
            returner->leftmostChild = t1;
            break;

        case (t_div):
            t1 = match(t_div);
            returner->item = "M";
            returner->leftmostChild = t1;
            break;

        default:
            printf("ERROR! multiplyOperation()");
            error();
    }

    return t1;
}

TREE declaration(){
    TREE returner = (TREE) malloc(sizeof(TREE));
    TREE t1, t2, t3, t4;
    switch ((token) (tokens->item)) {
        case (t_let):
            t1 = match(t_let);
            t2 = match(t_id);
            t3 = match(t_gets);
            t4 = expression();
            returner->item = "D";
            returner->leftmostChild = t1;
            t3->rightSibling = t4;
            t2->rightSibling = t3;
            t1->rightSibling = t2;
            break;


        default:
            printf("ERROR! Declaration()");
            error();
    }
    return t1;
}






//
//void printTree(TREE tree){
//
//}



