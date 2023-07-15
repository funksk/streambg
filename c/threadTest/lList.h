/*



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
node *getTop(void);
void deleteTop(void);
//private funcz
int isList(void);
void initList(tripnts, int);

#endif
