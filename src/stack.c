#include <stdlib.h>
#include "ufind.h"
#include "trie.h"
#include "stack.h"

#define true 1
#define false 0
#define bool int

void create(struct Stack **s) {
	*s = NULL;
}	// Function to create a stack
bool isEmpty(struct Stack *s) {
	return s == NULL;
}	// Function to check if the stack is empty
bool push(struct Stack **s, struct Trie *val) {
	struct Stack *tmp;
	tmp = (struct Stack *) malloc(sizeof(struct Stack));
	if (tmp == NULL) {return false;}
	tmp->next = *s;
	tmp->val = val;
	*s = tmp;
	return true;
}	// Function to add an item to stack, return false if no memory available, true otherwise
struct Trie *pop(struct Stack **s) {
	struct Stack *tmp = *s;
	struct Trie *val;
	val = (*s)->val;
	*s = (*s)->next;
	free(tmp);
	return (val);
}	// Function to remove an item from stack.
void freeStack(struct Stack **s) {
	while (!isEmpty(*s)) {
		pop(s);
	}
}	// Function to free a Stack


