/*
~~Stream Background Project~~
init.h init.c
by Andrew Yankovich
Document Created on 16-JUL-2023
Last edited 16-JUL-2023

Description:
create the work to be done from the configuration inferred before.
*/

#ifndef INIT_H
#define INIT_H
#include "types.h"

float randfloat(float, float);
tripnts inc(tripnts, tripnts, tripnts);
tripnts *createKeyframes(long long);
node *createLL(tripnts*,long long);
node *initSequence(config);

#endif
