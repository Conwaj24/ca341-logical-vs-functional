#include "core.c"

node *searchTreeForNumber(int number, node *root) {
	if (root->left && number < root->data)
		return searchTreeForNumber(number, root->left);
	if (root->right && number > root->data)
		return searchTreeForNumber(number, root->right);
	return root;
}

node *addNodeToTree(node *n, node *tree);

node *addLeft(node *n, node *tree) {
	if (tree->left)
		return fork( tree, addNodeToTree(n, tree->left), tree->right);
	return fork(tree, n, tree->right);
}

node *addRight(node *n, node *tree) {
	if (tree->right)
		return fork( tree, tree->left, addNodeToTree(n, tree->right));
	return fork(tree, tree->left, n);
}

node *addNodeToTree(node *n, node *tree) {
	if(!n)
		return tree;
	if (n->data < tree->data)
		return addLeft(n, tree);
	return addRight(n, tree);
}

node *removeRoot(node *root) {
	if (root->left)
		return addNodeToTree(root->right, root->left);
	else if (root->right)
		return root->right;
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
