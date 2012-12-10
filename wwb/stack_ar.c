#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#define LEN 10
#define STACK_SIZE 512
#define EFULLSTACK 2
#define EEMPTYSTACK 3

typedef int Type;

typedef enum {
	false,
	true,
} bool;

struct Stack {
	long *stack;
	int size;
	int sp;
};

struct Stack *initStack(size_t size)
{
	struct Stack *stack;

	if (size < 50) {
		printf("stack's size too small\n");
		return NULL;
	}

	stack = malloc(sizeof(struct Stack));
	if (stack == NULL) {
		perror("malloc");
		return NULL;
	}

	stack->stack = malloc(size);
	if (NULL == stack->stack) {
		perror("malloc");
		return NULL;
	}

	stack->size = size;
	stack->sp = 0;

	return stack;
}

void destryStack(struct Stack *stack)
{
	free(stack->stack);
	free(stack);
}

static bool emptyStack(struct Stack *stack)
{
	return stack->sp == 0;
}

static bool fullStack(struct Stack *stack)
{
	return stack->sp + 1 == stack->size;
}

int push(struct Stack *stack, long data)
{
	if (fullStack(stack)) {
		fprintf(stderr, "%s", "\nfull stack!\n");
		return -EFULLSTACK;
	}

	stack->stack[stack->sp++] = data;

	return 0;
}

int pop(struct Stack *stack, long *data)
{
	if (emptyStack(stack)) {
		fprintf(stderr, "%s", "\nempty stack!\n");
		return -EEMPTYSTACK;
	}

	*data = stack->stack[--stack->sp];

	return 0;
}

int main(int argc, char *argv[])
{
	int i;
	long data;
	struct Stack *stack;

	srand(time(NULL));
	stack = initStack(100);
	if (NULL == stack)
		return -1;

	for (i = 0; i < LEN; i++) {
		push(stack, rand() % 100);
	}
	putchar('\n');

	for (i = 0; i < LEN; i++) {
		pop(stack, &data);
		printf("%ld	", data);
	}
	putchar('\n');

	destryStack(stack);

	return 0;
}
