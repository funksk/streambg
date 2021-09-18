/*
TODO
okay, we're essensially at the point where we were in the python program.
now we need to just add the auto-frame maker and maybe the facecam window.

I think that the randomization function works just fine I guess..
now all that I need to do is justify the screen to some side of the screen,
make a frame maker for the facecam, and a box for the chat.
this should take like another day or something.

*/
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//********DECLARATIONS****************
//consts
#define NUM 45-2    //number of triangles you want in each quadrant*3 (must be multiple of 3 to work right)
const unsigned int drwbx = 1;
const unsigned int movbx = 0;

const int t = 60*10;
const int dt = 0;
const int fps = 30;
const int uplims = 50; //upper limit in seconds... this is not seconds idk
const int uplimf = fps*uplims;
const int resol[2] = {1920, 1080};
const int inbox[2] = {800,600};
const float a = 2.0;

//variables
int fflag = 0;
int i, j, k, count = 0;
float flbox[4];
int num1 = (NUM-1)/2;
FILE *f;


typedef struct
{
    float lof[4][NUM][2]; //0 = left, 1 = bottom, 2 = top, 3 = right
} tripnts;

typedef struct 
{
  float pts[4][4];
} frame;

tripnts cur, next, work;
frame frm, xylims;

//*************FUNCTIONS*********************

//for an amount from low and fills as much as high is
//think of a bucket, where you start at the number low
//and fill it till high. the number could be anywhere
//inbetween those numbers.
//...might have stolen from the internets. oh well!
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
  printf("%d, %d\n",glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
  printf("%d, %d\n", x, y);
  printf("x1 = %f, y1 = %f, x2 = %f, x3 = %f\n",a[0],a[1],a[2],a[3]);
//  while(1);
}


//these values can change. this code is indecipherable lol
frame getlims(float a[])
{
  frame x;
  x.pts[0][0] = -1.1;
  x.pts[0][1] = a[2]+0.1;
  x.pts[0][2] = -1.1;
  x.pts[0][3] = 1.1;
  x.pts[1][0] = -1.2;//bottom x
  x.pts[1][1] = 1.2;
  x.pts[1][2] = -1.1;
  x.pts[1][3] = a[3]+0.1;
  x.pts[2][0] = a[0]-0.1;
  x.pts[2][1] = 1.1;
  x.pts[2][2] = -1.1;
  x.pts[2][3] = 1.1;
  x.pts[3][0] = -1.2;
  x.pts[3][1] = 1.2;
  x.pts[3][2] = a[1]-0.1;
  x.pts[3][3] = 1.1;
  return x;
}

tripnts getlist(frame x)
{
  tripnts y;
  for(i = 0; i < NUM-1; i++)  //0 = x, 1 = y
  { 
    y.lof[0][i][0] = randfloat(x.pts[0][0],x.pts[0][1]);//left x
    y.lof[0][i][1] = randfloat(x.pts[0][2],x.pts[0][3]);//left y
    y.lof[1][i][0] = randfloat(x.pts[1][0],x.pts[1][1]);//bottom x
    y.lof[1][i][1] = randfloat(x.pts[1][2],x.pts[1][3]);//bottom y
    y.lof[2][i][0] = randfloat(x.pts[2][0],x.pts[2][1]);//right x
    y.lof[2][i][1] = randfloat(x.pts[2][2],x.pts[2][3]);//right y
    y.lof[3][i][0] = randfloat(x.pts[3][0],x.pts[3][1]);//top x
    y.lof[3][i][1] = randfloat(x.pts[3][2],x.pts[3][3]);//top y
//    printf("y.lof[0][%d][0] = %f \r", j, y.lof[0][j][0]);
//    sleep(5);
//    printf("%f, %f, %f, %f, %f, %f, %f, %f\n", y.lof[0][i][0], y.lof[0][i][1], y.lof[1][i][0], y.lof[1][i][1], y.lof[2][i][0], y.lof[2][i][1], y.lof[3][i][0], y.lof[3][i][1]);
//    if(debugf)
//      fprintf("%f, %f, %f, %f, %f, %f, %f, %f\n", y.lof[0][i][0], y.lof[0][i][1], y.lof[1][i][0], y.lof[1][i][1], y.lof[2][i][0], y.lof[2][i][1], y.lof[3][i][0], y.lof[3][i][1]);
  }
  printf("\n");
  return y;
}

