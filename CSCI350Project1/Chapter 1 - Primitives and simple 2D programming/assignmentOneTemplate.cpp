#include <math.h>
#include <GL\glut.h>

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left = -2.0;
GLfloat right = 2.0;
GLfloat bottom = -2.0;
GLfloat top = 2.0;
GLfloat Pi = 3.14159;
const float DtoR = 0.017453;

//Design your own stipple pattern here. Don't use this one
GLubyte mask[] = {
	0x00, 0x00, 0x10, 0x00,
	0x00, 0x00, 0x30, 0x00,
	0x00, 0x00, 0x70, 0x00,
	0x00, 0x00, 0x70, 0x00,
	0x00, 0x00, 0x60, 0x00,
	0x00, 0x00, 0x60, 0x00,
	0x00, 0x00, 0x60, 0x00,
	0x00, 0x00, 0x60, 0x00,
	0x00, 0x00, 0xC0, 0x00,
	0x00, 0x00, 0xCF, 0x80,
	0x00, 0x00, 0xFF, 0xF8,
	0x00, 0xFF, 0xCF, 0xFF,
	0x03, 0xFC, 0xC3, 0xF8,
	0x1F, 0xF0, 0x80, 0x00,
	0x00, 0x00, 0x80, 0x00,
	0x00, 0x38, 0x80, 0x00,
	0x00, 0xFE, 0xB8, 0x00,
	0x00, 0xFF, 0xFC, 0x00,
	0x00, 0x7F, 0xF8, 0x00,
	0x01, 0xFF, 0xF0, 0x00,
	0x03, 0xFF, 0xFE, 0x00,
	0x03, 0xFF, 0xFF, 0x00,
	0x01, 0xFF, 0xFF, 0x00,
	0x00, 0xEF, 0xFF, 0x00,
	0x00, 0x0F, 0xFE, 0x00,
	0x00, 0x1F, 0xC0, 0x00,
	0x00, 0x3F, 0xC0, 0x00,
	0x00, 0x3F, 0x80, 0x00,
	0x00, 0x1F, 0x00, 0x00,
	0x00, 0x1E, 0x00, 0x00,
	0x00, 0x0C, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00 };


//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void stippledTriangle(void);
void polarCurve(void);
void clock(void);
void region(void);
void axes(void);

void axes(void)
{
	glBegin(GL_LINES);
	glVertex2f(left, 0);
	glVertex2f(right, 0);

	glVertex2f(0, bottom);
	glVertex2f(0, top);
	glEnd();
}

void region(void)
{

}

void clock(void)
{

}

void polarCurve(void)
{

}

// This is for demonstration. Use the vertices given the homework assignment
void stippledTriangle(void)	
{
	//---------- draw the background triangle -----------
	glBegin(GL_POLYGON);
	glVertex2f(-0.8, 0.0);
	glVertex2f(-0.2, -0.6);
	glVertex2f(0.5, 0.0);
	glEnd();

	//---------- draw the stippled triangle ---------------
	glEnable(GL_POLYGON_STIPPLE);
	glColor3f(1, 0, 0);
	glPolygonStipple(mask);

	glBegin(GL_POLYGON);
	glVertex2f(-0.8, 0.0);
	glVertex2f(-0.2, -0.6);
	glVertex2f(0.5, 0.0);
	glEnd();
	glDisable(GL_POLYGON_STIPPLE);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	//------ display on the lower left quarter --------
	glViewport(0, 0, ww/2, wh/2);	//(x, y, width, height)
	stippledTriangle();
	//---------------------------------------

	//------- display on lower right quarter -------------
	glViewport(ww/2, 0, ww/2, wh/2);
	glColor3f(1, 1, 1);
	axes();

	glLineWidth(2);
	polarCurve();
	//-----------------------------------------------------

	//------- display on upper left quarter -------------
	glViewport(0, wh/2, ww/2, wh/2);
	clock();
	//-----------------------------------------------------

	//------- display on upper right quarter -------------
	glViewport(ww/2, wh/2, ww/2, wh/2);
	glColor3f(1, 1, 1);
	glLineWidth(1);
	axes();

	glLineWidth(2);
	region();
	//-----------------------------------------------------

	glFlush();
}

void init(void)
{
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glColor3f(0, 1, 1);

	glClearColor(0.5, 0.5, 0.5, 1.0);	// background color; default black; (R, G, B, Opacity)
	glColor3f(0, 1, 1);	// drawing color; default white

						//---the following segment could be included in the reshape callback-----
	float ratio = ww * 1.0 / (wh*1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio >= 1)
		gluOrtho2D(left*ratio, right*ratio, bottom, top);	// default (-1, 1, -1, 1)
	else
		gluOrtho2D(left, right, bottom / ratio, top / ratio);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, ww, wh);
	//-------------------------------------
}

void reshape(GLsizei w, GLsizei h)
{
	float ratio = w * 1.0 / (h*1.0);

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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // GLUT_DOUBLE work with glutPostRedisplay
	glutInitWindowSize(ww, wh);	// default size 300 by 300
	glutInitWindowPosition(100, 50); // defualt at (0, 0)
	glutCreateWindow("Your name shown here");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);	// envoked when the window is reshaped or moved; also envoked when the window is displayed at the first time

	glutMainLoop();

	return 0;
}