#include <math.h>
#include "GL/glut.h"


GLsizei ww = 512, wh = 512;
GLfloat fov = 45.0;	// field of view/vision; angle in the y-direction
GLfloat aspect = 1;	// width to height; x/y
GLfloat near =5.0;
GLfloat far = 15.0;
GLfloat rho = 10.0;
GLfloat phi = 90.0;
GLfloat theta = 0.0;
GLfloat dTheta = 5, dPhi = 5, dRho = 0.5;
GLfloat direction = 1.0;
GLfloat DtoR = 0.017453;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(rho*sin(theta*DtoR)*sin(phi*DtoR), rho*cos(phi*DtoR), rho*cos(theta*DtoR)*sin(phi*DtoR), 0, 0, 0, 0, 1, 0);

	glColor3f(1, 0, 0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glutWireCube(2);
	glColor3f(1, 1, 0);
	glutSolidCube(1.99);

	glutSwapBuffers();
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, aspect*w/h, near, far);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);

	ww = w;
	wh = h;
}

void init()
{
	glClearColor(1, 1, 1, 1);
	glColor3f(0, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, aspect, near, far);
	glMatrixMode(GL_MODELVIEW);
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
	if (k == 'p' || k == 'P')
		direction = 1.0;
	else if (k == 'n' || k == 'N')
		direction = -1.0;
}


int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(800, 200);
	glutCreateWindow("Perspective view");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);

	glutMainLoop();
	return 0;
}