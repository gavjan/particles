# Quantization makefile

CC       ?= gcc
CFLAGS   += -Wall -Wextra -std=c11 -O2
OBJS = ufind.o trie.o stack.o main.o

all: make

run: make; ./quantization

make: $(OBJS)
	$(CC) $(CFLAGS) -o quantization ufind.c trie.c stack.c main.c

$(OBJS): ufind.h trie.h stack.h

valgrind: make; valgrind --error-exitcode=15 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./quantization

valgrind_origin: make; valgrind --error-exitcode=15 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --track-origins=yes -v ./quantization

# For testing with binary 'quantization' and tests folder 'tests'
test: make; ./test.sh quantization tests

clean:
	-@$(RM) quantization *.out *.err *.o
