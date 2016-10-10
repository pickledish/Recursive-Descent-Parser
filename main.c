#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct list {
	void* item;
	struct list* rest;
} list;

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

		// strtok is a function that breaks up a string into tokens based on the delimiter (here, " ")
		t = strtok(input, " ");

		// Keep breaking our input string into tokens and adding them to a linked list
		while (t != NULL) {
			printf("%s\n", t);
			current->rest = (list*) malloc(sizeof(list));
			current = current->rest;
			current->item = t;
			t = strtok(NULL, " ");
		}

		// Finally done! Here, we /do something/ with tokens, the list of our statement's tokens. Parse.

	printf("Please enter another statement (q to quit): ");
	scanf(" %[^\n]", input);
	}

	return 0;
}