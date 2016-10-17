//
// Created by Kyle Edgette on 10/16/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"

list* tokens;

int debug = 1;

TREE multiplyOperation();
TREE declaration();
TREE statementList();
TREE statement();
TREE expression();
TREE term();
TREE termTail();
TREE factor();
TREE factorTail();
TREE addOperation();

void recursivePrint(TREE subtree, int indentLevel);
void printTree(TREE result);

TREE Program(list* tokens2) {

    tokens = tokens2;

    TREE result = statementList();

    if(result != NULL) {
        printTree(result);
    }
}

void printTree(TREE result) {

    recursivePrint(result, 0);

}

void recursivePrint(TREE subtree, int indentLevel) {

    if(subtree == NULL) {
        return;
    }

    printf("\n");

    for(int i = 0; i < indentLevel; i++) {
        printf("\t");
    }

    printf("(%s", subtree->value);

    if(subtree->leftmostChild != NULL) {
        recursivePrint(subtree->leftmostChild, indentLevel+1);

        TREE sibling = subtree->leftmostChild->rightSibling;

        while(sibling != NULL) {
            recursivePrint(sibling, indentLevel+1);
            if(sibling->rightSibling != NULL) {
                sibling = sibling->rightSibling;
            }
            else {
                break;
            }
        }


    }

    printf(")");

}

void error() {
    while ( (token) tokens->type != t_newline ) {
        tokens = tokens->rest;
    }
}

TREE match(token expected){
    if (expected == tokens->type) {
        if (debug) {printf("in match()\n");}
        TREE m = (TREE) malloc(sizeof(TREE));
        m->value = tokens->value;
        tokens = tokens->rest;
        return m;
    } else {
        // Throw Exception
    }
}

