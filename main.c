// [IPP] Małe Zadanie(Small Task), Gevorg Chobanyan 401929
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <values.h>
#include <errno.h>
#include "ufind.h"
#include "trie.h"
#include "stack.h"

#define CHAR_SIZE 4
#define MAX_WORD 8
#define NO_DIFF 0
#define STARTING_SIZE 1
#define ONE_ARGUMENT 1
#define TWO_ARGUMENTS 2
#define BAD_INPUT 0
#define NO_ENERGY 0
#define BASE_TEN 10

void err(/*int code*/) {
	fprintf(stderr, "ERROR\n");
}	// Function that returns Error. Error code was useful when determining what caused the error
void deletion(struct Trie *curr, char *str, struct list **l) {
	if (curr == NULL) {return;}
	struct Trie *prev = curr;
	int lastChar = *str - '0';
	while (*str) {
		prev = curr;
		lastChar = *str - '0';
		curr = curr->character[*str - '0'];
		if (curr == NULL) {return;}
		str++;
	}
	prev->character[lastChar] = NULL;
	freeTrie(curr, l);
}	// Deletes a Trie Node
void reachEnd() {
	while ((getchar()) != '\n') {}
}	// Takes input till the end
char *pushArr(int i, char value, char *arr, int *capacity) {
	if (i > (*capacity) - 1) {
		*capacity *= 2;
		arr = (char *) realloc(arr, sizeof(char) * (*capacity));
	}
	if (arr != NULL)
		arr[i] = value;
	return arr;
}	// Set in i position of arr
char *getFirstWord(char *letter, char *word) {
	int i = 1;
	int cap = STARTING_SIZE;
	word = pushArr(0, *letter, word, &cap);
	while ((*letter = (char) getchar()) != '\n' && i <= MAX_WORD - 1) {		// Get letter from first word
		word = pushArr(i, *letter, word, &cap);
		i++;
		if (*letter == ' ') {break;}
	}
	if (i > MAX_WORD) {reachEnd();}
	word = pushArr(i, '\0', word, &cap);
	return word;
}	// Take first word
char *getOneArgument(bool *valid, char *arr) {
	int i = 0;
	char letter;
	int cap = STARTING_SIZE;
	while ((letter = (char) getchar()) != '\n') {
		if (letter < '0' || letter > '3') {
			*valid = false;
			reachEnd();
			break;
		}
		arr = pushArr(i, letter, arr, &cap);
		i++;
	}
	if (i == 0) {*valid = false;}
	arr = pushArr(i, '\0', arr, &cap);
	return arr;
}	// Take one argument
char *getFirstArgument(int *option, char *arr) {
	int i = 0;
	char letter;
	int cap = STARTING_SIZE;
	while ((letter = (char) getchar()) != '\n' && letter != ' ') {
		if (letter < '0' || letter > '3') {
			*option = BAD_INPUT;
			reachEnd();
			break;
		}
		arr = pushArr(i, letter, arr, &cap);
		i++;
	}
	if (letter == '\n') {*option = ONE_ARGUMENT;}
	if (i == 0) {
		*option = BAD_INPUT;
		if (letter == ' ') {reachEnd();}
	}
	arr = pushArr(i, '\0', arr, &cap);
	return arr;
}	// Take first argument for ENERGY
char *getFirstArgumentOnly(int *valid, char *arr) {
	int i = 0;
	char letter;
	int cap = STARTING_SIZE;
	while ((letter = (char) getchar()) != '\n' && letter != ' ') {
		if (letter < '0' || letter > '3') {
			*valid = false;
			reachEnd();
			break;
		}
		arr = pushArr(i, letter, arr, &cap);
		i++;
	}
	if (letter == '\n') {*valid = false;}
	if (i == 0) {
		*valid = false;
		if (letter == ' ') {reachEnd();}
	}
	arr = pushArr(i, '\0', arr, &cap);
	return arr;
}	// Take first argument for EQUAL
char *getSecondArgument(int *option, char *arr) {
	int i = 0;
	char letter;
	int cap = STARTING_SIZE;
	while ((letter = (char) getchar()) != '\n') {
		if (i == 0 && letter == '0') {
			*option = BAD_INPUT;
			reachEnd();
			break;
		}
		if (letter < '0' || letter > '9') {
			*option = BAD_INPUT;
			reachEnd();
			break;
		}
		arr = pushArr(i, letter, arr, &cap);
		i++;
	}
	if (i == 0) {*option = BAD_INPUT;}
	arr = pushArr(i, '\0', arr, &cap);
	return arr;
}	// Take second argument for ENERGY
char *getSecondArgumentOnly(int *valid, char *arr) {
	int i = 0;
	char letter;
	int cap = STARTING_SIZE;
	while ((letter = (char) getchar()) != '\n') {
		if (letter < '0' || letter > '3') {
			*valid = false;
			reachEnd();
			break;
		}
		arr = pushArr(i, letter, arr, &cap);
		i++;
	}
	if (i == 0) {*valid = false;}
	arr = pushArr(i, '\0', arr, &cap);
	return arr;
}	// Take second argument for EQUAL
unsigned long long int energyMedian(unsigned long long int energy1, unsigned long long int energy2) {
	if (energy1 == NO_ENERGY && energy2 == NO_ENERGY) {return NO_ENERGY;}
	if (energy1 == NO_ENERGY || energy2 == NO_ENERGY) {return energy1 + energy2;}
	return energy1 / 2 + energy2 / 2 + (energy1 % 2 + energy2 % 2) / 2;
}	// Median
int main() {
	struct list *l = NULL;
	struct Trie *head = getNewTrieNode();
	if (head == NULL) {return 1;}
	char letter;
	int option;
	unsigned long long int energyInt, median;
	bool valid;
	struct Trie *t, *t1, *t2;
	struct uNode *u, *u1, *u2;
	char *arr = (char *) malloc(sizeof(char));
	char *energy = (char *) malloc(sizeof(char));
	char *firstWord = (char *) malloc(sizeof(char));
	if (arr == NULL || energy == NULL || firstWord == NULL) {return 1;}
	while ((letter = getchar()) != EOF) {
		firstWord = (char *) realloc(firstWord, sizeof(char));
		energy = (char *) realloc(energy, sizeof(char));
		arr = (char *) realloc(arr, sizeof(char));
		if (letter == '\n') {continue;}
		if (letter == '#') {
			reachEnd();
			continue;
		}
		firstWord = getFirstWord(&letter, firstWord);
		if (arr == NULL || energy == NULL || firstWord == NULL) {return 1;}
		if (strcmp(firstWord, "DECLARE ") == NO_DIFF) {
			valid = true;
			arr = getOneArgument(&valid, arr);
			if (valid) {
				insert(head, arr);
				printf("OK\n");
			} else {err(4);}
		} else if (strcmp(firstWord, "VALID ") == NO_DIFF) {
			valid = true;
			arr = getOneArgument(&valid, arr);
			if (valid) {
				if (search(head, arr)) {printf("YES\n");}
				else {printf("NO\n");}
			} else {err(5);}
		} else if (strcmp(firstWord, "REMOVE ") == NO_DIFF) {
			valid = true;
			arr = getOneArgument(&valid, arr);
			if (valid) {
				deletion(head, arr, &l);
				printf("OK\n");
			} else {err(6);}
		} else if (strcmp(firstWord, "EQUAL ") == NO_DIFF) {
			valid = true;
			arr = getFirstArgumentOnly(&valid, arr);
			if (!valid) {
				err(11);
				continue;
			}
			t1 = search(head, arr);
			arr = (char *) realloc(arr, sizeof(char));
			arr = getSecondArgumentOnly(&valid, arr);
			if (!valid) {
				err(11);
				continue;
			}
			t2 = search(head, arr);
			if (t1 != NULL && t2 != NULL) {
				if (t1 == t2) {	// EQUAL same history to itself
					printf("OK\n");
					continue;
				}
				u1 = uFind(t1->u);
				u2 = uFind(t2->u);
				median = energyMedian(u1->energy, u2->energy);
				if (median == NO_ENERGY) {// Neither one has energy
					err(14);
					continue;
				}
				join(u1, u2);
				u1->energy = median;
				u2->energy = median;
				printf("OK\n");
				continue;
			} else {
				err(12);
				continue;
			}
		} else if (strcmp(firstWord, "ENERGY ") == NO_DIFF) {
			option = TWO_ARGUMENTS;
			// After its execution option is going to be changed to 1 or 0, and 2 if unchanged
			arr = getFirstArgument(&option, arr);
			if (option == BAD_INPUT) {
				err(10);
				continue;
			}
			if (option == ONE_ARGUMENT) {
				t = search(head, arr);
				if (t == NULL) {
					err(8);
					continue;
				}
				u = t->u;
				u = uFind(u);
				if (u->energy == NO_ENERGY) {
					err(9);
					continue;
				}
				printf("%llu\n", u->energy);
			} else if (option == TWO_ARGUMENTS) {
				energy = getSecondArgument(&option, energy);
				char *endPtr;
				int errnoInitialVal = errno;
				energyInt = strtoull(energy, &endPtr, BASE_TEN);
				if (errnoInitialVal != errno) {
					err(13);
					errno = errnoInitialVal;
					continue;
				}
				if (option == BAD_INPUT) {
					err(10);
					continue;
				}
				t = search(head, arr);
				if (t == NULL) {
					err(8);
					continue;
				}
				u = t->u;
				u = uFind(u);
				u->energy = energyInt;
				printf("OK\n");
				continue;
			}
		} else {
			err(7);
			if (letter != '\n') {
				reachEnd();
			}
		}
	}
	free(firstWord);
	free(arr);
	free(energy);
	if (!freeTrie(head, &l)) {return 1;}
	freeList(l);
	return 0;
} // Main to take input
/* Error codes:
 * 1: giveEnergy() with NULL t
 * 2: giveEnergy() with t->uNode==NULL
 * 3: InsertEnergy() with t==NULL
 * 4: Wrong argument for DECLARE
 * 5: Wrong argument for VALID
 * 6: Wrong argument for REMOVE
 * 7: Wrong command
 * 8: Trying to access energy of a non-existant history
 * 9: Valid History doesn't have energy
 * 10: Bad command for ENERGY
 * 11: EQUAL wrong command
 * 12: EQUAL undeclared history
 * 13: strtoull() failed
 * 14: None of the two have energy when doing EQUAL
 * */
