#ifndef SMALL_TASK_STACK_H
#define SMALL_TASK_STACK_H

#endif //SMALL_TASK_STACK_H

struct Stack {
	struct Trie *val;
	struct Stack *next;
};

void create(struct Stack **s);

int isEmpty(struct Stack *s);

bool push(struct Stack **s, struct Trie *item);

struct Trie *pop(struct Stack **s);

void freeStack(struct Stack **s);
