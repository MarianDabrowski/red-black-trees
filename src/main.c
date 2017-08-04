#include "node.h"
#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	RBTree *rbtree = newRBTree();
	for(int i = 0; i < 12; ++i) insert(rbtree, rand() % 100);
	printRBTreePLR(rbtree);

	deleteNode(rbtree, 83);
	printRBTreePLR(rbtree);

	return 0;
}