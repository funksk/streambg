/*
~~Stream Background Project~~
parseConfig.h parseConfig.c
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

int getfromf(char* x, FILE* f, int debug);
config parseFile(void);
config setDefaults(void);
void createAndWriteFile(config);

#endif
