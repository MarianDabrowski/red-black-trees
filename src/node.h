/** @file
 * Interface of Node
 * @author Marian Dabrowski
 */

#ifndef __NODE_H__
#define __NODE_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/**
 * Type of enum representing the color
 */
typedef enum {RED, BLACK} Color;

/**
  * Structure that represents the Node
  */
typedef struct Node {
    int data;
    Color color;
    struct Node *left, *right, *parent;
} Node;

/**
 * Constructs a new instance of a node
 * @param[in] data: piece of data of the new instance of a node
 * @return new Node instance
 */
Node *newNode(int data);

/**
 * Prints the properties of a node to console as std output
 * @param[in] node: the node which properties will be printed
 */
void printNode(Node *node);

/**
 * Sets the color of a node
 * @param[in] node: node which color will be set
 * @param[in] color: color that the node will be colored
 */
static inline void setColor(Node *node, Color color)
{
	if(node) {
		node->color = color;
	}
}

/**
 * Changes the color of nodes, so that node1 has the color of node2
 * and node2 has the color of node1
 * @param[in] node1: node that color is swapped
 * @param[in] node2: node that color is swapped
 */
static inline void swapColors(Node *node1, Node *node2)
{
	Color c = node1->color;
	node1->color = node2->color;
	node2->color = c;
}

#endif /*__NODE_H__*/