/*
SIL4 Systems SSD Testing Tool
by Andrew Yankovich
Prompt:
Writes data to a drive at a specified speed (megabytes per second) (1, 10, then 20)
every so often (minute), grabs data and reports it to file (csv file)
data to grab: date (UNIX TIME), achieved write speed, current temperature


TODO:
remove all temperature and reporting things

write 1GB of data, with a small buffer that does not make it go at full speed (unless we want to)
create two threads, one copying the data, the other calculating how fast we went
copy at a speed for a minute

colloquialisms:
C refers to our drive, D refers to what I'm writing to. just makes it easier for me to understand, doesn't make any sense in the context of the prgrm.
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>
#include <sys/types.h>  // for time type, etc.
#include <unistd.h>     // for sysconf()
#include <dirent.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#ifdef unix
  #define CLK_TCK sysconf(_SC_CLK_TCK)
#endif

#define CRCTIME	30*6	//time to checksum, 30 minutes*every 10 seconds
#define DATATIME	8*60*6//time to ramp up speed to write at - 8hours*60minutes*6 times per minute
//#define CRCTIME	1	//DEBUG TIME
//#define DATATIME	1//DEBUG TIME
#define CSVTIME 5*60	//5 minutes - maybe not used
#define NOTMAXSPEED 1
#define BILLION  1000000000L;

int prevwait;
short running = 1;
short writing = 0;
int numTimes = 0;

typedef struct sp
{
  double userMBPS;
  double clockMBPS;
} speed;


void help();
void performanceChecker(); //never used
speed writeDataToD(char[], char*, unsigned int); //write data to drive
speed simpleWriteData(char[],int,char*,int);
speed fastSimpleWrite(char, int, char*);
void genoutf(char[], char[], char*);	//generate dir for outfile
void grabData(char[], char**);	//grab data into ram to send out
int readDataFromD();	//will be used for crc
int checkData();	//crc the data
int getTemp(char[]);	//get tempearture from command
void jotData(int, int, speed, char[]);	//jot data to csv
int checkMount(char *, char[]);	//get dir for where drive is mounted on computer
void adjust(double, int);	//needs tweaking, not used
void cycle(char*, unsigned long);	//used for crc (not yet)
unsigned int testWriteSpeed(int,char[]);
void simpledelay(int i)		//there is no better delay in linux I guess. terrible.
{
	while(i != 0)
		i--;
}
void intHandler(int dummy)
{
	running = 0;
}

int main(int argc, char *argv[])
{
	int i, j, k, curtemp, runcrc = CRCTIME, MBpsToWrite;
#if NOTMAXSPEED
	int count1 = 0, count2 = 0;	//count1 determines r/w speed, count2 determines how often we should check if the time is true (determined on how fast the r/w speed is)
#else
	int count1 = 2, count2 = 0;
#endif
	unsigned long cycleAmnt = 0;
	unsigned int testedWait;
	time_t t1, t2, initTime;
  struct tm *curtime, *curtime1;
  FILE *outf, *inf, *tempf;
  char fnameout[50] = "", fnamein[50] = "", tempstr[50] = "", curDrive[20] = "", fnameD[50] = "";
  char command[50] = "";
  char fnamein1[50] = "./1gb";
  char dDir[50] = "", fnameD1[50] = "";
  char *infc = NULL;
  speed s1;
  signal(SIGINT, intHandler);
	if(argc < 2 || argv[1] == "-h")
		help();
	else
	{
    //performanceChecker();
		//check if it is mounted, if not then mount it
		//if it doesn't exist, tell the user then leave
		//does the thing exist?
		strcpy(curDrive, "/dev/");
		strcat(curDrive, argv[1]);
		printf("curDrive = %s\n",curDrive);

		strcpy(fnameout, "./LinuxOut/");
		snprintf(tempstr,sizeof(tempstr), "%ld", initTime);
		strcat(fnameout, tempstr);
		strcpy(tempstr, "");
		strcat(fnameout,".csv");

		if(access(curDrive, F_OK) == 0)	//if the disk works
		{
			//see where drive is mounted
			if(checkMount(dDir, curDrive) == -1)
			{
				perror("we could not find, or write to the drive specified. sorry\n");
				exit(2);
			}
			printf("About to write to drive at dir %s\n", dDir);

			//check if 2nd passed num is a speed...
			/*
			for(i=0;i<strlen(argv[2]);i++)
				if(argv[2][i] >= '0' && argv[2][i] <= '9')
				{
					perror("please enter a MBps for the second argument\n");
					exit(2);
				}
			*/
			MBpsToWrite = atoi(argv[2]);
			printf("Writing at %dMBps\n",MBpsToWrite);
			//calculate what the waiting time should be by creating and testing the thing with a test file

			testedWait = testWriteSpeed(MBpsToWrite, dDir);

			//exit(0);
			//TODO: this is not continuous streaming of data. fix that w/ threads!!
			//				does this problem even matter that much? it's pretty much continuous
			//TODO: cycle the file around when printing it. do it somehow HERE!
			//make init of wait for each mb idea
      //INIT OUT FILE NAME, AND OUT DATA!!!
      strcpy(command, "rm ");
      strcat(command, dDir);
      strcat(command, "/1gb*");
      system(command);
      genoutf(dDir, fnamein1, fnameD);
      grabData(fnamein1, &infc);
      		//dispatch reading thread
			while(running)
			{
				s1 = writeDataToD(fnameD, infc, testedWait);
				//printf("curDrive (later) = %s\n",curDrive);
				curtemp = getTemp(curDrive);
				jotData(time(&t2),curtemp,s1,fnameout);
				//strcpy(fnameD, fnameD1);
				if((numTimes % 10) == 0)
					system(command);
			}
			realloc(infc, 0);
			system(command);
		}
  	else
  		perror("There is no drive specified, try again.\n");

	}
	return 0;
}

