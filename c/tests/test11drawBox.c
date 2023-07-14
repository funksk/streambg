#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/freeglut.h>



void xyjst(int x, int y, int z, float a[])
{
  float xx = (float)x/(float)glutGet(GLUT_WINDOW_WIDTH);
  float yy = (float)y/(float)glutGet(GLUT_WINDOW_HEIGHT);
  switch(z)
  {
    
    case 0: //topleft
      a[0] = (xx*(xx+1))-1;
      a[1] = 1;
      a[2] = -1;
      a[3] = (yy*(yy-1))+1;
      break;
    /*
    case 1: //midleft
      a[0] = ;
      a[1] = ;
      a[2] = -1;
      a[3] = ;
      break;
    case 2: //bottomleft
      a[0] = ;
      a[1] = ;
      a[2] = -1;
      a[3] = -1;
      break;
    case 3: //top middle
      a[0] = ;
      a[1] = 1;
      a[2] = ;
      a[3] = ;
      break;
      */
    default:
    case 4: //centered
      a[0] = xx;  //x1
      a[1] = yy; //y1
      a[2] = a[0] * -1; //x2
      a[3] = a[1] * -1; //y2
      break;
      /*
    case 5: //bottom middle
      a[0] = ;
      a[1] = ;
      a[2] = ;
      a[3] = -1;
      break;
    case 6: //top right
      a[0] = 1;
      a[1] = 1;
      a[2] = ;
      a[3] = ;
      break;
    case 7: //middle right
      a[0] = 1;
      a[1] = ;
      a[2] = ;
      a[3] = ;
      break;
    case 8: //bottom right
      a[0] = ;
      a[1] = ;
      a[2] = ;
      a[3] = -1;
      break;*/

      printf("x1 = %f, y1 = %f, x2 = %f, x3 = %f\n",a[0],a[1],a[2],a[3]);

  }
}

void display(void)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


int main(int argv, char *argc[])
{
	glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(resol[0],resol[1]);
    glutInitWindowPosition(0,0);
    glutCreateWindow("some typa program");

    getxy(inbox[0],inbox[1],flbox);
    xyjst(inbox[0],inbox[1], 0, flbox);

    glutDisplayFunc(display);
    glutTimerFunc(0, Timer, 0);
    if(movbx) glutSpecialFunc(keyin);
    glutMainLoop();
	return 0;
}