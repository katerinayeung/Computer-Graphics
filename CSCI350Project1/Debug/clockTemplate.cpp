// Practice problem: Draw a clock with 12 ticks with three hands representing the time 1:30. 

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
void clock(void);

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// clear the background

	//---------- graphics objects -------------
	clock();

	glFlush();	// force to render, work with single buffer
}

void clock(void)
{
	float r = 1;	// you can determine the radius of the clock face here
	float x, y;
	float theta = 0;

	//===================== the clock face =====================
	glColor3f(0.0, 0.3, 0.3);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 5)
	{
		theta = i * DtoR;

		//TODO: use the parameter equations of a circle: x = r*cos(theta); y = r*sin(theta) to obtain a vertex (x, y) on the circle
		x = r * cos(theta);
		y = r * sin(theta);

		glVertex2f(x, y);
	}
	glEnd();
	//=========================================================

	//============================ ticks ============================
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	for (int i = 0; i < 360; i += 30) //30 degrees
	{
		theta = i * DtoR;
		//outer ciricle
		glVertex2f(r * cos(theta), r * sin(theta));	
		//inner circle connect line segment to outter circle to create ticks; 0.9 is ratio/size of smaller circle to bigger

		glVertex2f(0.9 * r * cos(theta), 0.9 * r * sin(theta));
	}
	glEnd();
	//===============================================================
	
	//==================== hands at the time 1:30 ===================
	//------------------------ the hour hand --------------------
	glColor3f(0, 0, 0);
	glLineWidth(6);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0.6 * cos(45 * DtoR), 0.6 * sin(45 * DtoR));
	glEnd();

	//---------------------- the minute hand --------------------
	glColor3f(0, 0, 0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0.75 * cos(-90 * DtoR), 0.75 * sin(-90 * DtoR));
	glEnd();

	//---------------------- the second hand --------------------
	glColor3f(1, 1, 0.3);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0.85 * cos(90 * DtoR), 0.85 * sin(90 * DtoR));
	glEnd();
	//===============================================================
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
	glutCreateWindow("A Clock");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);	

	glutMainLoop();

	return 0;
}