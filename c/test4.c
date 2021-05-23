/*
TODO
make coordinate system that will generate a bunch of random triangles.
somehow do this with c. this should only take like a day or two lol (I guess)
*/
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM 15
int i, j, count = 0;
float a = 2.0;

typedef struct
{
    float lof[4][NUM][2]; //0 = left, 1 = bottom, 2 = top, 3 = right
} tripnts;

tripnts cur, next;

float randfloat(float low, float high)
{
  return (((float)rand()/(float)(RAND_MAX)) * high) - low;
}

tripnts getlist()
{
  float x1, x2;
  tripnts y;

  for(i = 0; i < NUM-1; i++)  //0 = x, 1 = y
  {
    y.[0][i][0] = randfloat();//left x
    y.[0][i][1] = randfloat();//left y
    y.[1][i][0] = randfloat();//bottom x
    y.[1][i][1] = randfloat();//bottom y
    y.[2][i][0] = randfloat();//right x
    y.[2][i][1] = randfloat();//right y
    y.[3][i][0] = randfloat();//top x
    y.[3][i][1] = randfloat();//top y
    
//    printf("curpt[%d] = %d, %d",i,y.curpts[i][0],y.curpts[i][1]);
  }
  return y;
}
 
void display(void)
 
{
//  printf("%d\n",++count);
    glClear(GL_COLOR_BUFFER_BIT);
 
 
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

 
    glBegin(GL_TRIANGLE_STRIP);
//    glBegin(GL_POINTS);

    printf("hello!\n");
    tris = getlist();
    
    for(i = 0; i < NUM-1; i++)
    {
      glVertex2f(tris.curpts[i][0],tris.curpts[i][1]);
      printf("tris.curpts[%d][0] = %f, tris.curpts[%d][1] = %f\n",i,tris.curpts[i][0],i,tris.curpts[i][1]);
    }

    glEnd();
 
    /* flush GL buffers */
 
    glFlush();
 
}
 
 
void init()
{
    srand((unsigned int)time(NULL));
    
}

int main(int argc, char** argv)
{
 
    /* Initialize mode and open a window in upper left corner of screen */
    /* Window title is name of program (arg[0]) */
 
    /* You must call glutInit before any other OpenGL/GLUT calls */
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(250,125);
    glutCreateWindow("simple");
    glutDisplayFunc(display);
    glutIdleFunc(display);
    init();
    glutMainLoop();
 
    return 0;
}
