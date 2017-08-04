#include "rbtree.h"

void rotateLeft(RBTree *rbtree, Node *node)
{
  if(node && node->right) {

    Node *temp = node->right;
    node->right = temp->left;
    temp->left = node;

    if(node->right) node->right->parent = node;
    temp->parent = node->parent;
    node->parent = temp;

    if(temp->parent) {
      if(node == temp->parent->left) temp->parent->left = temp;
      else temp->parent->right = temp;
    }
    else rbtree->root = temp;
  }
}

void rotateRight(RBTree *rbtree, Node *node)
{
  if(node && node->left) {
    Node *temp = node->left;
    node->left = temp->right;
    temp->right = node;

    if(node->left) node->left->parent = node;
    temp->parent = node->parent;
    node->parent = temp;

    if(temp->parent) {
      if(node == temp->parent->left) temp->parent->left = temp;
      else temp->parent->right = temp;
    }
    else rbtree->root = temp;
  } 
}

void insertBST(RBTree *rbtree, Node *node)
{
  bool inserted = false;
  Node *itterator = rbtree->root;
  if(isEmpty(rbtree)) {
    inserted = true;
    rbtree->root = node;
  }
  else {
    while(!inserted) {
      if(itterator->data < node->data) {
        if(itterator->right == NULL) {
          itterator->right = node;
          node->parent = itterator;
          inserted = true;
        }
        else itterator = itterator->right;
      }
      else if(itterator->data > node->data) {
        if(itterator->left == NULL) {
          itterator->left = node;
          node->parent = itterator;
          inserted = true;
        }
        else itterator = itterator->left;
      }
      else inserted = true;
    }
  }
}

void printTreePLR(Node *node)
{
  if(node) {
    printNode(node);
    printTreePLR(node->left);
    printTreePLR(node->right);
  }
  else printNode(node);
}

void printRBTreePLR(RBTree *rbtree)
{
  printTreePLR(rbtree->root);
  printf("############################################################\n");
}

void insert(RBTree *rbtree, int value)
{
  Node *node = newNode(value);
  insertBST(rbtree, node);
  if(isInserted(rbtree, node)) fixViolation(rbtree, node);
  else free(node);
}

void fixViolation(RBTree *rbtree, Node *node)
{
  Node *parent = NULL, *grandParent = NULL, *uncle = NULL;

  while((node != rbtree->root) && (node->color == RED) &&
     (node->parent->color == RED)) {

    parent = node->parent;
    grandParent= parent->parent;
    uncle = grandParent->right;
    if(uncle == parent) uncle = grandParent->left;

    if(uncle && uncle->color == RED) {
      setColor(uncle, BLACK);
      setColor(parent, BLACK);
      setColor(grandParent, RED);
      node = grandParent;
    }

    else if(parent == grandParent->left) {
        if(node == parent->right) {
          rotateLeft(rbtree, parent);
          node = parent;
          parent = node->parent;
        }
        rotateRight(rbtree, grandParent);
        swapColors(parent, grandParent);
        node = parent;
    }

    else {
        if(node == parent->left) {
          rotateRight(rbtree, parent);
          node = parent;
          parent = node->parent;
        }
        rotateLeft(rbtree, grandParent);
        swapColors(parent, grandParent);
        node = parent;
    }
  }
  rbtree->root->color = BLACK;
}

Node *findNode(RBTree *rbtree, int value)
{
  Node *node = NULL, *itterator = rbtree->root;
  while(node == NULL && itterator) {
    if(itterator->data < value) itterator = itterator->right;
    else if(itterator->data > value) itterator = itterator->left;
    else node = itterator;
  }
  return node;
}

Node *findInorderSuccessor(Node *node)
{
  Node *successor = node->right;
  while(successor->left) successor = successor->left;
  return successor;
}

void deleteNode(RBTree *rbtree, int value)
{
  Node *node = findNode(rbtree, value), *successor = NULL, *parent = NULL;
  Node *child = NULL;

  if(node) {
    if(node->left && node->right) {
      //covert into case where there are 0 or 1 child
      successor = findInorderSuccessor(node);
      node->data = successor->data;
      node = successor;
    }
    if(node->color == RED) {
      parent = node->parent;
      if(parent->left == node) parent->left = NULL;
      else parent->right = NULL;
      free(node);
    }
    else if((node->left && node->left->color == RED) ||
            (node->right && node->right->color == RED)) {
      parent = node->parent;
      child = node->left;
      if(child == NULL) child = node->right;

      if(parent->left == node) parent->left = child;
      else parent->right = child;
      free(node);
      setColor(child, BLACK);
    }
    else repairInLoop(rbtree, node);
  }
}


void repairInLoop(RBTree *rbtree, Node *node)
{
  Node *parent = NULL;
  bool termianted = false;

  while(!termianted) {
    parent = node->parent;
    if(node == rbtree->root) {
      free(node);
      rbtree->root = NULL;
      termianted = true;
    }
    else if(parent->color == BLACK && parent->right->color == RED) {
      rotateLeft(rbtree, parent);
      swapColors(node->parent, node->parent->parent);
    }
    else if(parent->color == BLACK && parent->right->color == BLACK) {
      setColor(parent->right, RED);
      node = parent;
    }
    else if(parent->color == RED && parent->right->color == BLACK) {
      swapColors(parent, parent->right);
      setColor(node, BLACK);
      termianted = true;
    }
    else if(parent->color == BLACK && parent->right->color == BLACK
      && parent->right->left && parent->right->left->color == RED) {
      rotateRight(rbtree, parent->right);
      swapColors(parent->right, parent->right->right);
    }
    else {
      rotateLeft(rbtree, parent->right);
      swapColors(node->parent, node->parent->parent);
      setColor(node, BLACK);
      setColor(node->parent->parent->right, BLACK);
      termianted = true;
    }
  }
}