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
#include "lList.h"
#include "types.h"

#define TRIPNTAMNT 1

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

void cpyFrameFromNode(tripnts tOut, int fOut, node *in)
{
	int i, j, k;
	for(i = 0;i<=3;i++)
  	{
    	for(j = 0;j < NUM-1;j++)
    	{
      		for(k = 0;k<=1;k++)
      		{
      			tOut.lof[i][j][k] = in->pts.lof[i][j][k];
      		}
  		}
  	}
  	fOut = in->fNum;
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

int main(int argv, char *argc[])
{
	tripnts test[TRIPNTAMNT], testVal[TRIPNTAMNT];
	frame tf;
	float f[4];
	node *testPtr;
	int i, j, k;
	frame defaultFrame;

	f[0] = 0.7;
	f[1] = 0.6;
	f[2] = -1*f[0];
	f[3] = -1*f[1];

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

	//pop all back to us
	for(i=0;i<TRIPNTAMNT;i++)
	{
		(testPtr) = getTop();
		deleteTop();
		cpyFrameFromNode(testVal[i],j,testPtr);
		printf("testVal[%d] = \n", i);
		printTripnts(testVal[i]);
	}

	printf("all Popped\n");

	//validate that's what we had pushed...

	//validate we had free'd ram



	return 0;
}
