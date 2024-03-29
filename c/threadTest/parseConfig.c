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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "parseConfig.h"

//getfromf
//input: a string to fill with data from a file, and a file pointer to grab from. file must be open before calling function.
//output: the characters grabbed from the file, and an aknowledgement that it's not the end of file (I don't think I ever use this though.)
//this function gets some chars from a file
//until a space, or a new line.
int getfromf(char* x, FILE* f, int debug)
{
    int i = 0, a;

    char infc;
    char *str = NULL;
    str = malloc(50*sizeof(char));
    strcpy(str,"");
    infc = fgetc(f);

    //make sure you're not reading after the file
    if(infc == EOF)
        return 1;
    else    //while it's not 0x20(space), 0xFFFFFFFF(bad data), 0x09(tab), or 0x0A(<cr>)
        while((infc != 0x20) && (infc != 0xFFFFFFFF) && (infc != 0x09) && (infc != 0x0A))
        {
            str[i] = infc;
            if(debug) printf("str[%d] = %X, %c, ", i, str[i], str[i]);  //DEBUG
            ++i;
            infc = fgetc(f);    //grab the data
        }
    
    str[i] = '\0';

    if(str == NULL) //let them know if it's null too.
    {
        x = NULL;
        return 1;
    }
    
    i = 0;
    if(debug) printf("\ncopying instring to a malloced string \n");
    while(str[i] != '\0')   //copy the malloced string into our string
    {
        x[i] = str[i];
        if(debug) printf("x[%d] = %X, %c, ", i, x[i], x[i]);  //DEBUG
        if(debug) printf("str[%d] = %X, %c, ", i, str[i], str[i]);  //DEBUG
        ++i;
    }
    x[i] = '\0';
    
    realloc(str, 0);    //reallocate the ram
    return 0;
}

void printCurConfig(config in)
{
	printf("in.drwbx = %d\n",in.drwbx);		//draw our box in the middle
	printf("in.movbx = %d\n", in.movbx);		//don't let them move the box? (shouldn't really exist)
	printf("in.drwfrm = %d\n", in.drwfrm);		//no frame...
	printf("in.drwlns = %d\n",in.drwlns);		//pls draw the lines
	printf("in.lineSize = %0.2f\n",in.lineSize);	//nice fuzzy lines :)
	printf("in.maxIter = %d\n",in.maxIter); //30*2
	printf("in.baseDir = %s\n", in.baseDir);	//for our nice VM stuff
	printf("in.color[0] = %0.3f\n",in.color[0]);	//nice 
	printf("in.color[1] = %0.3f\n",in.color[1]);	//blue
	printf("in.color[2] = %0.3f\n",in.color[2]);	//color :)
}

unsigned short validate(char inBuffer[], char validateStr[], int len)
{
	unsigned short ret = 0;
	char tempstr[255];
	strcpy(tempstr,inBuffer);
	tempstr[len] = '\0';
	if(strcmp(tempstr,validateStr) != 0)
		ret = 3;
	return ret;
}

config parseFile(void)
{
	FILE *f;
	config ret;
	char inBuffer[255];
	char *configCheck[] = {"drawbox=", "movebox=","drawframe=","drawlines=","lineSize=","lengthInSeconds=","baseDir=","colorFloat1=","colorFloat2=","colorFloat3="};
	char configStrs[10][255];
	int chckf = 0;
	int i = 0;
	int j, k;
	printf("hello1\n");
	if((f = fopen("config.ini", "r")) == NULL)
	{
		//set the defaults, make the file, be done with the program!
		ret = setDefaults();
		ret.exit = createAndWriteFile(ret);
	}
	else
	{	//parse the file
		printf("hello2\n");
		while(i < 10)
		{
			if((getfromf(inBuffer,f,0)) != 0)	//drwbx
				ret.exit = 3;	
			else
			{
				if((ret.exit = validate(inBuffer, configCheck[i], strlen(configCheck[i]))) != 3)
				{
					//copy the string over
					j=strlen(configCheck[i]);
					k = 0;
					while(inBuffer[j] != '\0')
					{
						configStrs[i][k] = inBuffer[j];
						++j;
						++k;
					}
					configStrs[i][k] = '\0';
					//clear the buffer
					memset(&inBuffer,'0',strlen(inBuffer));
				}
			}
			i++;
		}
		fclose(f);
		//parse each string got
		ret.drwbx = atoi(configStrs[0]);		//draw our box in the middle
		ret.movbx = atoi(configStrs[1]);		//don't let them move the box? (shouldn't really exist)
		ret.drwfrm = atoi(configStrs[2]);		//no frame...
		ret.drwlns = atoi(configStrs[3]);		//pls draw the lines
		ret.lineSize = atof(configStrs[4]);	//nice fuzzy lines :)
		ret.maxIter = atoll(configStrs[5]); //30*2
		strcpy(ret.baseDir, configStrs[6]);	//for our nice VM stuff
		ret.color[0] = atof(configStrs[7]);	//nice 
		ret.color[1] = atof(configStrs[8]);	//blue
		ret.color[2] = atof(configStrs[9]);	//color :)
	}
	return ret;
}

config setDefaults(void)
{
	config ret;
	ret.drwbx = 1;		//draw our box in the middle
	ret.movbx = 0;		//don't let them move the box? (shouldn't really exist)
	ret.drwfrm = 0;		//no frame...
	ret.drwlns = 1;		//pls draw the lines
	ret.lineSize = 2.0;	//nice fuzzy lines :)
	ret.maxIter = 60; //30*2
	strcpy(ret.baseDir, "/mnt/hgfs/VM_swap/");	//for our nice VM stuff
	ret.color[0] = 0.241;	//nice 
	ret.color[1] = 0.139;	//blue
	ret.color[2] = 0.61;	//color :)

	return ret;
}

int createAndWriteFile(config in)
{
	FILE *f;
	int ret = 1;
	printf("in createAndWriteFile\n");
	if((f = fopen("config.ini","w")) == NULL)
	{
		ret = 2;
	}
	else
	{
		fprintf(f, "drawbox=%d\n", in.drwbx);
		fprintf(f, "movebox=%d\n", in.movbx);
		fprintf(f, "drawframe=%d\n", in.drwfrm);
		fprintf(f, "drawlines=%d\n", in.drwlns);
		fprintf(f, "lineSize=%0.1f\n", in.lineSize);
		fprintf(f, "lengthInSeconds=%d\n", 2);
		fprintf(f, "baseDir=\"%s\"\n", in.baseDir);
		fprintf(f, "colorFloat1=%0.3f\n", in.color[0]);
		fprintf(f, "colorFloat2=%0.3f\n", in.color[1]);
		fprintf(f, "colorFloat3=%0.3f\n", in.color[2]);
	}
	fclose(f);
	printf("leaving creatandriwirtfile\n");
	return ret;
}

