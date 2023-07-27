/*
~~Stream Background Project~~
main.c
by Andrew Yankovich
Document Created on 16-JUL-2023
Last edited 16-JUL-2023

Description:
Master program that glues all other
functions together as an entry-point.
The "executive" running all programs,
and housing all global variables

Should do the following in order:
	Dispatch file getter & parser
	Dispatch initializer number-cruncher
	Dispatch supervisor/thread dispatcher
	wrap-up & execute extra code
	exit cleanly

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "lList.h"
#include "parseConfig.h"
#include "init.h"

int main()
{
	config mainConfig;
	node *mainPtr;
	//config logic
	mainConfig = parseFile();
	if(mainConfig.exit == 1)
	{
		printf("wrote config.ini defaults\n");
		return(0);
	}
	else if(mainConfig.exit == 2)
	{
		perror("could not make config.ini. Check your permissions in this folder?\n");
		return(1);
	}
	else if (mainConfig.exit == 3)
	{
		perror("config.ini was corrupted!\n");
		return(1);
	}

	printCurConfig(mainConfig);

	//init
	mainPtr = initSequence(config);

	return 0;
}
