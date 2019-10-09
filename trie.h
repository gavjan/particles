#include <stdio.h>

#define CHAR_SIZE 4
#ifndef TESTING_SEPERATE_TRIE_H
#define TESTING_SEPERATE_TRIE_H

#endif //TESTING_SEPERATE_TRIE_H

struct Trie {
	struct Trie *character[CHAR_SIZE];
	struct uNode *u;	// Pointer to a uNode
};	// A Trie node
struct Trie *getNewTrieNode();

void insert(struct Trie *curr, char *str);

struct Trie *search(struct Trie *head, char *str);

bool freeTrie(struct Trie *t, struct list **l);