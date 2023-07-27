#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "init.h"

float randfloat(float Min, float Max)
{
  return (((float)rand() / (float)RAND_MAX) * (Max - Min)) + Min;
}

tripnts inc(tripnts c, tripnts n, tripnts w)
{
  float ut;
  tripnts ret;
  for(i = 0;i<=3;i++)
  {
    for(j = 0;j < NUM-1;j++)
    {
      for(k = 0;k<=1;k++)
      {
        if(n.lof[i][j][k]>w.lof[i][j][k])
        {
          ut = n.lof[i][j][k] - c.lof[i][j][k];
          ret.lof[i][j][k] = w.lof[i][j][k]+(ut/uplimf);
        }
        else if(n.lof[i][j][k]<w.lof[i][j][k])
        {
          ut = c.lof[i][j][k] - n.lof[i][j][k];
          ret.lof[i][j][k] = w.lof[i][j][k]-(ut/uplimf);
        }
//        if(i == 0 && j == 0 && k == 0)
//          printf("ut = %f\n",ut);
        /*
        printf("ret.lof[%d][%d][%d] = %f\n",i,j,k,ret.lof[i][j][k]);
        if(debugf)
        {
           fprintf(f, "ret.lof[%d][%d][%d] = %f\n",i,j,k,ret.lof[i][j][k]);
        }*/
      }
//      sleep(1);
    }
  }
  return ret;
}

tripnts *createKeyframes(long long x)	//take the maximum iteration...
{
	tripnts *ret;

}

node *createLL(tripnts*,long long x)
{
	node *ret;
	return ret;
}

node *initSequence(config in)
{
	node *ret;
	tripts keyframes[TRIPNTBUFF];
	

	keyframes = createKeyframes(in.maxIter);

	ret = createLL(keyframes, in.maxIter);

	return ret;
}
