/*
~~Stream Background Project~~
lList.h lList.c
by Andrew Yankovich
Document Created on 14-JUL-2023
Last edited 16-JUL-2023

see lList.h for a detailed description.
google "singly linked list" if this code confuses you.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lList.h"
#include "types.h"

node *head;
node *tail;

//tri points & frame number
void push(tripnts pntsIn, int fNumIn)
{
	node *x = malloc(sizeof(node));

	if(head != NULL)
	{
		x->next = head;
	}
	
	head = x;

	x->pts = pntsIn;
	x->fNum = fNumIn;
}

void append(tripnts pntsIn, int fNumIn)
{
	node *x = malloc(sizeof(node));
	node *y = head;

	x->pts = pntsIn;
	x->fNum = fNumIn;

	while(y->next != NULL)
	{
		y = y->next;
	}

	y->next = x;
}

node *popHead()
{
	return head;
}

/*
//does not work...
node *getTopDeep()
{
	printf("1\n");
	node *x = malloc(sizeof(node));
	printf("2\n");
	memcpy(&x, &head, sizeof(node));
	printf("3\n");
	printf("%.2f\n",x->pts.lof[0][0][0]);
	return x;
}
*/

void deleteHead(void)
{
	node *x = malloc(sizeof(node));

	x = head;

	head = head->next;

	free(x);
}

int isList(void)
{
	if(head == NULL)
	{
		return 1;
	}
	return 0;
}
