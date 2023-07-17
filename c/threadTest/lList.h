/*
~~Stream Background Project~~
lList.h lList.c
by Andrew Yankovich
Document Created on 14-JUL-2023
Last edited 16-JUL-2023

Description:
This is an implementation of a singly-linked list,
in the style of a stack (as it pretty much is)

The node in question contains 3 variables of interest for 
this program:
	1. a 3-dimensional array of type tripnts called "pts"
	   for storing the 2-D triangle points
    2. an int called "fNum" which stands for frame number,
       as to keep track of what frame we're on when rendering,
       as well as for the file name

This linked-list implementation reads the head in a
non-destructive manner, because the implementation
of the return function is soft (passes the address)
Deleting the pointer at the same time as passing the address
will only return an address to "garbage data" (i.e. the compiler
doesn't see it as apart of it's memory anymore.)

There is a seperate function to delete the head, and move it on
to the next node. lol. lmao.
*/
#ifndef LLIST_H
#define LLIST_H
#include "types.h"

//internal variables
extern node *head;
extern node *tail;

//tri points & frame number
//public funcz
void push(tripnts, int);
void append(tripnts, int);
node *popHead(void);
//node *getTopDeep(void);
void deleteHead(void);
//private funcz
int isList(void);
void initList(tripnts, int);

#endif
