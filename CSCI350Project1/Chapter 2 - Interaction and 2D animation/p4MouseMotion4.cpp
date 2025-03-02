#include <GL/glut.h>

GLsizei ww = 512;
GLsizei wh = 512;

int xx = 0, yy = 0;



void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glFlush();
}

void passiveMotion( int x, int y)
{
	glBegin(GL_POINTS);
			glVertex2f(x, wh-y);
	glEnd();

	glFlush();
}

void init()
{
	glClearColor(0.3, 0.3, 0.3, 1);

	glColor3f(0.2, 0.8, 0.8);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, ww, 0, wh, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(800, 200);
	glutCreateWindow( "Mouse motion" );

	init();

	glutDisplayFunc(display);
	glutPassiveMotionFunc( passiveMotion );

	glutMainLoop();
}