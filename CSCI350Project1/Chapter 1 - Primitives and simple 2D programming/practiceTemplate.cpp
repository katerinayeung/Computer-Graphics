#include <math.h>
#include <GL\glut.h>

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left = -4.0;
GLfloat right = 4.0;
GLfloat bottom = -4.0;
GLfloat top = 4.0;
const float DtoR = 0.017453;		// the ratio of degree to radian

//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void ellipse(float x0, float y0, float a, float b);
void solidEllipse(float x0, float y0, float a, float b);

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// clear the background

	//---------- graphics objects -------------
	glLineWidth(4);

	glColor3f(1, 0, 1);
	solidEllipse(0, 0, 2, 1);

	glColor3f(1, 1, 0);
	ellipse(0, 0, 2, 1);


	glFlush();	// force to render, work with single buffer
}

//---------------------------------------------------------------------------------------------
// The parameter equations of an oval are: x = x0 + a * cos(theta); y = y0 + b * sin(theta);
// where (x0, y0) is the center, and a and b are the semi-axes.
//---------------------------------------------------------------------------------------------
void ellipse(float x0, float y0, float a, float b)
{
	float x, y;
	float theta;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i += 10)
	{
		theta = i * DtoR;
		x = x0 + a * cos(theta);
		y = y0 + b * sin(theta);

		glVertex2f(x, y);
	}
	glEnd();
}

//---------------------------------------------------------------------------------------------
// The parameter equations of an oval are: x = x0 + a * cos(theta); y = y0 + b * sin(theta);
// where (x0, y0) is the center, and a and b are the semi-axes.
//---------------------------------------------------------------------------------------------
void solidEllipse(float x0, float y0, float a, float b)
{
	float x, y;
	float theta;

	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 10)
	{
		theta = i * DtoR;
		x = x0 + a * cos(theta);
		y = y0 + b * sin(theta);

		glVertex2f(x, y);
	}
	glEnd();
}

void init(void)
{
	glClearColor(0.5, 0.5, 0.5, 1.0);	// background color; default black; (R, G, B, Opacity)
	glColor3f(0, 1, 1);	// drawing color; default white

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
	glutCreateWindow("An Ellipse");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);	

	glutMainLoop();

	return 0;
}