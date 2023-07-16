
#ifndef TYPES_H
#define TYPES_H
//********DECLARATIONS****************
//consts
#define NUM 9-2    //number of triangles you want in each quadrant*3 (must be multiple of 3 to work right)

#define fps 30;
#define uplims 15; //upper limit in seconds... this is not seconds idk
#define uplimf fps*uplims;

typedef struct
{
    float lof[4][NUM][2]; //0 = left, 1 = bottom, 2 = top, 3 = right
} tripnts;

typedef struct 
{
  float pts[4][4];
} frame;

typedef struct n {
	struct n *next;
	tripnts pts;
	int fNum;	//frame number
} node;


#endif