tripnts randlist(frame x, tripnts y)
{
  tripnts z;
  for(i = 0;i<=3;i++)
  {
    for(j = 0;j < NUM-1;j++)
    {
      for(k = 0;k<=1;k++)
      {
        do
        {
            z.lof[i][j][k] = randfloat(y.lof[i][j][k]-0.2,y.lof[i][j][k]+0.2);
//          printf("z.lof[%d][%d][%d] = %f, x.pts[%d][%d] = %f, x.pts[%d][%d] = %f\n", i,j,k,z.lof[i][j][k],i,k*2,x.pts[i][k*2],i,k*3,x.pts[i][(k*2)+1]);
//          fprintf("z.lof[%d][%d][%d] = %f, x.pts[%d][%d] = %f, x.pts[%d][%d] = %f\n", i,j,k,z.lof[i][j][k],i,k*2,x.pts[i][k*2],i,k*3,x.pts[i][(k*3)+1]);
//          if(i == 1)
//            while(1);
//          printf("%f > %f && %f < %f\n",z.lof[i][j][k], x.pts[i][k*2], z.lof[i][j][k], x.pts[i][(k*3)+1]);
//          printf("z.lof[0][0][0] = %f, z.lof[0][0][1] = %f\n", z.lof[0][0][0],z.lof[0][0][1]);
        }while
        (!(z.lof[i][j][k] > x.pts[i][k*2] && z.lof[i][j][k] < x.pts[i][(k*2)+1]));
      }
    }
  }
  return z;
}


tripnts inc(tripnts c, tripnts n, tripnts w)
{
  float ut;
  tripnts ret;
  for(i = 0;i<=3;i++)
  {
    for(j = 0;j < NUM-1;j++)
    {
      for(k = 0;k<=1;k++)
      {
        if(n.lof[i][j][k]>w.lof[i][j][k])
        {
          ut = n.lof[i][j][k] - c.lof[i][j][k];
          ret.lof[i][j][k] = w.lof[i][j][k]+(ut/uplimf);
        }
        else if(n.lof[i][j][k]<w.lof[i][j][k])
        {
          ut = c.lof[i][j][k] - n.lof[i][j][k];
          ret.lof[i][j][k] = w.lof[i][j][k]-(ut/uplimf);
        }
//        if(i == 0 && j == 0 && k == 0)
//          printf("ut = %f\n",ut);
        /*
        printf("ret.lof[%d][%d][%d] = %f\n",i,j,k,ret.lof[i][j][k]);
        if(debugf)
        {
           fprintf(f, "ret.lof[%d][%d][%d] = %f\n",i,j,k,ret.lof[i][j][k]);
        }*/
      }
//      sleep(1);
    }
  }
  return ret;
}


 //*****DISPLAY*****
void display(void)
{
//  printf("henlo :3\n");
  count+=1;
  if(count == uplimf)
  {
    work = next;
    cur = next;
 //   next = getlist(flbox);
    next = randlist(xylims, cur);
    printf("switched it up, baby\ncur.lof[1][0][0] = %f\nnext.lof[1][0][0] = %f\n\n", cur.lof[1][0][0], next.lof[1][0][0]);
    count = 0;
  }

//  printf("%d\n",++count);
    glClear(GL_COLOR_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
 
//    glBegin(GL_TRIANGLE_STRIP);
    glBegin(GL_TRIANGLES);
//    glBegin(GL_POINTS);

 //   printf("hello!\n");

    glColor3f(0.241, 0.139, 0.61);

//    printf("hello!\n");
    work = inc(cur, next, work);
//    printf("goodbye!\n");
//    printf("work.lof[0][0][0] = %f \r", work.lof[0][0][0]);
//    printf("cur.lof[1][0][0] = %f, next.lof[1][0][0] = %f, work.lof[1][0][0] = %f\n",cur.lof[1][0][0], next.lof[1][0][0], work.lof[1][0][0]);
    for(i = 0; i <= 3; i++)
    {
      if(i == 1 || i == 3)  //the top and bottom have half of the amnt of triangles because it looks redickyewlas
        for(j = 0; j < num1; j++)
          glVertex2f(work.lof[i][j][0],work.lof[i][j][1]); 
      else
        for(j = 0; j < NUM-1; j++)
          glVertex2f(work.lof[i][j][0],work.lof[i][j][1]);
    }

    glRasterPos2f(500, 500);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "black people");
    glEnd();
  
    /* flush GL buffers */

    glFlush();
//    glutPostRedisplay();
//    glutSwapBuffers();
 
}

void Timer(int x)
{
  display();
  glutTimerFunc((float)(1/fps), Timer, 0);
}
 

 //*****INIT*****
void init()
{
    f = fopen("debug.txt", "w");
    srand((unsigned int)time(NULL));
    getxy(inbox[0],inbox[1],flbox);
//    xyjst(inbox[0],inbox[1], 0, flbox);
    xylims = getlims(flbox);
    cur = getlist(xylims);
    next = randlist(xylims, cur);
    printf("cur.lof[0][0][0] = %f\nnext.lof[0][0][0] = %f\n", cur.lof[0][0][0], next.lof[0][0][0]);
    work = cur;
    printf("we are out of prison\n");
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
    glutCreateWindow("streamstarting");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, Timer, 0);
    glutMainLoop();
 
    return 0;
}
