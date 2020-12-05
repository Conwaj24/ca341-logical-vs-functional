#include "tree.c"
#include <stdbool.h>

node *insert(int x, node *tree) {
	return addNodeToTree( newNode(x), tree);
}
bool search(int x, node *tree) {
	return searchTreeForNumber(x, tree)->data == x;
}
node *preorder(node *tree);
node *inorder(node *tree);
node *postorder(node *tree);

node *remove(int key, node *tree) {
	if (!search(key, tree))
		return tree;
	return removeNodeFromTree(searchTreeForNumber(key, tree), tree);
}
