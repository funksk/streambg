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

typedef struct
{
    float curpts[NUM][2], nxtpts[NUM][2];
} tripnts;

tripnts tris;
tripnts getlist()
{
  int x1, x2;
  tripnts y;
  for(i = 0; i < NUM-1; i++)
  {
    x1 = rand() % 10 - 10;
    x2 = rand() % 10 - 10;
    y.curpts[i][0] = x1;
    y.curpts[i][1] = x2;
//    printf("y.curpts[%d][0] = %d, y.curpts[%d][1] = %d\n",i,y.curpts[i][0],i,y.curpts[i][1]);
  }
  return y;
}
 
void display(void)
 
{
    /* clear window */
  printf("%d\n",++count);
    glClear(GL_COLOR_BUFFER_BIT);
 
 
    /* draw unit square polygon */
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

 
    glBegin(GL_TRIANGLE_STRIP);

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
    srand(time(NULL));
    /* set clear color to black */
 
    /*  glClearColor (0.0, 0.0, 0.0, 0.0); */
    /* set fill  color to white */
 
    /*  glColor3f(1.0, 1.0, 1.0); */
 
    /* set up standard orthogonal view with clipping */
    /* box as cube of side 2 centered at origin */
    /* This is default view and these statement could be removed */
 
    /* glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);  */
}

int main(int argc, char** argv)
{
 
    /* Initialize mode and open a window in upper left corner of screen */
    /* Window title is name of program (arg[0]) */
 
    /* You must call glutInit before any other OpenGL/GLUT calls */
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("simple");
    glutDisplayFunc(display);
    glutIdleFunc(display);
    init();
    glutMainLoop();
 
    return 0;
}
