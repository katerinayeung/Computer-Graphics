#include <GL/glut.h>

GLsizei ww = 512;
GLsizei wh = 512;

int points[1000][2];
int count = 0;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glBegin(GL_LINE_STRIP);
	//glBegin(GL_POINTS);
		for ( int i=0; i<count; i++ )
			glVertex2iv(points[i]);
	glEnd();

	glFlush();
}

void mouseMotion( int x, int y)
{
	if ( count < 1000 )
	{
		points[count][0] = x;
		points[count][1] = wh - y;
		 
		count ++;
	}

	display();
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
	glutMotionFunc( mouseMotion );
	glutDisplayFunc( display );
	glutMainLoop();
}