/** @file
 * Interface of RedBlack tree
 * @author Marian Dabrowski
 */
#ifndef __RBTREE_H__
#define __RBTREE_H__

#include "node.h"
#include <assert.h>

/**
  * Structure that represents the red black tree
  */
typedef struct RBTree {
  Node *root;
} RBTree;

/**
 * Constructs a new instance of a RBTree
 * @return a new instance of a red black tree
 */
static inline RBTree *newRBTree()
{
	RBTree *rbtree = malloc(sizeof(RBTree));
	assert(rbtree != NULL);
	rbtree->root = NULL;
	return rbtree;
}

/**
 * Checks if the RBTree is empty
 * @param[in] rbtree: a instance of a RBTree
 * @return if the rbtree is empty
 */
static inline bool isEmpty(RBTree *rbtree)
{
	return (rbtree->root == NULL);
}

/**
 * Checks if a node was inserted into a RBTree
 * @param[in] rbtree: the RBTree where we check if the node is inserted
 * @param[in] node: node that we check if it was inserted
 * @return if the node is inserted into this rbtree
 */
static inline bool isInserted(RBTree *rbtree, Node *node)
{
	return ((rbtree->root == node) || (node->parent));
}

/**
 * Rotates the tree left in the node position
 * @param[in] rbtree: tree to be rotated
 * @param[in] node: node to be rotated
 */
void rotateLeft(RBTree *rbtree, Node *node);

/**
 * Rotates the tree right in the node position
 * @param[in] rbtree: tree to be rotated
 * @param[in] node: node to be rotated
 */
void rotateRight(RBTree *rbtree, Node *node);

/**
 * Prints the rbtree in preorder left right
 * @param[in] rbtree: tree to be printed
 */
void printRBTreePLR(RBTree *rbtree);

/**
 * Prints the node in preorder left right
 * @param[in] node: node to be printed
 */
void printTreePLR(Node *node);

/**
 * Find inoreder successor of a node
 * @param[in] node: node which successor we wish to find
 * @return the inoreder successor
 */
Node *findInorderSuccessor(Node *node);

/**
 * Finds the pointer to a node
 * @param[in] rbtree: the tree to look into
 * @param[in] value: the value to look for
 * @return the pointer to the node with value
 */
Node *findNode(RBTree *rbtree, int value);

/**
 * Inserts as if into a BST tree
 * @param[in] rbtree: tree into which the node is to be inserted
 * @param[in] node: node to be inserted
 */
void insertBST(RBTree *rbtree, Node *node);

/**
 * Inserts a node into a RBTree
 * @param[in] rbtree: the tree into which we want to insert
 * @paramp[in] value: value that we insert
 */
void insert(RBTree *rbtree, int value);

/**
 * Fixes the violation after inserting a node
 * @param[in] rbtree: tree to be fixed
 * @param[in] node: node that has been inserted
 */
void fixViolation(RBTree *rbtree, Node *node);

/**
 * Repairs in loop the violation after deleting a node
 * @param[in] rbtree: tree to be repaired
 * @param[in] node: node that was changed
 */
void repairInLoop(RBTree *rbtree, Node *node);

/**
 * Deletes the value from the tree
 * @param[in] rbtree: tree where the value shall be deleted from
 * @param[in] value: value that shall be deleted
 */
void deleteNode(RBTree *rbtree, int value);

#endif /*__RBTREE_H__*/