//would be used to check what the computer is capable of, then adjusting the wait from it
//not used yet. needs work.
void performanceChecker()
{
  int i = 500, j;
  double num = 1.0;
  clock_t c1, c2;
  c1 = clock();
  while(i != 0)
    i--;
  c2 = clock();
  num = (double)(c2-c1)/CLOCKS_PER_SEC;
  printf("num = %f\n",num);
}

void help()
{
	printf("Usage: contWrite*.o <drive to test> <Speed of MBps> || -h\n-h: prints this help\n <drive to test>: E.G. sdb1, sdc1 ...\n<Speed of MBps>: E.G. 1, 5, 10, 20 ...\n");
}
//don't create a file, create the file in MALLOC'd RAM, write to drive, delete the file
//get user time, calc MBps, do some algebra to get to goal time
//
unsigned int testWriteSpeed(int goalMBPS, char dDir[])
{
	FILE *outf;
	unsigned int waitTime, numOWaits = 0;
	double num, diff;
	unsigned long i=0,j=0;
	double runMBPS, totT, timeClock;
	double userMBPS, clockMBPS, goalSecs;
	unsigned long dataAmnt = 1000000 * 100;	//100mb for testing sounds good
	char outfname[50] = "";
	char *tempc = malloc(dataAmnt * sizeof(char));
	time_t t1, t2;
	clock_t c1, c2;	//very unfortunate...
	struct timespec tp1, tp2;
	//gen data
	while(i != dataAmnt)	//100mb
	{
		tempc[i] = (rand() % (95 - 32 + 1)) + 32;
		++i;
	}
	//get outfile
	genoutf(dDir, "./test.txt", outfname);	//get our outfile name
	printf("outfname = %s\n",outfname);

	//get time
	i = 0;
	outf = fopen(outfname, "w");
	time(&t1);
	clock_gettime(CLOCK_REALTIME, &tp1);

	//write to file
	while(i != dataAmnt)
	{
		fputc(tempc[i], outf);
		++i;
		if((i%1000000) == 0) 
			usleep(0);//fsync(fileno(outf));
		//printf("i = %ld\n",i);
	}
	fflush(outf);
	clock_gettime(CLOCK_REALTIME, &tp2);
	//get time
	time(&t2);
	//c2= clock();

	//close file
	fclose(outf);

	//calc user, clock time, MBps
	totT = ( tp2.tv_sec - tp1.tv_sec ) + (double)( tp2.tv_nsec - tp1.tv_nsec ) / (double)BILLION;
	printf("TEST data :\n");
	printf("user time was %ld\n",t2-t1);
	printf("clock time was %f\n",totT);
	userMBPS = (dataAmnt/1000000)/(double)(t2-t1);
	clockMBPS = (dataAmnt/1000000)/totT;
	printf("user mbps was %f\n",userMBPS);
	printf("clock mbps was %f\n",clockMBPS);

	//find x in the algebra equation

	goalSecs = 1/(double)goalMBPS;	//number of seconds per megabyte
	num = (1/clockMBPS);	//seconds per megabyte to write, need to increase this for our goal
	printf("goalSecs = %f\nsecs for each MEGAbyte = %f\n",goalSecs,num);
	if(goalSecs > num)
	{
		diff = goalSecs - num;
		waitTime =(int)(diff * 1e6);
		waitTime/=2;
		printf("diff = %f\nwaitTime = %d\n",diff, waitTime);
	}
	else
	{
		printf("your computer is too slow for this megabyte, sorry!\n");
		exit(2);
	}

	//num1 = //make up the difference
	//waitTime = / timeClock;	//num of waits we have to take for it to work

	//free up ram
	realloc(tempc, 0);
	//delete test file
	if(remove(outfname) == -1)
	{
		printf("Couldn't remove outfile... who cares?\n");
	}
	//return the result
	return waitTime;
}

