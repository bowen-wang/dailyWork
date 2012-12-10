#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list_F.h"

static struct Node *CreateNode(Type data)
{
	struct Node *node;

	node = malloc(sizeof(*node));
	if (NULL == node)
		return NULL;

	node->data = data;
	node->next = NULL;

	return node;
}

struct Node *CreateList_F(size_t len)
{
	int i;
	struct Node *first = NULL, *node;

	for (i = len; i > 0; i--) {
		node = CreateNode(rand() % 100);
		first = InsertNode(first, node);
	}

	return first;
}

struct Node *SeachInsert(struct Node *first, struct Node *node, Type data)
{
	struct Node *pre, *cur;

	if (first == NULL)
		return NULL;

	if (first->data == data) {
		node->next = first;
		first = node;
	} else {
		pre = first;
		while (pre->next) {
			cur = pre->next;
			if (cur->data == data) {
				node->next = cur;
				pre->next = node;

				break;
			}

			pre = pre->next;
		}
	}

	return first;
}

struct Node *ListSort(struct Node *first)
{
	struct Node *max, *pre, *preMax, *newFirst = NULL;

	while (1) {
		pre = first;
		max = first;
		while (pre->next) {
			if (max->data < pre->next->data) {
				preMax = pre;
				max = pre->next;
			}

			pre = pre->next;
		}

		if (max == first)
			first = max->next;
		else
			preMax->next = max->next;

		max->next = newFirst;
		newFirst = max;

		if (first == NULL)
			break;
	}

	return newFirst;
}

struct Node *DelNode(struct Node *first, Type data)
{
	struct Node *cur, *pre;

	if (NULL == first)
		return NULL;

	cur = first;
	if (first->data == data) {
		first = first->next;
	} else {
		pre = first;
		cur = pre->next;
		while (cur) {
			if (cur->data == data) {
				pre->next = cur->next;
				break;
			}

			pre = cur;
			cur = cur->next;
		}
	}
	free(cur);

	return first;
}

int TraverseList(struct Node *first)
{
	struct Node *node = first;
	while (node) {
		printf("%d	", node->data);
		node = node->next;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	struct Node *first;

	srand(time(NULL));

	first = CreateList_F(10);
	TraverseList(first);
	putchar('\n');

//	first = DelNode(first, 1);

	first = ListSort(first);
	TraverseList(first);
	putchar('\n');

	return 0;
}
