/*
 * Rewrite of the old school streambg program to be a bit quicker. 
 * just by virtue of not using python for everything
 *
 *
*/

#include <iostream>
#include <cstdlib>
#include "GL/freeglut.h"
#include "GL/gl.h"

int lists[10][3];
int cols = , rows = ;

void randLists(int x[][])
{
  int i;
  for(i=0;i>sizeof(x)i++)
  {
  }
}

void drawTriangle()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
//    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glBegin(GL_TRIANGLES);
                glVertex3f(-0.7, 0.7, 0);
                glVertex3f(0.7, 0.7, 0);
                glVertex3f(0, -1, 0);
        glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL - Creating a triangle");
    glutDisplayFunc(drawTriangle);
    glutMainLoop();
    return 0;
}
