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
GLfloat theta = 90;			// second hand's initial position
GLfloat beta = -22.5;		// minute hand's initial position
const GLfloat DtoR = 0.017453;
GLint multiple = 50;		// multiple of a millisecond

//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void timer(int v);

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// clear the background

	glBegin(GL_LINES);
	// the second hand
	glColor3f(1, 0, 0);
	glVertex2f(0, 0);
	glVertex2f(cos(theta*DtoR), sin(theta*DtoR));

	//TODO: draw the minute hand (use the angle beta)

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
	theta -= 6.0;		// the second hand decreases by 6 degrees per second
	//TODO: decrease the angle beta for the minute hand	// the minute hand is 60 times slower than the second hand. (floating point devision)
						// the hour hand is 12 times slower than the minute hand, thus 12*60 times slower than the second hand.
	if (theta < -360.0)
		theta += 360.0;

	if (beta < -360.0)
		beta += 360.0;

	glutTimerFunc(multiple, timer, v);
}

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowSize(ww, wh);	
	glutInitWindowPosition(800, 200); 
	glutCreateWindow("Clock hands rotations");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutTimerFunc(multiple, timer, 1);

	glutMainLoop();
}