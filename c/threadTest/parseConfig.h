/*
~~Stream Background Project~~
main.c
by Andrew Yankovich
Document Created on 16-JUL-2023
Last edited 16-JUL-2023

Description:
parses config file for config stuff
if not, creates default config file & exits w/ a zero (?)
*/

#ifndef PCONFIG_H
#define PCONFIG_H
#include "types.h"

config parseFile(void);
config setDefaults(void);
void createFile(char*);

#endif
