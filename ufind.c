#include "ufind.h"
#include "trie.h"
#include <stdlib.h>

struct uNode *newUNode(unsigned long long int val) {
	struct uNode *p;
	if ((p = (struct uNode *) malloc(sizeof(struct uNode))) == NULL) {
		return NULL;
	}
	p->energy = val;
	p->parent = NULL;
	p->depth = 1;
	return p;
}	// Returns a new uNode, NULL if no memory is available
struct uNode *uFind(struct uNode *element) {
	if (element == NULL) {return NULL;}
	struct uNode *originalElement = element;
	while (element->parent != NULL) {
		element = element->parent;
	}
	if (element != originalElement->parent && element != originalElement) {
		originalElement->parent = element;
	}
	return element;
}	// Union find with compression
void join(struct uNode *a, struct uNode *b) {
	struct uNode *rootA = a;
	struct uNode *rootB = b;
	if (rootA != rootB) {
		if (rootA->depth > rootB->depth) {
			rootB->parent = rootA;
		} else if (rootA->depth < rootB->depth) {
			rootA->parent = rootB;
		} else {
			rootA->parent = rootB;
			rootB->depth++;
		}
	}
}	// Merge two unions
bool freeuNode(struct uNode *element, struct list **l) {
	if (element == NULL) {return true;}

	if (element->depth == 1) {free(element);}
	else {
		if (!prepend(element, l)) {return false;}
	}
	return true;
}	// Free uNode, return false if no memory available, true otherwise
bool prepend(struct uNode *p, struct list **head) {
	struct list *new;
	new = (struct list *) malloc(sizeof(struct list));
	if (new == NULL) {
		return false;
	}
	new->u = p;
	new->next = *head;
	*head = new;
	return true;
}	// Prepend to a linked list, return false if no memory available, true otherwise
void freeList(struct list *head) {
	struct list *tmp;
	struct uNode *u;
	while (head != NULL) {
		tmp = head;
		head = head->next;
		u = tmp->u;
		tmp->u = NULL;
		free(u);
		free(tmp);
	}
}	// Frees a linked list