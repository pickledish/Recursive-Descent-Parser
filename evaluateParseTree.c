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


char* getTreeExpression(TREE tree, char* exp){

    if(tree==NULL){
        return 0;
    }
    exp = strcat((getTreeExpression(tree->leftmostChild, exp)), exp);
    if(tree->leftmostChild==NULL){
        exp = strcat(tree->value, exp);
    }
    exp = strcat((getTreeExpression(tree->rightSibling, exp)), exp);
    return exp;

}

int evaluateExpression(char* exp){
    int result = 0;
    for(int i = 0; i<strlen(exp); i++){
        char a = exp[i];
        if(a!=" " && a!="")
    }
}

int evaluateParseTree(TREE tree){
    char* exp =
}

//void printInorder(Node node)
//{
//    if (node == null)
//        return;
//
//    /* first recur on left child */
//    printInorder(node.left);
//
//    /* then print the data of node */
//    System.out.print(node.key + " ");
//
//    /* now recur on right child */
//    printInorder(node.right);
//}