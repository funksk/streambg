#include <stdio.h>
#include "lList.h"
#include "types.h"

int main(int argv, char *argc[])
{
	tripnts test;
	node *testPtr;
	int i, j, k;

	printf("test\n");

	for(i=0;i<4;i++)
	{
		for(j=0;j<NUM;j++)
		{
			for(k=0;k<2;k++)
			{
				if(k % 2)
					test.lof[i][j][k] = 0;
				else
					test.lof[i][j][k] = 1;
			}
		}
	}

	printf("test2\n");

	push(test, 1);

	printf("test3\n");

	(testPtr) = getTop();
	printf("dude, guess what, %f, %d !!\n",testPtr->pts.lof[0][0][0], testPtr->fNum);

	printf("holy shit\n");

	return 0;
}
