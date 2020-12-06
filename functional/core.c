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

node *replace(node *old, node *new) {
	if (!new) {
		freeTree(old);
		return new;
	} if (old != new) {
		replace(old->left, new->left);
		replace(old->right, new->right);
	}
	free(old);
	return new;
}

typedef struct list {
	struct list *next;
	node *data;
} list;

list *newList(node *data) {
	if (!data)
		return NULL;
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

list *endofList(list *l) {
	for (;l->next;l=l->next) {}
	return l;
}

list *concatList(list *l0, list *l1) {
	if (!l0)
		return l1;
	if (!l1)
		return l0;
	endofList(l0)->next = l1; //I could use another fork method here but lists aren't essential and I think you get the idea
	return l0;
}

int listLen(list *l) {
	if (!(l->next))
		return 1;
	return 1 + listLen(l->next);
}


