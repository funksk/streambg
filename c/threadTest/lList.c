#include <stdio.h>
#include <stdlib.h>
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
	/*DEBUG!!!!!!!!!!! PLS DELETE!!!!!!!!!!!!*/
	printf("x->pts.lof[0][0] = %0.2f\n", x->pts.lof[0][0][0]);
	printf("x->pts.lof[0][1] = %0.2f\n", x->pts.lof[0][0][1]);
	printf("x->pts.lof[1][0] = %0.2f\n", x->pts.lof[0][1][0]);
	printf("x->pts.lof[1][1] = %0.2f\n", x->pts.lof[0][1][1]);
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

node *getTop()
{
	return head;
}

void deleteTop(void)
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
