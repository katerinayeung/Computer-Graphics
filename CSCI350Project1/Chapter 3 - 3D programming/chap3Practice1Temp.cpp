//TODO: use the arrow keys to turn the camera around; use the '+' key to zoom in and the '-' key to zoom out
//TODO: Render a pyramid with vertices (0, 2, 0), (1, 0, 1), (1, 0, -1), (-1, 0, -1), and (-1, 0, 1).

#include <math.h>
#include <GL\glut.h>

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left, right, bottom, top, near, far;
const float REGION_DIM = 2;
const GLfloat DtoR = 0.017453;
GLfloat theta = 0, phi = 90, rho = 15;
GLfloat dTheta = 5, dPhi = 5, dRho = 0.5;


//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void keys(unsigned char k, int x, int y);
void specialKeys(int k, int x, int y);


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(rho*sin(theta*DtoR)*sin(phi*DtoR), rho*cos(phi*DtoR), rho*cos(theta*DtoR)*sin(phi*DtoR), 0, 0, 0, 0, 1, 0);
	

	//----------- the object --------------------------
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 0);
	glVertex3f(0, 2, 0);
	glColor3f(0, 1, 0);
	glVertex3f(1, 0, 1);
	glColor3f(0, 0, 1);
	glVertex3f(1, 0, -1);

	//TODO: complete the other three triangles
	glEnd();

	glBegin(GL_POLYGON);
	//TODO: complete the bottom square
	glEnd();

	glutSwapBuffers();	
	glutPostRedisplay();	// work with GLUT_DOUBLE
}

void init(void)
{
	float ratio = ww*1.0 / (wh*1.0);

	glClearColor(0.8, 0.8, 0.8, 1.0);	// background color; default black; (R, G, B, Opacity)
	glColor3f(0, 1, 1);	// drawing color; default white

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio >= 1)
	{
		left = -1.0 * REGION_DIM * ratio;
		right = REGION_DIM * ratio;
		bottom = -0.75 * REGION_DIM;
		top = 1.25 * REGION_DIM;
	}
	else
	{
		left = -1.0 * REGION_DIM;
		right = REGION_DIM;
		bottom = -0.75 * REGION_DIM / ratio;
		top = 1.25 * REGION_DIM / ratio;
	}

	near = REGION_DIM * 5;
	far = REGION_DIM * 20;

	glFrustum(left, right, bottom, top, near, far);
	glMatrixMode(GL_MODELVIEW);
}

void reshape(GLsizei w, GLsizei h)
{
	float ratio = w*1.0 / (h*1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio >= 1)
	{
		left = -1.0 * REGION_DIM * ratio;
		right = REGION_DIM * ratio;
		bottom = -0.75 * REGION_DIM;
		top = 1.25 * REGION_DIM;
	}
	else
	{
		left = -1.0 * REGION_DIM;
		right = REGION_DIM;
		bottom = -0.75 * REGION_DIM / ratio;
		top = 1.25 * REGION_DIM / ratio;
	}

	near = REGION_DIM * 5;
	far = REGION_DIM * 20;

	glFrustum(left, right, bottom, top, near, far);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);		// important!

	//------ reset the window size
	ww = w;
	wh = h;
}

void keys(unsigned char k, int x, int y)
{
	if (k == '+')		//zoom in
		rho -= dRho;
	else if (k == '-')
	{
		//TODO: zoom out
	}
	else if (k == 'R' || k == 'r')
	{
		//TODO:	reset the camera to its initial position
	}
}

void specialKeys(int k, int x, int y)
{
	if (k == GLUT_KEY_LEFT)
	{
		theta -= dTheta;

		if (theta < -360)
			theta += 360;
	}
	else if (k == GLUT_KEY_RIGHT)
	{
		//TODO: change theta in the other direction
	}
	else if (k == GLUT_KEY_UP)
	{
		//TODO: decrease phi
	}
	else if (k == GLUT_KEY_DOWN)
	{
		//TODO: change phi in the other direction
	}
}


void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // GLUT_DOUBLE work with glutPostRedisplay
	glutInitWindowSize(ww, wh);	
	glutInitWindowPosition(800, 200); 
	glutCreateWindow("3D programming");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keys);
	glutSpecialFunc(specialKeys);

	glutMainLoop();
}