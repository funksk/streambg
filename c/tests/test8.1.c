/*
supposed to be a simple test of the bitmap capabilities of freeglut
*/

#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

int resol[2] = {640,480};
int fps = 60;

void putstr(int x, int y, char *str)
{
    int len, i;
    glRasterPos2f(x,y);
    len = (int) strlen(str);
    for(i = 0; i < len; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
}

void GLUTputc(int x, int y, char c)
{
    glRasterPos2f(x, y);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBegin(GL_TRIANGLES);

    glColor3f(0.241, 0.139, 0.61);

    glVertex2f(-0.3, -0.3);
    glVertex2f(-0.3, 0.3);
    glVertex2f(0.3, 0.3);
    glVertex2f(0.3, -0.3);

    glEnd();

    //putstr(0.3,0.3,"henlo uwu");

    //glRasterPos2f(x,y);
    //glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'h');

    GLUTputc(0.3,0.3,'c');

    glFlush();

    
}

void Timer(int x)
{
	display();
  	glutTimerFunc((float)(1/fps), Timer, 0);
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(resol[0],resol[1]);
    glutInitWindowPosition(0,0);
    glutCreateWindow("mic check 1 2");
    glutDisplayFunc(display);
    glutTimerFunc(0, Timer, 0);
    glutMainLoop();
}