//get the temperature from a command to jot down.
int getTemp(char drive[])
{
	FILE *fpipe;
	int i = 0, j=0, temp = 0;
	char command[50] = "smartctl ";
	char a[100] = {0}, tempstr[50] = "", str1[50] = "";
	char c;
	strcpy(str1,drive);
	str1[strlen(str1)] = '\0';
	strcat(command, str1);
	strcat(command, " -a | grep 194");
	//printf("command is %s\n",command);

	if (0 == (fpipe = (FILE*)popen(command, "r")))
  {
      perror("popen() failed.");
      exit(2);	//TODO: make this not an exit(2)
  }

  fgets(a, sizeof(a), fpipe);	//grab the data into a

  //printf("a = %s\n", a);
  fclose(fpipe);

  if(strcmp(a, "") == 0)
  {
  	printf("to be able to see temperatures, run this program as root!\n");
    temp = 0;
  }
  else
  {
    i=strlen(a)-11; 
    //printf("a[i] = %d\na[i-1] = %d\n",a[i]&~0x30,a[i-1]&~0x30);
    
    //printf("a[%d] = %X, a[%d] = %X\n",i,a[i],i-1,a[i-1]);

    temp = a[i]&~0x30;	//quick n dirty atoi
    temp += (a[i-1]&~0x30)*10;
  }

  printf("temp = %d\n",temp);

	return temp;
}

void jotData(int t, int temp, speed s, char fnameout[])
{
	FILE *outf;
	char tempstr[50] = "", str1[50] = "", str2[50] = "", str3[50] = "";
	outf = fopen(fnameout, "a");
	snprintf(tempstr, sizeof(tempstr),"%f",s.clockMBPS);
	snprintf(str3, sizeof(str3),"%f",s.userMBPS);
	snprintf(str1,sizeof(str1),"%d",t);
	snprintf(str2,sizeof(str2),"%d",temp);
	fprintf(outf, "%s,%s,%s,%s", str1, tempstr, str3, str2);
	fputc(0x0D, outf);	//seems to close out a line
	fputc(0x0A, outf);
	fclose(outf);	//close the file for writing
}

void genoutf(char dDir[], char fnamein[], char *outstr)
{
  FILE *inf;
  unsigned long i = 1, j = strlen(dDir);
  char str[50] = "";
  strcpy(str, dDir);

  while(fnamein[i] !='\0')
  {
    str[j] = fnamein[i];
    i++;j++;
  }
  str[j] = '\0';
  strcpy(outstr,str);
}

