#include <stdio.h>
#include <stdlib.h>

#define EMALLOC 1
//#define LEN 10

typedef int Type;

struct Node {
	Type data;
	struct Node *next;
};

typedef void (*handler)(struct Node *node);

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

static struct Node *__invert(struct Node *first)
{
	struct Node *last, *node;

	if (NULL == first || NULL == first->next)
		return first;

	last = first->next;
	first->next = NULL;
	node = __invert(last);
	last->next = first;

	return node;
}

static int invert_iterate(struct Node *head)
{
	struct Node *pre, *cur, *last;

	pre = NULL;
	cur = head->next;
	while (cur) {
		last = cur->next;
		cur->next = pre;
		pre = cur;
		cur = last;
	}

	head->next = pre;

	return 0;
}

static int invert_stack(struct Node *head)
{
	struct Node *node, *sp;

	sp = head->next;
	head->next = NULL;

	while (sp) {
		node = sp;
		sp = sp->next;
		node->next = head->next;
		head->next = node;
	}

	return 0;
}

static int invert(struct Node *head)
{
	head->next = __invert(head->next);

	return 0;
}

int inline Insert(struct Node *head, struct Node *node)
{
	node->next = head->next;
	head->next = node;

	return 0;
}

static struct Node *CreateList(size_t len)
{
	int i;
	struct Node *head, *node;
	head = CreateNode(0);

	for (i = 0; i < len; i++) {
		node = CreateNode(i);
	//	printf("%d \n", node->data);
		Insert(head, node);
	}

	return head;
}

void DelNode_val(struct Node *head, Type data)
{
	struct Node *pre, *cur;

	pre = head;
	cur = head->next;

	while (cur) {
		if (cur->data == data) {
			pre->next = cur->next;
			free(cur);
			break;
		}

		pre = cur;
		cur = cur->next;
	}
}

void DelNode(struct Node *node)
{
	printf("free %d \n", node->data);
	free(node);
}

void __show(struct Node *node)
{
	printf("%d	", node->data);
}

int traverse(struct Node *head, handler hand) {
	struct Node *last, *cur = head->next;
//fixme	 hand
	if (hand == DelNode)
		(*head).next = NULL;

	while (cur) {
		last = cur->next;
		hand(cur);
		cur = last;
	}

	return 0;
}

int Destroy(struct Node *head)
{
	traverse(head, DelNode);

	return 0;
}

int Show(struct Node *head)
{
	traverse(head, __show);

	return 0;
}

int main(int argc, char *argv[])
{
	struct Node *list;

	list = CreateList(10);
	Show(list);
	putchar('\n');

	//invert(list);
//	invert_iterate(list);
//	invert_stack(list);
//	DelNode(list, 0);
	Destroy(list);
	Show(list);
	putchar('\n');

	return 0;
}
