CSC 173 Project 2
October 19, 2016

Partners:
	Brandon Willett
	Kyle Edgette
	Manan Hora

Scanner.h

Simple header, defines functions that are used across files. Inside, we define an enum "token" to make the handling of our different types of token easier. Also defines simple list and stack implementations, for tokens, that are used throughout the code. List and Stack both have two data fields, one for the type of token (t_literal, t_add, etc) and one string for the actual content of that token (like "3" or "+"). In addition, there are NODE and TREE structures 

Scanner.c

VERY simple scanning procedure, considering that scanning is an entire necessary step of compilation that wasn't even mentioned in the project description. This file contains methods to look to standard input for a statement, cut the statement up into smaller strings based on spaces with the "strtok" function (thus, it's very important to use spaces between tokens like parentheses and operators), convert those small strings into tokens using a big switch statement inside the "tokenize" function, add those tokens to a list called "tokens", and then send it along to one of the parsing methods to be parsed. A "q" and nothing else inputted means the user wants to quit, and the program will do so. Otherwise, it will parse the input statement and then come back and request another statement. 

RecursiveDescentParser.c

This (large) file contains all the usual elements of a recursive descent parser, and it's mainly made up of an individual function for each nonterminal in the grammar. Each of these functions returns a tree, where each of its children are one of the terminals/nonterminals that the parent nonterminal expands into via the appropriate production. This particular production is guessed via the use of the one look-ahead token (since our grammar is LL(1)) and the hand-coded predict sets, which can be seen in productions.txt. So, the calls to these functions will produce nodes, which set their children to the trees returned by the functions of its expansion tokens. 

This file also contains a "match" function, which consumes a single token from the "tokens" list and creates a leaf node from it, containing the content of the token. That node is returned, and used by other methods in the construction of the tree. In addition, we have the "printTree" function, which calls "recursivePrint" with a depth of 0 to walk over the parse tree in a depth-first manner and print out the contents of the node (i.e. the value or nonterminal) with the appropriate tabs and parentheses. Finally, we have the "getTreeExpression" function.

table_Driven.c

The file also contains some useful methods, such as "string_from_token" to convert a token into its string representation, and "isProduction" to determine whether a token is a nonterminal (I misnamed it a little). Finally, we include a large table which shows 

Running the project:

Notes:

	- We know that "t_SL", "t_E", and other nonterminals should not count as tokens. They were put there so that they could be used in a list/stack in the table-driven implementation, and are handled such that they never cause problems.

	- We implemented variable creation and assignment, in the form of a "let id := (expression)" statement. 

	- We did not use code from any other website in this project.

	- Input an "r" or a "t" at the start line to determine whether to use recursive descent descent or table driven.







