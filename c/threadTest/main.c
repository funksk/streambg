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
#include "lList.h"
#include "types.h"

#define TRIPNTAMNT 10

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

void printTripnts(tripnts x)
{
	int i, j, k;
	for(i = 0;i<=3;i++)
	  {
	    for(j = 0;j < NUM-1;j++)
	    {
	      for(k = 0;k<=1;k++)
	      {
	      	//print
	      }
	  	}
	  }
}	

int main(int argv, char *argc[])
{
	tripnts test[TRIPNTAMNT], testVal[TRIPNTAMNT];
	frame tf = ;
	node *testPtr;
	int i, j, k;

	//generate several tripnts



	//push a bunch of them

	push(test, 1);

	(testPtr) = getTop();

	//pop all back to us

	//validate that's what we had pushed...

	//validate we had free'd ram

	//i'd call that a success



	return 0;
}
