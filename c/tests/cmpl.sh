#!/bin/bash

arg1=$1

#gcc $1.c -lglut -lGL -lil -o $1 

#just for test9, but will work for all
gcc $1.c -lIL -lILU -lILUT -lglut -lGL

