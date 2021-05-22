#!/bin/bash

arg1=$1

g++ $1.cpp -lglut -lGL -o $1 & ./$1

