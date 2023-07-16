/*
test for lList.c:
	void push(tripnts, int);
	void append(tripnts, int);
	node *getTop(void);
	void deleteTop(void);

	push several
	append several
	get top & delete top until end
	confirm everything works...
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lList.h"
#include "types.h"

#define TRIPNTAMNT 2
#define RAMWAITS 0

float randfloat(float Min, float Max)
{
  return (((float)rand() / (float)RAND_MAX) * (Max - Min)) + Min;
}

frame frmmkr(float tls[4], float x)
{
  frame tmp;
  //left
  tmp.pts[0][0] = tls[0]-x;
  tmp.pts[0][1] = tls[1]+x;
  tmp.pts[0][2] = tls[0];
  tmp.pts[0][3] = tls[3]-x;
  //top
  tmp.pts[1][0] = tls[0]-x;
  tmp.pts[1][1] = tls[1]+x;
  tmp.pts[1][2] = tls[2]+x;
  tmp.pts[1][3] = tls[1];
  //right
  tmp.pts[2][0] = tls[2];
  tmp.pts[2][1] = tls[1]+x;
  tmp.pts[2][2] = tls[2]+x;
  tmp.pts[2][3] = tls[3]-x;
  //bottom
  tmp.pts[3][0] = tls[0]-x;
  tmp.pts[3][1] = tls[3];
  tmp.pts[3][2] = tls[2]+x;
  tmp.pts[3][3] = tls[3]-x;
  return tmp;
}

tripnts randlist(frame x, tripnts y)
{
  tripnts z;
  int i, j, k;
  for(i = 0;i<=3;i++)
  {
    for(j = 0;j < NUM-1;j++)
    {
      for(k = 0;k<=1;k++)
      {
        do
        {
          z.lof[i][j][k] = randfloat(y.lof[i][j][k]-0.2,y.lof[i][j][k]+0.2);
        }while
        (!(z.lof[i][j][k] > x.pts[i][k*2] && z.lof[i][j][k] < x.pts[i][(k*2)+1]));
      }
    }
  }
  return z;
}

tripnts getlist(frame x)
{
  tripnts y;
  int i;
  for(i = 0; i < NUM-1; i++)  //0 = x, 1 = y
  { 
    y.lof[0][i][0] = randfloat(x.pts[0][0],x.pts[0][1]);//left x
    y.lof[0][i][1] = randfloat(x.pts[0][2],x.pts[0][3]);//left y
    y.lof[1][i][0] = randfloat(x.pts[1][0],x.pts[1][1]);//bottom x
    y.lof[1][i][1] = randfloat(x.pts[1][2],x.pts[1][3]);//bottom y
    y.lof[2][i][0] = randfloat(x.pts[2][0],x.pts[2][1]);//right x
    y.lof[2][i][1] = randfloat(x.pts[2][2],x.pts[2][3]);//right y
    y.lof[3][i][0] = randfloat(x.pts[3][0],x.pts[3][1]);//top x
    y.lof[3][i][1] = randfloat(x.pts[3][2],x.pts[3][3]);//top y
//    printf("y.lof[0][%d][0] = %f \r", j, y.lof[0][j][0]);
//    sleep(5);
//    printf("%f, %f, %f, %f, %f, %f, %f, %f\n", y.lof[0][i][0], y.lof[0][i][1], y.lof[1][i][0], y.lof[1][i][1], y.lof[2][i][0], y.lof[2][i][1], y.lof[3][i][0], y.lof[3][i][1]);
//    if(debugf)
//      fprintf("%f, %f, %f, %f, %f, %f, %f, %f\n", y.lof[0][i][0], y.lof[0][i][1], y.lof[1][i][0], y.lof[1][i][1], y.lof[2][i][0], y.lof[2][i][1], y.lof[3][i][0], y.lof[3][i][1]);
  }
  printf("\n");
  return y;
}

void printTripnts(tripnts x)
{
	int i, j, k;

	for(i = 0;i<=3;i++)
  {
  	printf("%d:\n",i);
    for(j = 0;j < NUM-1;j++)
    {
    	printf("\t%d:\t[",j);
      for(k = 0;k<=1;k++)
      {
      	printf("%d = %.2f ",k,x.lof[i][j][k]);
      }
      printf("]\n");
  	}
  }
}

unsigned short checkTripnts(tripnts x, tripnts y)
{
  int i, j, k;
  printf("**********In checkTripnts*******\n");
  printf("x\n");
  printTripnts(x);
  printf("y\n");
  printTripnts(y);

  for(i = 0;i<=3;i++)
  {
    for(j = 0;j < NUM-1;j++)
    {
      for(k = 0;k<=1;k++)
      {
        //printf("%0.2f == %0.2f\n", x.lof[i][j][k], y.lof[i][j][k]);
        if(x.lof[i][j][k] != y.lof[i][j][k])
          return 1;
      }
    }
  }
  return 0;
}

void cpyTripnts(tripnts *x, tripnts *y)
{
  
  printf("**********In cpyTripnts*******\n");

  memcpy(x,y,sizeof(tripnts));

}


int main(int argv, char *argc[])
{
	tripnts test[TRIPNTAMNT], testVal[TRIPNTAMNT];
	frame tf;
	float f[4];
	node *testPtr;
	int i, j, k;
  float testFlts[2] = {0.0};
  unsigned short flg = 0;
	frame defaultFrame;
  char c;

	f[0] = 0.7;
	f[1] = 0.6;
	f[2] = -1*f[0];
	f[3] = -1*f[1];

  //ensure no garbage data
  for(i=0;i<TRIPNTAMNT;i++)
  {
    memset(&test[i],0,sizeof(tripnts));
    memset(&testVal[i],0,sizeof(tripnts));
  }
	//make a nice beautiful frame
	defaultFrame = frmmkr(f,0.01);

	//generate several tripnts
	for(i=0;i<TRIPNTAMNT;i++)
	{
		test[i] = getlist(defaultFrame);
		printf("list[%d] = \n",i);
		printTripnts(test[i]);
	}

	printf("init generated\n");

	//push a bunch of them

	for(i=0;i<TRIPNTAMNT;i++)
	{
		push(test[i], i);
	}
	printf("all pushed\n");

  if(RAMWAITS)
  {
    printf("check ram (usage), press enter to free & validate...");
    scanf("%c",&c);
  }

  printf("getTop() = \n");
  (testPtr) = getTop();
  printTripnts(testPtr->pts);

  //testFlts[0] = testPtr->pts.lof[0][0][0];
  //testFlts[1] = testPtr->pts.lof[0][0][1];
  
  printf("testFlts[0] = %.2f, testFlts[1] = %.2f\n",testFlts[0],testFlts[1]);

	//pop all back to us
	for(i=0;i<TRIPNTAMNT;i++)
	{
		(testPtr) = getTop();
		deleteTop();
    memcpy(&testVal[i],&testPtr->pts,sizeof(tripnts));
    testVal[i].lof[0][0][0] = testPtr->pts.lof[0][0][0];
    testVal[i].lof[0][0][1] = testPtr->pts.lof[0][0][1];
    //cpyTripnts(&testVal[i], &testPtr->pts);
		//testVal[i] = testPtr->pts;
		printf("testVal[%d] = \n", i);
		printTripnts(testVal[i]);
	}

  printf("testVal[0] = %.2f, testVal[1] = %.2f\n",testVal[0].lof[0][0][0],testVal[0].lof[0][0][1]);
  
  //testVal[0].lof[0][0][0] = testFlts[0];
  //testVal[0].lof[0][0][1] = testFlts[1];

	printf("all Popped\n");

	//validate that's what we had pushed...
  //do some weird while loop shit
  //flip this, use i & j...
  i = 0;
  while(i < TRIPNTAMNT && !flg)
  {
    flg = checkTripnts(testVal[i], test[i]);
    ++i;
  }
  if(flg)
    printf("something went wrong in the transfer...\n");
  else
    printf("all numbers validated, everything works!\n");

	//validate we had free'd ram
  if(RAMWAITS)
  {
  printf("check RAM & press enter to quit...");
  scanf("%c",&c);
  }
	
  return 0;
}
