#include <math.h>
#include <GL\glut.h>

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left = -10.0;
GLfloat right = 10.0;
GLfloat bottom = -10.0;
GLfloat top = 10.0;
GLfloat Pi = 3.14159;
const float DtoR = 0.017453;

//Design your own stipple pattern here. Don't use this one
GLubyte mask[] = {
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0xff, 0xff };

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
	GLfloat x, y1, y2;
	GLfloat a = -4;	
	GLfloat b = 4;		
	GLfloat dx = 0.01;	

	glBegin(GL_QUAD_STRIP);
	x = a;
	while (x <= b) { 

		y1 = sqrt(16 - x * x); 
		glColor3ub(0, 0, 0);
		glVertex2f(x, y1);

		y2 = 2 * sqrt(16 - x * x);  
		glColor3f(0.0, 0, 0.0);  
		glVertex2f(x, y2);

		x += dx;
	}
	glEnd();

	glLineWidth(2);  
	glColor3f(1.0, 1.0, 0.0);  
	glBegin(GL_LINE_STRIP);
	x = a;
	while (x <= b) {  
		y1 = sqrt(16 - x * x);  
		glVertex2f(x, y1);  
		x += dx;
	}
	glEnd();

	
	glLineWidth(2); 
	glColor3f(1.0, 1.0, 0.0); 
	glBegin(GL_LINE_STRIP);
	x = a;
	while (x <= b) { 
		y2 = 2 * sqrt(16 - x * x);  
		glVertex2f(x, y2);  
		x += dx;
	}
	glEnd();
}

void clock(void)
{
	float r = 8;	//radius 8
	float x, y;
	float theta = 0;

	//clock face
	glColor3f(0.0, 0.3, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 5)
	{
		theta = i * DtoR;
		x = r * cos(theta);
		y = r * sin(theta);

		glVertex2f(x, y);
	}
	glEnd();


	// ticks
	glColor3f(1, 1, 0.3);
	glBegin(GL_LINES);
	for (int i = 0; i < 360; i += 30) //30 degrees
	{
		theta = i * DtoR;
		//outer ciricle
		glVertex2f(r * cos(theta), r * sin(theta));	
		//inner circle connect line segment to outter circle to create ticks
		glVertex2f(0.9 * r * cos(theta), 0.9 * r * sin(theta));
	}
	glEnd();
	
	// time is at 3:45
	// hour hand
	glColor3f(0, 0, 0);
	glLineWidth(6);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(5 * cos(-30 * 3/4 * DtoR), 5 * sin(-30 * 3/4 * DtoR));
	glEnd();

	// minute hand
	glColor3f(0, 0, 0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(6 * cos(-180 * DtoR), 6 * sin(-180 * DtoR));
	glEnd();

	// second hand
	glColor3f(1, 1, 0.3);
	glColor3f(1, 0, 0);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(6.5 * cos(90 * DtoR), 6.5 * sin(90 * DtoR));
	glEnd();

}


void polarCurve(void)
{
	float r, theta;
	float alpha = 0;
	float beta = 2 * Pi;
	float x, y;
	float dTheta = 0.01;

	//glClear(GL_COLOR_BUFFER_BIT);	// clear the background
	axes();

	glLineWidth(2);
	glColor3f(0, 1, 1);
	glBegin(GL_LINE_STRIP);
	theta = alpha;
	while (theta <= beta)
	{
		r = 4 * (1 - cos(theta) *sin(4* theta));

		x = r * cos(theta);
		y = r * sin(theta);
		glVertex2f(x, y);

		theta += dTheta;
	}
	glEnd();

	glFlush();
}



// This is for demonstration. Use the vertices given the homework assignment
void stippledTriangle(void)	
{
	glColor3f(1, 1, 0);
	//---------- draw the background triangle -----------
	glBegin(GL_POLYGON);
	glVertex2f(-8, -6);
	glVertex2f(8, -6);
	glVertex2f(0, 8);
	glEnd();

	//---------- draw the stippled triangle ---------------
	glEnable(GL_POLYGON_STIPPLE);
	glColor3f(1, 0, 0);
	glPolygonStipple(mask);

	glBegin(GL_POLYGON);
	glVertex2f(-8, -6);
	glVertex2f(8, -6);
	glVertex2f(0, 8);
	glEnd();
	glDisable(GL_POLYGON_STIPPLE);

	glFlush();
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

	glClearColor(0.7, 0.7, 0.7, 1.0);	// background color; default black; (R, G, B, Opacity)
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
	glutCreateWindow("Katerina Yeung");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);	// envoked when the window is reshaped or moved; also envoked when the window is displayed at the first time

	glutMainLoop();

	return 0;
}