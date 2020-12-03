#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NOTNULL(n) if(!n) {return;}

typedef struct {
	char *name;
	char *address;
	int number;
} phonebookEntry;

typedef struct node {
	struct node *parent;
	struct node *left;
	struct node *right;
	phonebookEntry *data;
} node;

node *root;

phonebookEntry *newPhonebookEntry(char *name, char *address, int number) {
	phonebookEntry *out = malloc(sizeof(phonebookEntry));
	out->name = strdup(name);
	out->address = strdup(address);
	out->number = number;
	return out;
}

void freePhonebookEntry(phonebookEntry *pbe) {
	free(pbe->name);
	free(pbe->address);
	free(pbe);
}

node *newNode(phonebookEntry *data) {
	node *out = malloc(sizeof(node));
	out->data = data;
	out->left = NULL;
	out->right = NULL;
	out->parent = NULL;
	return out;
}

void freeNode(node *n) {
	NOTNULL(n)
	freePhonebookEntry(n->data);
	free(n);
}

void freeTree(node *n) {
	NOTNULL(n)
	freeTree(n->left);
	freeTree(n->right);
	freeNode(n);
}

void displaypbe(phonebookEntry *pbe){
	fprintf(stdout, "%s\n%s\n%i\n", pbe->name, pbe->address, pbe->number);
}

void display(node *n){
	if (n)
		displaypbe(n->data);
	else
		printf("NULL\n");
	printf("");
}

node *searchTreeForNumber(int number, node *root) {
	if (root->left && number < root->data->number)
		return searchTreeForNumber(number, root->left);
	if (root->right && number > root->data->number)
		return searchTreeForNumber(number, root->right);
	return root;
}

void addNodeToTree(node *n) {
	NOTNULL(n)
	node *parent = searchTreeForNumber(n->data->number, root);
	n->parent = parent;
	if (n->data->number < parent->data->number) {
		node *orphan = parent->left;
		parent->left = n;
		addNodeToTree(orphan);
	} else {
		node *orphan = parent->right;
		parent->right = n;
		addNodeToTree(orphan);
	}
}

void addToTree(phonebookEntry *item) {
	node *n = newNode(item); 
	addNodeToTree(n);
}

node *findNode(node *root, int number) {
	node *n = searchTreeForNumber(number, root);
	if (n->data->number != number)
		n = NULL;
	return n;
}

void kidnap(node *n) {
	//remove node from its parent
	NOTNULL(n->parent)
	if (n->parent->left == n)
		n->parent->left = NULL;
	else
		n->parent->right = NULL;
}

void setAsRoot(node *n) {
	root = n;
	n->parent=NULL;
}

void removeNodeFromTree(node* n) {
	kidnap(n);
	if (n == root) {
		if (n->left) {
			setAsRoot(n->left);
			addNodeToTree(n->right);
		} else if (n->right)
			setAsRoot(n->right);
		else {
			root = NULL;
			printf("Warning! Tree is empty", stderr);
		}
	} else {
		addNodeToTree(n->left);
		addNodeToTree(n->right);
	}
	freeNode(n);
}

void removeFromTree(int key) {
	node *n = findNode(root, key);
	if (n != NULL) 
		removeNodeFromTree(n);
}

