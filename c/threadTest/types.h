/*
~~Stream Background Project~~
types.h
by Andrew Yankovich
Document Created on 14-JUL-2023
Last edited 16-JUL-2023

Description:
This document defines our custom data
types specific to this project.

Mostly structs containing arrays, as
passing these without structs suckts!

*/
#ifndef TYPES_H
#define TYPES_H
//********DECLARATIONS****************
//consts
#define NUM 9-2    //number of triangles you want in each quadrant*3 (must be multiple of 3 to work right)

#define fps 30;
#define uplims 15; //upper limit in seconds... this is not seconds idk
#define t 60*10;
#define dt  0;
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

typedef struct
{
	unsigned int drwbx;		//default 1
	unsigned int movbx;		//default 0
	unsigned int drwfrm;	//default 0
	unsigned int drwlns;	//default 1
	float lineSize;			//default 2.0 (for fuzzier lines)
	unsigned long maxIter; 	//30 * seconds * minutes * hours
	char baseDir[255];		//default "/mnt/hgfs/VM_swap/" because...
	float color[3];			//default 0.241, 0.139, 0.61
	unsigned short exit;	//do we exit or not?
} config;



#endif
