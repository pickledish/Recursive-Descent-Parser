#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"

token tokenize(char* t) {
    if (strcmp(t, "+") == 0) { return t_add; }
    else if (strcmp(t, "-") == 0) { return t_sub; }
    else if (strcmp(t, "*") == 0) { return t_mul; }
    else if (strcmp(t, "/") == 0) { return t_div; }
    else if (strcmp(t, "(") == 0) { return t_lparen; }
    else if (strcmp(t, ")") == 0) { return t_rparen; }
    else if (strcmp(t, "$") == 0) { return t_eof; }
    else if (strcmp(t, "let") == 0) { return t_let; }
    else if (strcmp(t, ":=") == 0) { return t_gets; }
    else {
        // printf(" Hello %d\n", isalpha(t[0]));
        if (isnumber(t[0]) != 0) {
            return t_literal;
        } else {
            return t_id;
        }
    }
}

int main()
{
	// Don't ask why "strang" needs to exist. It has to do with string literals and I don't get it either.
	printf("Please enter a starting statement (q to quit): ");
	char strang[] = "hi";
	char* input = &strang[0];
	scanf(" %[^\n]", input);

	// A 'q' followed by the end of string character means the human wants to quit
	while ( !( (input[0] == 'q') && (input[1] == '\0'))) {
		
		char* t;
		list* tokens = (list*) malloc(sizeof(list));
		list* current = tokens;

        tokens->type = NULL;

		// strtok is a function that breaks up a string into tokens based on the delimiter (here, " ")
		t = strtok(input, " ");

		// Keep breaking our input string into tokens and adding them to a linked list
		while (t != NULL) {
			//printf("%s\n", t);
            current->type = tokenize(t);
            current->value = t;
			current->rest = (list*) malloc(sizeof(list));
			current = current->rest;
			t = strtok(NULL, " ");
		}

        current->type = NULL;

		ProgramTD(tokens);

		input: printf("\n\nPlease enter another statement (q to quit): ");
		scanf(" %[^\n]", input);
	}

	return 0;
}