void grabData(char fnamein[], char** infc)
{
  FILE *inf;
  int i = 0;
  printf("writing infile into ram to access later!\n");
  *infc = malloc(1000000000 * sizeof(char));	//1GB
  inf = fopen(fnamein, "r");
  while(((*infc)[i] = fgetc(inf)) != EOF)
  	++i;
  //infc[i-1] = '\0';
  //printf("infc[i-1] = %c",*infc[i-2]);
  i = 0;
  fclose(inf);
  //printf("c = %s\n",*infc);
}
/*
void cycle(char *data, unsigned long amnt)
{
	//we can memmove
	unsigned long i, j;
	char byte[19999999];	//max amount of bytes to move lol
	for(i=0;i<amnt;i++)
		byte[i] = data[i];
	//move all data from amnt and up to beginning of data pointer
	memmove(*data, *data+amnt,sizeof(data)-amnt);
	//move prev data to end
	j = sizeof(data);
	for(i=0;i<amnt;i++)
	{
		data[j] = byte[i];
		j++;
	}
	//this isn't gonna work first try lmao.
}*/

//try to write some function that every bunch of writes, it checks the speed, and adjusts some sleep() thing
//the only way I could think this could work.
//TODO: make this write continuously, with another thread checking the R/W speed.
//for now, we will just intervene every so often for a little bit. just to get the ball rolling.
speed writeDataToD(char outfdata1[], char *infc, unsigned int wait)
{
	FILE *outf;
	unsigned long i, j, upamnt, dataAmnt;
	double runMBPS, totT;
	double userMBPS, clockMBPS, goalSecs;
	time_t t1, t2;
	clock_t c1, c2;	//very unfortunate...
	char str1[10] = "", str2[10] = "";
	struct timespec tp1, tp2;
	char outfdata[50] = "";
	speed s;
	//get the amount of data being thrown at the device
  	dataAmnt = 1000000000;
	printf("-------------------\n**writing %ld bytes to the usb.**\n",dataAmnt);
	strcpy(outfdata, outfdata1);
	sprintf(str2, "%d", numTimes);
	strcat(outfdata,str2);
	printf("str2 = %s\noutfdata = %s\n",str2,outfdata);
	outf = fopen(outfdata, "w");
	//get time
	i = 0;
	writing = 1;
	time(&t1);
	clock_gettime(CLOCK_REALTIME, &tp1);

	//write to file
	while(i != dataAmnt && running)
	{
		fputc(infc[i], outf);
		++i;
		if((i%1000000) == 0)
			//fsync(fileno(outf));
			usleep(wait);
		//printf("i = %ld\n",i);
	}
	fflush(outf);
	clock_gettime(CLOCK_REALTIME, &tp2);
	//get time
	time(&t2);
	writing = 0;
	//c2= clock();

	//close file
	fclose(outf);

	//calc user, clock time, MBps
	totT = ( tp2.tv_sec - tp1.tv_sec ) + (double)( tp2.tv_nsec - tp1.tv_nsec ) / (double)BILLION;
	printf("TEST data :\n");
	printf("user time was %ld\n",t2-t1);
	printf("clock time was %f\n",totT);
	s.userMBPS = (dataAmnt/1000000)/(double)(t2-t1);
	s.clockMBPS = (dataAmnt/1000000)/totT;
	printf("user mbps was %f\n",s.userMBPS);
	printf("clock mbps was %f\n",s.clockMBPS);
	numTimes++;
	return s;
}

int checkMount(char *D, char Dloc[])
{
	FILE *fpipe;
	int i = 0, j = 0;
	char command[50] = "cat /etc/mtab | grep ";
	char a[100] = {0};
	char *tempstr = NULL;
	tempstr = malloc(50*sizeof(char));
	strcpy(tempstr, "");
	strcat(command, Dloc);

	//printf("command is %s\n", command);

	if (0 == (fpipe = (FILE*)popen(command, "r")))
  {
      perror("popen() failed.");
      return -1;	//TODO: make this not an exit(2)
  }

  fgets(a, sizeof(a), fpipe);
  //printf("a = ");
  while(a[i] != 0x20)
  //{
  	//printf("%c ",a[i]);
  	i++;
  //}

  //printf("\n");
  ++i;
  while(a[i] != 0x20)
  {
  	tempstr[j] = a[i];
  	i++;
  	j++;
  	//printf("%c", a[i]);
  }

  fclose(fpipe);

  tempstr[j] = '\0';

  //printf("tempstr = %s\n", tempstr);

  strcpy(D, tempstr);

	//printf("D = %s\n", D);

  realloc(tempstr, 0);    //reallocate the ram
	return 0;
}
