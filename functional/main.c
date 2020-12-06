#include "tree.c"
#include <stdbool.h>

node *insert(int x, node *tree) {
	return addNodeToTree( newNode(x), tree);
}
bool search(int x, node *tree) {
	return searchTreeForNumber(x, tree)->data == x;
}
list *preorder(node *tree) {
	return concatList(
		newList(tree),
		concatList(
			preorder(tree->left),
			preorder(tree->right)
		)
	);
}
list *inorder(node *tree) {
	return concatList(
		inorder(tree->left),
		concatList(
			newList(tree),
			inorder(tree->right)
		)
	);
}
list *postorder(node *tree) {
	return concatList(
		postorder(tree->left),
		concatList(
			postorder(tree->right),
			newList(tree)
		)
	);
}
node *remove(int key, node *tree) {
	if (!search(key, tree))
		return tree;
	return removeNodeFromTree(searchTreeForNumber(key, tree), tree);
}
