/*
TODO
make coordinate system that will generate a bunch of random triangles.
somehow do this with c. this should only take like a day or two lol (I guess)

we can then code the move between function, then put it all together :)

the inc function is busted. it has to do with the order of the array. 
maybe swap it around? idk.
*/
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//********DECLARATIONS****************
//consts
#define NUM 9    //number of triangles you want in each quadrant*3 (must be multiple of 3 to work right)
const unsigned int drwbx = 1;
const unsigned int debugf = 1;
const int t = 60*10;
const int dt = 0;
const int fps = 30;
const int uplims = 10; //upper limit in seconds
const int uplimf = fps*uplims;
const int resol[2] = {1280, 720};
const int inbox[2] = {900, 400};
const float a = 2.0;

//variables
int i, j, k, count = 0;
float flbox[4];

typedef struct
{
    float lof[4][NUM][2]; //0 = left, 1 = bottom, 2 = top, 3 = right
} tripnts;

tripnts cur, next, work;

//*************FUNCTIONS*********************

//for an amount from low and fills as much as high is
//think of a bucket, where you start at the number low
//and fill it till high. the number could be anywhere
//inbetween those numbers.
float randfloat(float Min, float Max)
{
  return (((float)rand() / (float)RAND_MAX) * (Max - Min)) + Min;
}

//get the xy of the box inside of the box, it
//returns the ratio of the screen that it will take
//up of the screen as an array of floats.
void getxy(int x, int y, float a[])
{
  a[0] = (float)x/(float)glutGet(GLUT_WINDOW_WIDTH);  //x1
  a[1] = (float)y/(float)glutGet(GLUT_WINDOW_HEIGHT); //y1
  a[2] = a[0] * -1; //x2
  a[3] = a[1] * -1; //y2
//  printf("x1 = %f, y1 = %f\n",a[0],a[1]);
}

tripnts getlist(float a[])
{
  tripnts y;
  for(i = 0; i < NUM-1; i++)  //0 = x, 1 = y
  { //formula: total area of range - low offset
    //so if we wanted -1.1 to 0.9, we would generate a random
    //number from 0.0-0.2, then subtract 1.1.
    //-100 to 
    y.lof[0][i][0] = randfloat(-1.1,a[2]+0.1);//left x
    y.lof[0][i][1] = randfloat(-1.1,1.1);//left y
    y.lof[1][i][0] = randfloat(-1.2,1.2);//bottom x
    y.lof[1][i][1] = randfloat(-1.1,a[3]+0.1);//bottom y
    y.lof[2][i][0] = randfloat(a[0]-0.1,1.1);//right x
    y.lof[2][i][1] = randfloat(-1.1,1.1);//right y
    y.lof[3][i][0] = randfloat(-1.2,1.2);//top x
    y.lof[3][i][1] = randfloat(a[1]-0.1,1.1);//top y
//    printf("%f, %f, %f, %f, %f, %f, %f, %f\n", y.lof[0][i][0], y.lof[0][i][1], y.lof[1][i][0], y.lof[1][i][1], y.lof[2][i][0], y.lof[2][i][1], y.lof[3][i][0], y.lof[3][i][1]);
  }
  return y;
}
 
void drawbox(float x[4])
{
//  printf("I am drawbox. destroyer of consoles\n");
  glVertex2f(x[0],x[1]);
  glVertex2f(x[2],x[3]);
  glVertex2f(x[0],x[3]);
  glVertex2f(x[0],x[1]);
  glVertex2f(x[2],x[3]);
  glVertex2f(x[2],x[1]);
}

//we can do a little hacking here.
//just look at what our initial value is, 
//compare to the other value
//see what fucked up. change the clock speed n shit
//be an engineer, retard!

tripnts inc(tripnts c, tripnts n, tripnts w)
{
  FILE *f = fopen("debug.txt", "w");
  float ut;
  tripnts ret;
  for(i = 0;i<=3;i++)
    for(j = 0;j<=NUM-1;j++)
      for(k = 0;k<=1;k++)
      {
        if(n.lof[i][j][k]>w.lof[i][j][k])
        {
          ut = n.lof[i][j][k] - c.lof[i][j][k];
          ret.lof[i][j][k] = w.lof[i][j][k]+(ut/(float)uplimf);
        }
        else if(n.lof[i][j][k]<w.lof[i][j][k])
        {
          ut = c.lof[i][j][k] - n.lof[i][j][k];
          ret.lof[i][j][k] = w.lof[i][j][k]+(ut/(float)uplimf);
        }
        printf("ret.lof[%d][%d][%d] = %f\n",i,j,k,ret.lof[i][j][k]);
        if(debugf)
        {
          fprintf(f, "ret.lof[%d][%d][%d] = %f\n",i,j,k,ret.lof[i][j][k]);
        }
      }
  return ret;
}

 //*****DISPLAY*****
void display(void)
{
  count+=1;
  if(count == uplimf)
  {
    cur = next;
    next = getlist(flbox);
    count = 0;
  }
//  printf("%d\n",++count);
    glClear(GL_COLOR_BUFFER_BIT);
 
  
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
 
    glBegin(GL_TRIANGLE_STRIP);
//    glBegin(GL_POINTS);

 //   printf("hello!\n");
//    cur = getlist(flbox);
    if(drwbx)
      drawbox(flbox);
    printf("hello!\n");
    work = inc(cur, next, work);
    printf("goodbye!\n");
    for(i = 0; i <= 3; i++)
      for(j = 0; j < NUM-1; j++)
        glVertex2f(work.lof[i][j][0],work.lof[i][j][1]);

    glEnd();
 
    /* flush GL buffers */

    glFlush();
 
}

void Timer(int x)
{
  display();
  glutTimerFunc((float)(1/fps), Timer, 0);
}
 
 //*****INIT*****
void init()
{
    srand((unsigned int)time(NULL));
    getxy(inbox[0],inbox[1], flbox);
    cur = getlist(flbox);
    next = getlist(flbox);
}


//****************MAIN*******************
int main(int argc, char** argv)
{
 
    /* Initialize mode and open a window in upper left corner of screen */
    /* Window title is name of program (arg[0]) */
 
    /* You must call glutInit before any other OpenGL/GLUT calls */
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(resol[0],resol[1]);
    glutInitWindowPosition(0,0);
    glutCreateWindow("simple");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, Timer, 0);
    glutMainLoop();
 
    return 0;
}