TREE statementList() {
    if (debug) {printf("in statementList()\n");}
    TREE returner = (TREE) malloc(sizeof(TREE));
    TREE t1, t2;

    switch((token) (tokens->type)) {

        case (t_none):
            return returner;

        case (t_lparen):
        case (t_id):
        case (t_literal):
        case (t_let):
            t1 = statement();
            match(t_newline);
            t2 = statementList();

            (TREE) malloc(sizeof(TREE));
            returner->value = "SL";
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

    if (debug) {printf("in statement()\n");}
    TREE returner = (TREE) malloc(sizeof(TREE));
    TREE t0, t1;

    switch((token) (tokens->type)) {

        case (t_none):
            return returner;

        case (t_let):
            t0 = declaration();
            returner->value = "S";
            returner->leftmostChild = t0;
            break;
        case (t_lparen):
        case (t_id):
        case (t_literal):

            t1 = expression();
            returner->value = "S";
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
    if (debug) {printf("in expression()\n");}
    TREE returner = (TREE) malloc(sizeof(TREE));
    TREE t1, t2;

    switch((token) (tokens->type)) {

        case (t_none):
            return returner;

        case (t_lparen):
        case (t_id):
        case (t_literal):
            t1 = term();
            t2 = termTail();
            t1->rightSibling = t2;
            returner->value = "E";
            returner->leftmostChild = t1;
            break;
        case (t_eof) : break;
        default:
            printf("ERROR! : expression()");
            error();

    }
    return returner;


}

TREE term(){
    if (debug) {printf("in term()\n");}
    TREE returner = (TREE) malloc(sizeof(TREE));
    TREE t1, t2;

    switch((token) (tokens->type)) {

        case (t_none):
            return returner;

        case (t_lparen):
        case (t_id):
        case (t_literal):
            t1 = factor();
            t2 = factorTail();
            t1->rightSibling = t2;
            returner->value = "T";
            returner->leftmostChild = t1;
            break;
        case (t_eof) : break;
        default:
            printf("ERROR! : term()");
            error();

    }
    return returner;
}

TREE factorTail(){
    if (debug) {printf("in factorTail()\n");}
    TREE returner = (TREE) malloc(sizeof(TREE));
    TREE t1, t2, t3;

    switch((token) (tokens->type)) {

        case (t_none):
            return returner;

        case (t_mul):
        case (t_div):
            t1 = multiplyOperation();
            t2 = factor();
            t3 = factorTail();
            returner->value = "FT";
            returner->leftmostChild = t1;
            t1->rightSibling = t2;
            t2->rightSibling = t3;
            break;

        case (t_eof) :
        case (t_add):
        case (t_sub):
        case (t_rparen):
        case (t_let):
        case (t_lparen):
        case (t_id):
        case (t_literal):
            break;

        default:
            printf("ERROR! : factorTail()");
            error();

    }
    return returner;
}

TREE termTail(){
    if (debug) {printf("in termTail()\n");}
    TREE returner = (TREE) malloc(sizeof(TREE));
    TREE t1, t2, t3;

    switch((token) (tokens->type)) {

        case (t_none):
            returner->value = "TT";
            returner->leftmostChild = NULL;
            returner->rightSibling = NULL;
            return returner;

        case (t_add):
        case (t_sub):
            t1 = addOperation();
            t2 = term();
            t3 = termTail();

            t2->rightSibling = t3;
            t1->rightSibling = t2;
            returner->value = "TT";
            returner->leftmostChild = t1;
            break;

        case (t_eof):
        case (t_rparen):
        case (t_let):
        case (t_lparen):
        case (t_id):
        case (t_literal):
            break;
        default:
            printf("ERROR! : termTail()");
            error();

    }

}

TREE addOperation() {
    if (debug) {printf("in addOperation()\n");}
    TREE returner = (TREE) malloc(sizeof(TREE));
    TREE t1;

    switch ((token) (tokens->type)) {

        case (t_none):
            return returner;

        case (t_add):
            t1 = match(t_add);
            returner->value = "A";
            returner->leftmostChild = t1;
            break;

        case (t_sub):
            t1 = match(t_sub);
            returner->value = "A";
            returner->leftmostChild = t1;
            break;

        default:
            printf("ERROR! addOperation()");
            error();
    }

    return returner;
}
TREE factor(){
    if (debug) {printf("in factor()\n");}
    TREE returner = (TREE) malloc(sizeof(TREE));
    TREE t1, t2, t3;

    switch ((token) (tokens->type)) {

        case (t_none):
            return returner;

        case (t_lparen):
            t1 = match(t_lparen);
            t2 = expression();
            t3 = match(t_rparen);
            returner->value = "F";
            returner->leftmostChild = t1;
            t1->rightSibling = t2;
            t2->rightSibling = t3;
            break;

        case (t_id):
            t1 = match(t_id);
            returner->value = "ID";
            returner->leftmostChild = t1;
            break;

        case (t_literal):
            t1 = match(t_literal);
            returner->value = "N";
            returner->leftmostChild = t1;
            break;

        default:
            printf("ERROR! factor()");
            error();
    }
    return returner;
}

//TREE number(){
//    char* num = getNum(tokens);
//    if(isNumber(num)){
//        // match the number
//        //make a tree
//    }
//}

TREE multiplyOperation(){
    if (debug) {printf("in multiplyOperation()\n");}
    TREE returner = (TREE) malloc(sizeof(TREE));
    TREE t1;
    switch ((token) (tokens->type)) {

        case (t_none):
            return returner;

        case (t_mul):
            t1 = match(t_mul);
            returner->value = "M";
            returner->leftmostChild = t1;
            break;

        case (t_div):
            t1 = match(t_div);
            returner->value = "M";
            returner->leftmostChild = t1;
            break;

        default:
            printf("ERROR! multiplyOperation()");
            error();
    }

    return returner;
}

TREE declaration(){
    if (debug) {printf("in declaration()\n");}
    TREE returner = (TREE) malloc(sizeof(TREE));
    TREE t1, t2, t3, t4;
    switch ((token) (tokens->type)) {

        case (t_none):
            return returner;

        case (t_let):
            t1 = match(t_let);
            t2 = match(t_id);
            t3 = match(t_gets);
            t4 = expression();
            returner->value = "D";
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

