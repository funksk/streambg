#!/bin/bash

arg1=$1

gcc $1.c -lglut -lGL -o $1 & ./$1

