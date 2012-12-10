#include <stdio.h>
#include <stdlib.h>

typedef int Type;

struct Node {
	Type data;
	struct Node *next;
};

struct Node *CreateNode(Type data)
{
	struct Node *node;

	node = (struct Node *)malloc(sizeof(*node));
	if (NULL == node) {
		perror("malloc failed!");
		return NULL;
	}

	node->data = data;
	node->next = NULL;

	return node;
}

struct Node *CreateList(size_t num)
{
	struct Node *first, *pre, *node;
	int i;
	first = NULL;

	for (i = 1; i <= num; i++) {
		node = CreateNode((Type)i);
		if (NULL == node)
			return NULL;

		if (NULL == first)
			first = node;
		else
			pre->next = node;

		pre = node;
	}
	pre->next = first;

	return first;
}

int joseph(int people, int num)
{
	struct Node *first = NULL;
	struct Node *tmp;

	first = CreateList(people);
	int flag = 0;

	while (people != 1) {
		flag++;

		if (flag == num - 1) {
			tmp = first->next;
			first->next = first->next->next;
			free(tmp);

			flag = 0;
			people--;
		}
		first = first->next;
	}

	return first->data;
}

int main(int argc, char *argv[])
{
	printf("%d\n", joseph(5, 3));
	return 0;
}
