#include "core.c"

node *searchTreeForNumber(int number, node *root) {
	if (root->left && number < root->data)
		return searchTreeForNumber(number, root->left);
	if (root->right && number > root->data)
		return searchTreeForNumber(number, root->right);
	return root;
}

node *addNodeToTree(node *n, node *tree) {
	if(!n) {return tree;}

	if (n->data < tree->data) {
		if (tree->left)
			addNodeToTree(n, tree->left);
		else
			tree->left = n;
	} else {
		if (tree->right)
			addNodeToTree(n, tree->right);
		else
			tree->right = n;
	}
	return tree;
}

node *addToTree(int item, node *root) {
	node *n = newNode(item); 
	return addNodeToTree(n, root);
}

node *findNode(int number, node *tree) {
	node *n = searchTreeForNumber(number, tree);
	if (n->data != number)
		n = NULL;
	return n;
}

node *removeRoot(node *root) {
	if (root->left)
		return addNodeToTree(root->right, root->left);
	else if (root->right)
		return root->right;
	else
		return NULL;
}

node *removeNodeFromTree(node* n, node* tree) {
	if (!n)
		return tree;
	if (n == tree)
		return removeRoot(n);

	addNodeToTree(n->left, tree);
	addNodeToTree(n->right, tree);
	return tree;
}
