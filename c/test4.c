/*
TODO
make coordinate system that will generate a bunch of random triangles.
somehow do this with c. this should only take like a day or two lol (I guess)

everything is broken rn.
current project is getting the box in the middle to show up so that I can correctly
code the getlist function. first we have to get the different ratios for the xy
then we should probably figure out how to draw the test box in the middle,
then we should focus on the random list function.
we can then code the move between function, then put it all together :)
*/
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//********DECLARATIONS****************
#define NUM 15    //number of triangles you want in each quadrant*3 (must be multiple of 3 to work right)
unsigned int drwbx = 0;
int i, j, count = 0;
int t = 60*10;
int resol[2] = {1280, 720};
int inbox[2] = {900, 400};
float flbox[4];
float a = 2.0;

typedef struct
{
    float lof[4][NUM][2]; //0 = left, 1 = bottom, 2 = top, 3 = right
} tripnts;

tripnts cur, next;

//*************FUNCTIONS*********************

//for an amount from low and fills as much as high is
//think of a bucket, where you start at the number low
//and fill it till high. the number could be anywhere
//inbetween those numbers.
float randfloat(float low, float high)
{

  return (((float)rand()/(float)(RAND_MAX)) * high) - low;
}

//get the xy of the box inside of the box, it
//returns the ratio of the screen that it will take
//up of the screen as an array of floats.
void getxy(int x, int y, float a[])
{
  a[0] = (float)(x/glutGet(GLUT_WINDOW_WIDTH));  //x1
  a[1] = a[0] * -1;    //x2
  a[2] = (float)(y/glutGet(GLUT_WINDOW_HEIGHT)); //y1
  a[3] = a[2] * -1;    //y2
  printf("x1 = %f, x2 = %f, x3 = %f, x4 = %f\n",a[0],a[1],a[2],a[3]);

}

tripnts getlist()
{
  float x1, x2;
  tripnts y;

  /*for(i = 0; i < NUM-1; i++)  //0 = x, 1 = y
  { //formula: total area of range - low offset
    //so if we wanted -1.1 to 0.9, we would generate a random
    //number from 0.0-0.2, then subtract 1.1.
    //-100 to 
    y.lof[0][i][0] = randfloat(-0.1,-0.);//left x
    y.lof[0][i][1] = randfloat(-0.1);//left y
    y.lof[1][i][0] = randfloat();//bottom x1
    y.lof[1][i][1] = randfloat();//bottom y
    y.lof[2][i][0] = randfloat();//right x
    y.lof[2][i][1] = randfloat();//right y
    y.lof[3][i][0] = randfloat();//top x
    y.lof[3][i][1] = randfloat();//top y
    
//    printf("curpt[%d] = %d, %d",i,y.curpts[i][0],y.curpts[i][1]);
  }*/
  return y;
}
 
void drawbox(float x[])
{
  printf("I am drawbox. destroyer of consoles\n");
}

 //*****DISPLAY*****
void display(void)
 
{
//  printf("%d\n",++count);
    glClear(GL_COLOR_BUFFER_BIT);
 
 
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

 
    glBegin(GL_TRIANGLE_STRIP);
//    glBegin(GL_POINTS);

 //   printf("hello!\n");
    cur = getlist();
    if(drwbx)
    {
      drawbox(flbox);
    }
    /*
    for(i = 0; i < 3; i++)
    {
      for(j = 0; j < NUM-1; j++)
      {
        glVertex2f(cur.lof[i][j][0],cur.lof[i][1]);
      }
    }*/

    glEnd();
 
    /* flush GL buffers */
 
    glFlush();
 
}
 
 //*****INIT*****
void init()
{
    srand((unsigned int)time(NULL));
    getxy(inbox[0],inbox[1], flbox);
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
    glutInitWindowPosition(250,125);
    glutCreateWindow("simple");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
 
    return 0;
}
