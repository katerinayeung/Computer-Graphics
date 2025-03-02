#include <iostream>		
#include <math.h>
#include <GL\glut.h>

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left = -2;
GLfloat right = 2;
GLfloat bottom = -2;
GLfloat top = 2;
GLfloat theta; 
const GLfloat DtoR = 0.017453;

//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void timer(int v);

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// clear the background

	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex2f(cos(DtoR*theta), sin(DtoR*theta));

	glColor3f(0, 1, 0);
	glVertex2f(-sin(DtoR*theta), cos(DtoR*theta));

	glColor3f(0, 0, 1);
	glVertex2f(-cos(DtoR*theta), -sin(DtoR*theta));

	glColor3f(1, 1, 0);
	glVertex2f(sin(DtoR*theta), -cos(DtoR*theta));
	glEnd();

	glutSwapBuffers();	
	glutPostRedisplay();	// work with GLUT_DOUBLE
}

void init(void)
{
	float ratio = ww*1.0 / (wh*1.0);

	glClearColor(1.0, 1.0, 1.0, 1.0);	// background color; default black; (R, G, B, Opacity)
	glColor3f(0, 1, 1);	// drawing color; default white

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio >= 1)
		gluOrtho2D(left*ratio, right*ratio, bottom, top);	
	else
		gluOrtho2D(left, right, bottom / ratio, top / ratio);
	glMatrixMode(GL_MODELVIEW);
}

void reshape(GLsizei w, GLsizei h)
{
	float ratio = w*1.0 / (h*1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio >= 1)
		gluOrtho2D(left*ratio, right*ratio, bottom, top);	
	else
		gluOrtho2D(left, right, bottom / ratio, top / ratio);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);		

	//------ reset the window size
	ww = w;	
	wh = h;
}

void timer(int v)
{
	theta -= 5;

	if (theta < 0.0)
		theta += 360.0;

	glutTimerFunc(100, timer, v);
}

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowSize(ww, wh);	
	glutInitWindowPosition(100, 100); 
	glutCreateWindow("2D animation with a timer");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutTimerFunc(100, timer, 1);

	glutMainLoop();
}