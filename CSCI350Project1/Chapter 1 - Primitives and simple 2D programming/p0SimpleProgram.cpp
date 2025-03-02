#include <GL\glut.h>


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// clear the background

	glRectf(-0.5, -0.5, 0.5, 0.5);

	glFlush();	// force to render, work with single buffer
}

int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutCreateWindow("A simple program");

	glutDisplayFunc(display);
	
	glutMainLoop();
	return 0;
}