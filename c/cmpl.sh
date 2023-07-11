#!/bin/bash

arg1=$1

gcc $1.c -lIL -lILU -lILUT -lglut -lGL -o $1 