#pragma once

typedef int Type;

struct Node {
	Type data;
	struct Node *next;
};

static inline struct Node *InsertNode(struct Node *first, struct Node *node)
{
	node->next = first;
	first = node;

	return first;
}

int TraverseList(struct Node *first);
struct Node *CreateList_F(size_t len);
struct Node *DelNode(struct Node *first, Type data);
