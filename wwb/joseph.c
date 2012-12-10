#include <stdio.h>
#include <stdlib.h>
#include "list_F.h"

struct Node *__joseph(struct Node *first, size_t people, size_t count)
{
	int n;
	struct Node *node;

	if (people == 1)
		return first;

	n = 0;
	while (people > 1) {
		n++;
		if (n == count - 1) {
			node = first->next;
			first->next = node->next;
			free(node);

			people--;
			n = 0;
		}

		first = first->next;
	}

	return first;
}

struct Node *_joseph(size_t people, size_t count)
{
	struct Node *first, *cur, *pre;

	//create a list
	first = CreateList_F(people);
	if (NULL == first)
		return NULL;

	//create a loop
	pre = first;
	cur = first->next;
	while (cur) {
		pre = cur;
		cur = cur->next;
	}

	pre->next = first;
}

int main(int argc, char *argv[])
{
	struct Node *joseph;

	joseph = _joseph(2, 3);

	printf("win	%d\n", joseph->data);
	free(joseph);

	return 0;
}
