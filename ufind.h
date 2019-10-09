#ifndef SMALL_TASK_UFIND_H
#define SMALL_TASK_UFIND_H

#endif //SMALL_TASK_UFIND_H
#define true 1
#define false 0
#define bool int

struct uNode {
	struct uNode *parent;
	unsigned long long int energy;
	int depth;
};	// Union node
struct list {
	struct uNode *u;
	struct list *next;
};	// Linked List with uNodes
struct uNode *newUNode(unsigned long long int val);

struct uNode *uFind(struct uNode *element);

void join(struct uNode *a, struct uNode *b);

bool freeuNode(struct uNode *element, struct list **l);

bool prepend(struct uNode *p, struct list **head);

void freeList(struct list *head);