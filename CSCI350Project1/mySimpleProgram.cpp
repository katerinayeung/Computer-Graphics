#include <GL/glut.h>

GLint windowWidth = 512;
GLint windowHeight = 512;
GLfloat left = -1;
GLfloat right = 1;
GLfloat bottom = -1;
GLfloat top = 1;

//shape
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5,0.5);
	glVertex2f(0.5, -0.5);
	glEnd();

	glFlush();

}
//color
void init()
{
	glClearColor(0, 1, 1, 1);
	glColor3f(1, 0, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
	glMatrixMode(GL_MODELVIEW);

}
//keep shape the same ratio when stretch
void reshape(GLsizei w, GLsizei h) 
{
	float ratio = w * 1.0 / (h * 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio >= 1)
		gluOrtho2D(left * ratio, right * ratio, bottom, top);
	else
	
		gluOrtho2D(left, right, bottom / ratio, top / ratio);
	glMatrixMode(GL_MODELVIEW);
	
	glViewport(0, 0, w, h);
	
	//reset the window size
	windowWidth = w;
	windowHeight = h;
	
}

//main
int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(800, 200);
	glutCreateWindow("My simple program");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}