#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define ARRAY_LEN 10 //(sizeof(data) / sizeof(data[0]))

typedef char Type;

struct stack {
	Type *data;
	size_t size;
	Type top;
};

typedef enum {
	false,
	true,
} boolean;

pthread_mutex_t mutex;

static boolean init_stack(struct stack *stack, size_t size)
{
	pthread_mutex_init(&mutex, 0);

	stack->data = malloc(sizeof(*(stack->data) * size));
	if (NULL == stack->data)
		return false;

	stack->size = size;
	stack->top = 0;

	return true;
}

static boolean IsEmpty(struct stack *stack)
{
	return stack->top == 0;
}

static boolean IsFull(struct stack *stack)
{
	return stack->top == stack->size;
}

static boolean push(struct stack *stack, Type data)
{
	if (IsFull(stack))
		return false;

//	pthread_mutex_lock(&mutex);

	stack->data[stack->top] = data;
	stack->top++;

//	pthread_mutex_unlock(&mutex);

	return true;
}

static boolean pop(struct stack *stack, Type *data)
{
	if (IsEmpty(stack))
		return false;

//	pthread_mutex_lock(&mutex);

	stack->top--;
	*data = stack->data[stack->top];

//	pthread_mutex_unlock(&mutex);

	return true ;
}

int main(int argc, char *argv[])
{
	struct stack srcStack, destStack;
	char s1[] = "hi liumei";
	char ch;
	char *tmp = s1;

	init_stack(&srcStack, 20);
	init_stack(&destStack, 20);

	push(&srcStack, ' ');
	while (*tmp != '\0') {
		push(&srcStack, *tmp);
		tmp++;
	}

	while (false != pop(&srcStack, &ch)) {
		if (ch != ' ') {
			push(&destStack, ch);
		} else {
			while(false != pop(&destStack, &ch)) {
				putchar(ch);
			}

			putchar(' ');
		}

	}

	putchar('\n');

	return 0;
}
