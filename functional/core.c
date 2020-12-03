#include <stdlib.h>

typedef struct node {
	struct node *left;
	struct node *right;
	int data;
} node;

node *newNode(int data) {
	node *out = malloc(sizeof(node));
	out->data = data;
	out->left = NULL;
	out->right = NULL;
	return out;
}

void freeTree(node *tree) {
	if(!tree)
		return;
	freeTree(tree->left);
	freeTree(tree->right);
	free(tree);
}

node *fork(node *n, node *left, node *right) {
	node *new = newNode(n->data);
	new->left = left;
	new->right = right;
	return new;
}

node *copy(node *n) {
	return fork(n, n->left, n->right);
}

node *replace(node *old, node *new);

typedef struct list {
	struct list *next;
	int data;
} list;

list *newList(int data) {
	list *out = malloc(sizeof(list));
	out->data = data;
	out->next = NULL;
	return out;
}

void freeList(list *l) {
	if (l->next)
		freeList(l->next);
	free(l);
}

int listLen(list *l) {
	if (!(l->next))
		return 1;
	return 1 + listLen(l->next);
}
