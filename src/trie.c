#include "ufind.h"
#include "trie.h"
#include "stack.h"
#include <stdlib.h>

#define NO_ENERGY 0

struct Trie *getNewTrieNode() {
	struct Trie *node = (struct Trie *) malloc(sizeof(struct Trie));
	if (node == NULL) {
		return NULL;
	}
	node->u = newUNode(NO_ENERGY);
	for (int i = 0; i <= CHAR_SIZE - 1; i++) {
		node->character[i] = NULL;
	}
	return node;
}	// Function that returns a new Trie node, returns NULL if no memory is available
void insert(struct Trie *curr, char *str) {
	while (*str) {
		if (curr->character[*str - '0'] == NULL) {
			curr->character[*str - '0'] = getNewTrieNode();
		}
		curr = curr->character[*str - '0'];
		str++;
	}
}	// Insert a history in Trie.
struct Trie *search(struct Trie *head, char *str) {
	if (head == NULL || str == NULL) {return NULL;}
	struct Trie *curr = head;
	while (*str) {
		curr = curr->character[*str - '0'];
		if (curr == NULL) {return NULL;}
		str++;
	}
	return curr;
}	// Search for a history in Trie
bool freeTrie(struct Trie *t, struct list **l) {
	if (t == NULL) {return true;}
	struct Stack *s;
	create(&s);
	if (!push(&s, t)) {return false;}
	while (!isEmpty(s)) {
		t = pop(&s);
		for (int i = 0; i <= CHAR_SIZE - 1; i++) {
			if (t->character[i] != NULL) {
				if (!push(&s, t->character[i])) {return false;}
			}
		}
		if (!freeuNode(t->u, l)) {return false;}
		free(t);
	}
	freeStack(&s);
	return true;
}	// Free Trie Node, return false if no memory available, true otherwise
