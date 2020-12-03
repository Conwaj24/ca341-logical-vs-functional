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

