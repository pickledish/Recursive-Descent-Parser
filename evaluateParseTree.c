//
// Created by Manan hora on 10/17/16.
//

/*
 * Turn your parser into a calculator by evaluating the parse tree produced by your parser.
 * That is, write code to traverse a parse tree computing the value of
 * sub- expressions as appropriate and printing the final result.
 * You may use either ver- sion of your parser—they should produce equivalent parse trees.
 * The result is a command-line calculator like the UNIX program bc.*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include <stdbool.h>


//char* getTreeExpression(TREE tree, char* exp){
//    if(tree==NULL){
//        return 0;
//    }
//    exp = strcat((getTreeExpression(tree->leftmostChild, exp)), exp);
//    if(tree->leftmostChild==NULL){
//        exp = strcat(tree->value, exp);
//    }
//    exp = strcat((getTreeExpression(tree->rightSibling, exp)), exp);
//    return exp;
//}

bool isOperator(char c) {
    if (c == '+' || c == '-'
        || c == '*' || c == '/'
        || c == '^') {
        return true;
    }
    return false;
}

int evaluateExpression(char* exp){
    int result = 0;
    //get the first "number"
    while(*exp!=NULL){
        char a = *exp;
        if(a!=" "){
            //a is either a literal, a symbol or a bracket,
           if(!isOperator(a)){

           }
        }
    }
    return result;
}




int evaluateParseTree(TREE tree){
    if(tree->value=="S"){
        return evaluateParseTree(tree->leftmostChild);
    }
    if(tree->value=="D"){

    }
    if(tree->value == "E"){
        int leftHalf = evaluateParseTree(tree->leftmostChild);
        int rightHalf = evaluateParseTree(tree->leftmostChild->rightSibling);
        int result = leftHalf + rightHalf;
        return result;
    }
    if(tree->value == "T"){
        if(tree->leftmostChild!=NULL){
            int leftHalf = evaluateParseTree(tree->leftmostChild);
            int rightHalf = evaluateParseTree(tree->leftmostChild->rightSibling);
            int result = leftHalf*rightHalf;
            return result;
        }
    }
    if(tree->value == "FT"){
        int firstRightHalf = evaluateParseTree(tree->leftmostChild->rightSibling);
        int secondRightHalf = evaluateParseTree(tree->leftmostChild->rightSibling->rightSibling);
        int result = firstRightHalf*secondRightHalf;
        if(tree->leftmostChild->leftmostChild->value=="*"){
            return result;
        }
        if(tree->leftmostChild->leftmostChild->value=="/"){
            result = 1/result;
            return result;
        }
    }
    if(tree->value == "TT"){
        int firstRightHalf = evaluateParseTree(tree->leftmostChild->rightSibling);
        int secondRightHalf = evaluateParseTree(tree->leftmostChild->rightSibling->rightSibling);
        int result = firstRightHalf + secondRightHalf;
        if(tree->leftmostChild->leftmostChild->value=="+"){
            return result;
        }
        else if(tree->leftmostChild->leftmostChild->value == "-"){
            return (0 - result);
        }
    }
    if(tree->value == "F"){
        if(tree->leftmostChild->value == "("){
            int expressionVal = evaluateParseTree(tree->leftmostChild->rightSibling);
            return expressionVal;
        }
        else{
            int result = atoi(tree->leftmostChild->value);
            return result;
        }
    }
}

















































