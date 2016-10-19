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



int evaluateParseTree(TREE tree){
    if(tree->value=="SL"){
        return evaluateParseTree(tree->leftmostChild);
    }
    if(tree->value=="S"){
        return evaluateParseTree(tree->leftmostChild);
    }
    if(tree->value=="D"){
        return evaluateParseTree(tree->leftmostChild->rightSibling->rightSibling->rightSibling);
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
            int rightHalf = 1;
            if(tree->leftmostChild->rightSibling!=NULL && tree->leftmostChild->rightSibling->value!=NULL){
                rightHalf = evaluateParseTree(tree->leftmostChild->rightSibling);
            }
            int result = leftHalf*rightHalf;
            return result;
        }
    }
    if(tree->value == "FT"){
        int result = 1;
        if(tree->leftmostChild!=NULL){
            int firstRightHalf = evaluateParseTree(tree->leftmostChild->rightSibling);
            int secondRightHalf = evaluateParseTree(tree->leftmostChild->rightSibling->rightSibling);
            result = firstRightHalf*secondRightHalf;
            if(tree->leftmostChild->leftmostChild->value=="*"){
                return result;
            }
            if(tree->leftmostChild->leftmostChild->value=="/"){
                result = 1/result;
                return result;
            }
        }
        return result;
    }
    if(tree->value == "TT"){
        int result = 0;
        if(tree->leftmostChild!=NULL){
            int firstRightHalf = evaluateParseTree(tree->leftmostChild->rightSibling);
            int secondRightHalf = 0;
            if(tree->leftmostChild->rightSibling->rightSibling!=NULL){
                secondRightHalf = evaluateParseTree(tree->leftmostChild->rightSibling->rightSibling);
            }
            result = firstRightHalf + secondRightHalf;
            if(tree->leftmostChild->leftmostChild->value=="+"){
                return result;
            }
            else if(tree->leftmostChild->leftmostChild->value == "-"){
                return (0 - result);
            }
        }
        return result;
    }
    if(tree->value == "F"){

        if(tree->leftmostChild->value[0] == '('){
            int expressionVal = evaluateParseTree(tree->leftmostChild->rightSibling);
            return expressionVal;
        }
        else{
            int result = atoi(tree->leftmostChild->value);
            return result;
        }
    }
}





















