/*
TODO
make coordinate system that will generate a bunch of random triangles.
somehow do this with c. this should only take like a day or two lol (I guess)
*/
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
int num = 15, i, j;
int lon[15][2], nlon[33];


 
void getlist(int* x[num+1][2])
{
  int x1, x2;
  for(i = 0; i < num-1; i++)
  {
    x1 = rand() % 1920;
    x2 = rand() % 1080;
    printf("x1 = %d, x2 = %d\n", x1, x2);
    x[i][0] = x1;
    x[i][1] = x2;
    printf("lon[%d][0] = %d, lon[%d][1] = %d\n",i,lon[i][0],i,lon[i][1]);
  }

}
 
void display(void)
 
{
    /* clear window */

  getlist(lon);
 
     glClear(GL_COLOR_BUFFER_BIT);
 
 
    /* draw unit square polygon */
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

 
    glBegin(GL_TRIANGLE_STRIP);

    printf("hello!\n");
    for(i = 0; i < num-1; i++)
    {
      printf("lon[%d][0] = %d, lon[%d][1] = %d\n",i,lon[i][0],i,lon[i][1]);
      glVertex2i(lon[i][0],lon[i][1]);
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
    init();
    glutMainLoop();
 
}
