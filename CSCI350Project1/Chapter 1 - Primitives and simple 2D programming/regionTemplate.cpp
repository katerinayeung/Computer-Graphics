// In this practice, you color a region between two curves y1 = sin(2*x)
// and y2 = cos(2*x). Also, thicken each curve with a different color. 

#include <math.h>
#include <GL\glut.h>

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left = -2.0;
GLfloat right = 2.0;
GLfloat bottom = -2.0;
GLfloat top = 2.0;
const float DtoR = 0.017453;		// the ratio of degree to radian

//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void region(void);

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// clear the background

	//---------- graphics objects -------------
	region();

	glFlush();	// force to render, work with single buffer
}

void region(void)
{
	GLfloat x, y1, y2;
	GLfloat a = -1;		// the left end, and it can be changed 
	GLfloat b = 1;		// the right end, and it can be changed
	GLfloat dx = 0.01;	// the increament, and it can be changed

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUAD_STRIP);
	x = a;
	while (x <= b)	// two vertices are created in each round, one from each curve
	{
		y1 = sin(2 * x);		// curve one, and it can be replaced with any other curve
		glColor3ub(255, 0, 0);	// unsigned byte: 0 - 255
		glVertex2f(x, y1);

		y2 = cos(2 * x);		// curve two, and it can be replaced with any other curve
		glColor3f(0, 1, 1);		// float: 0 - 1
		glVertex2f(x, y2);

		x += dx;
	}
	glEnd();

	glLineWidth(2);			// thicken the first curve
	glColor3ub(0, 0, 0);	// with some color. (unsigned byte: 0 - 255)
	glBegin(GL_LINE_STRIP);
	x = a;
	while (x <= b)	// draw the first curve
	{
		y1 = sin(2 * x);
		glVertex2f(x, y1);

		x += dx;

	}
	glEnd();

	glLineWidth(2);		// thicken the second curve
	glColor3f(1, 1, 0);	// with some color. (float: 0 - 1)
	glBegin(GL_LINE_STRIP);
	x = a;
	while (x <= b)	// draw the second curve
	{
		y2 = cos(2* x);
		glVertex2f(x, y2);

		x += dx;

	}
	glEnd();
}

void init(void)
{
	glClearColor(0.5, 0.5, 0.5, 1.0);	// background color; default black; (R, G, B, Opacity)
	glColor3f(0, 1, 1);	// drawing color

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, ww, wh);
	//-------------------------------------
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

int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(ww, wh);	// default size 300 by 300
	glutInitWindowPosition(100, 50); // defualt at (0, 0)
	glutCreateWindow("A Region");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);	

	glutMainLoop();

	return 0;
}