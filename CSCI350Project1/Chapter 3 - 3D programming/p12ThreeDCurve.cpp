#include <math.h>
#include "GL/glut.h"


//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left, right, bottom, top, near, far;
const float REGION_DIM = 8;
const GLfloat DtoR = 0.017453;
const GLfloat Pi = 3.1415926535;
GLfloat rho = 10.0;
GLfloat phi = 90.0;
GLfloat theta = 0.0;
GLfloat dTheta = 5, dPhi = 5, dRho = 0.5;
GLfloat direction = 1.0;
GLint whichCurve = 1;

//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void mouse(int, int, int, int);
void curve1(void);
void curve2(void);
void curve3(void);


void curve3(void)
{
	float x, y, z, t;
	float dt = 0.01;
	int count;

	count = (int)(2 * Pi / dt);

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < count; i++)
	{
		t = i*dt;
		x = (4+sin(20*t))*cos(t);
		y = (4+sin(20*t))*sin(t);
		z = cos(20*t);

		glVertex3f(x, y, z);
	}
	glEnd();
}

void curve2(void)
{
	float x, y, z, t;
	float dt = 0.01;
	int count;

	count = (int)(2 * Pi / dt);

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < count; i++)
	{
		t = i*dt;
		x = cos(t);
		y = sin(t);
		z = sin(2*t);

		glVertex3f(x, y, z);
	}
	glEnd();
}

void curve1(void)
{
	float x, y, z, t;
	float dt = 0.01;
	int count;

	count = (int)(2 * Pi / dt);

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < count; i++)
	{
		t = i*dt;
		x = sin(3 * t)*cos(t);
		y = sin(3 * t)*sin(t);
		z = t;

		glVertex3f(x, y, z);
	}
	glEnd();
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(rho * sin(theta * DtoR) * sin(phi * DtoR), rho * cos(phi * DtoR), rho * cos(theta * DtoR) * sin(phi * DtoR), 0, 0, 0, 0, 1, 0);


	glColor3f(0, 1, 1);
	glLineWidth(3);
	switch (whichCurve)
	{
	case 1:
		curve1();
		break;
	case 2:
		curve2();
		break;
	case 3: 
		curve3();
		break;
	default:
		break;
	}

	glutSwapBuffers();	
	glutPostRedisplay();	// work with GLUT_DOUBLE
}

void init(void)
{
	float ratio = ww*1.0 / (wh*1.0);

	glClearColor(0.5, 0.5, 0.5, 1.0);	// background color; default black; (R, G, B, Opacity)
	glColor3f(0, 1, 1);	// drawing color; default white

	if (ratio >= 1)
	{
		left = -1.0 * REGION_DIM * ratio;
		right = REGION_DIM * ratio;
		bottom = -1.0 * REGION_DIM;
		top = REGION_DIM;
	}
	else
	{
		left = -1.0 * REGION_DIM;
		right = REGION_DIM;
		bottom = -1.0 * REGION_DIM / ratio;
		top = REGION_DIM / ratio;
	}

	near = REGION_DIM * 0.7;
	far = REGION_DIM * 4.0;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(left, right, bottom, top, near, far);
	glMatrixMode(GL_MODELVIEW);
}

void reshape(GLsizei w, GLsizei h)
{
	float ratio = w*1.0 / (h*1.0);

	if (ratio >= 1)
	{
		left = -1.0 * REGION_DIM * ratio;
		right = REGION_DIM * ratio;
		bottom = -1.0 * REGION_DIM;
		top = REGION_DIM;
	}
	else
	{
		left = -1.0 * REGION_DIM;
		right = REGION_DIM;
		bottom = -1.0 * REGION_DIM / ratio;
		top = REGION_DIM / ratio;
	}

	near = REGION_DIM * 0.7;
	far = REGION_DIM * 4.0;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(left, right, bottom, top, near, far);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);		// important!

	//------ reset the window size
	ww = w;
	wh = h;
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		theta += dTheta * direction;
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		rho += dRho * direction;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		phi += dPhi * direction;
	}
}

void keys(unsigned char k, int x, int y)
{
	if (k == 'p')
		direction = 1.0;
	else if (k == 'n')
		direction = -1.0;
	else if (k == '1')
		whichCurve = 1;
	else if (k == '2')
		whichCurve = 2;
	else if (k == '3')
		whichCurve = 3;
}

int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowSize(ww, wh);	
	glutInitWindowPosition(800, 200); 
	glutCreateWindow("3D programming");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);
	
	glutMainLoop();
	return 0;
}