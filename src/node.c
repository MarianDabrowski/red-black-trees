#include "node.h"

Node *newNode(int data)
{
 	Node *node = malloc(sizeof(Node));
 	if(node == NULL) exit(1);
 	node->data = data;
 	node->color = RED;
 	node->left = NULL;
 	node->right = NULL;
 	node->parent = NULL;
 	return node;
}

void printNode(Node *node)
{
	if(node) {
		if(node->color == RED)
			printf("Node: {Value: %d, Color: RED}\n", node->data);
		else printf("Node: {Value: %d, Color: BLACK}\n", node->data);
	}
	else printf("Node : {NULL, BLACK}\n");
}