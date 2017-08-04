all: rbtreeExecute
clear:
	rm *.o

rbtreeExecute: main.o node.o rbtree.o
	gcc main.o node.o rbtree.o -o rbtreeExecute

rbtree.o: rbtree.c node.h
	gcc -c rbtree.c

node.o: node.c
	gcc -c node.c

main.o: main.c node.h rbtree.h
	gcc -c main.c
