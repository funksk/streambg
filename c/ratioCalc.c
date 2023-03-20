#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define CLRSCREEN() printf("\e[2J\e[H")
#define GOTOXY(x,y) printf("\033[%d;%dH",y,x)
#define SVCRSR()  printf("\033[s")
#define LDCRSR()  printf("\033[u")

int main(int argc, char * argv[])
{
	char in1[5], in2[5];
	unsigned int divisor, dividend;
	char in;
	float ratio = 0.0;

	printf("pick a ratio\n");
	scanf("%s",in1);
	printf(":");
	scanf("%s",in2);
	
	ratio = (float)atoi(in2) / (float)atoi(in1);

	if(ratio == (9.0 / 16.0))	//16:9, for fun...
		divisor = 1920;
	else
		divisor = 800;

	dividend = (int)(divisor*ratio);

	do
	{
		switch(in)
		{
			case 'w':	//increase
				divisor+=50;
				break;
			case 's':
				divisor-=50;
				break;
			case 'e':
				divisor+=10;
				break;
			case 'd':
				divisor-=10;
				break;
			default:
				break;
		}

		CLRSCREEN();
		GOTOXY(0,0);
		dividend = (int)(divisor*ratio);
		printf("w:+50\ts:-50\ne:+10\td:-10\nq=quit\n");
		printf("%dx%d\n",divisor,dividend);
	
	} while((in = getchar()) != 'q');

	return 0;
}
