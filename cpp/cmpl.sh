#!/bin/bash

arg1=$1

g++ -c $arg1.cpp -o $arg1.o& g++ $arg1.o -o $arg1 -lsfml-graphics -lsfml-window -lsfml-system & ./$arg1

