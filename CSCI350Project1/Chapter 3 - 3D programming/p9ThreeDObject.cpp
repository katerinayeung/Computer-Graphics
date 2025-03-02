#include <math.h>
#include "GL/glut.h"

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left, right, bottom, top, back, front;
const float REGION_DIM = 4;
const GLfloat DtoR = 0.017453;
//GLfloat fov = 45.0, aspect = 1;
GLfloat theta = 0, phi = 90, rho = 10;
GLfloat dTheta = 5, dPhi = 5, dRho = 0.5;
GLfloat a = 1, b = 1, c = 1;
GLfloat dA = 0.1, dB = 0.1, dC = 0.1;
GLfloat direction = 1.0;

//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void keys(unsigned char k, int x, int y);
void mouse(int, int, int, int);
void sideSurface(float r, float R, float h, int slices, int stacks);
void sideSurface2(float r, float R, float h, int slices, int stacks);
void surface(float r, float R, float h, int slices, int stacks);
void ellipsoid(float a, float b, float c, int slices, int stacks);


void ellipsoid(float a, float b, float c, int slices, int stacks)
{
	float Theta, Phi;
	float dTheta = 360.0 / slices;
	float dPhi = 180.0 / stacks;
	float x, y, z;

	glBegin(GL_QUADS);
	Phi = 0;
	while (Phi <= 180.0 - dPhi)
	{
		Theta = 0;
		while (Theta <= 360.0 - dTheta)
		{
			x = a * sin(Phi * DtoR) * cos(Theta * DtoR);
			y = b * sin(Phi * DtoR) * sin(Theta * DtoR);
			z = c * cos(Phi * DtoR);
			glVertex3f(x, y, z);

			x = a * sin((Phi+dPhi) * DtoR) * cos(Theta * DtoR);
			y = b * sin((Phi + dPhi) * DtoR) * sin(Theta * DtoR);
			z = c * cos((Phi + dPhi) * DtoR);
			glVertex3f(x, y, z);

			x = a * sin((Phi + dPhi) * DtoR) * cos((Theta+dTheta) * DtoR);
			y = b * sin((Phi + dPhi) * DtoR) * sin((Theta+dTheta) * DtoR);
			z = c * cos((Phi + dPhi) * DtoR);
			glVertex3f(x, y, z);

			x = a * sin(Phi * DtoR) * cos((Theta + dTheta) * DtoR);
			y = b * sin(Phi * DtoR) * sin((Theta + dTheta) * DtoR);
			z = c * cos(Phi * DtoR);
			glVertex3f(x, y, z);

			Theta += dTheta;
		}

		Phi += dPhi;
	}
	glEnd();
}

void sideSurface(float r, float R, float h, int slices, int stacks)
{
	float alpha; 
	float dAlpha = 360.0 / slices; 

	glBegin(GL_QUADS);
	alpha = 0;
	while (alpha <= 360.0-dAlpha)
	{
		glVertex3f(R * cos(alpha * DtoR), R * sin(alpha * DtoR), 0);
		glVertex3f(R * cos((alpha+dAlpha) * DtoR), R * sin((alpha+dAlpha) * DtoR), 0);
		glVertex3f(r * cos((alpha+dAlpha) * DtoR), r * sin((alpha+dAlpha) * DtoR), h);
		glVertex3f(r * cos(alpha * DtoR), r * sin(alpha * DtoR), h);

		alpha += dAlpha;
	}
	glEnd();
}

void sideSurface2(float r, float R, float h, int slices, int stacks)
{
	float alpha;
	float dAlpha = 360.0 / slices;

	glBegin(GL_QUAD_STRIP);
	alpha = 0;
	while (alpha <= 360.0)
	{
		glVertex3f(R * cos(alpha * DtoR), R * sin(alpha * DtoR), 0);
	
		glVertex3f(r * cos(alpha * DtoR), r * sin(alpha * DtoR), h);

		alpha += dAlpha;
	}
	glEnd();
}

void surface(float r, float R, float h, int slices, int stacks)
{
	float alpha;
	float dAlpha = 360.0 / slices;

	glBegin(GL_QUADS);
	alpha = 0;
	while (alpha <= 360.0 - dAlpha)
	{
		glVertex3f(R * cos(alpha * DtoR), R * sin(alpha * DtoR), 0);
		glVertex3f(R * cos((alpha + dAlpha) * DtoR), R * sin((alpha + dAlpha) * DtoR), 0);
		glVertex3f(r * cos((alpha + dAlpha) * DtoR), r * sin((alpha + dAlpha) * DtoR), h);
		glVertex3f(r * cos(alpha * DtoR), r * sin(alpha * DtoR), h);

		alpha += dAlpha;
	}
	glEnd();

	glBegin(GL_POLYGON);
	alpha = 0;
	while (alpha <= 360.0 - dAlpha)
	{
		glVertex3f(R * cos(alpha * DtoR), R * sin(alpha * DtoR), 0);
	
		alpha += dAlpha;
	}
	glEnd();

	glBegin(GL_POLYGON);
	alpha = 0;
	while (alpha <= 360.0 - dAlpha)
	{
		glVertex3f(r * cos(alpha * DtoR), r * sin(alpha * DtoR), h);

		alpha += dAlpha;
	}
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(rho*sin(phi*DtoR)*sin(theta*DtoR), rho*cos(phi*DtoR), rho*sin(phi*DtoR)*cos(theta*DtoR), 
				0, 0, 0, 0, 1, 0);
	
	//----- draw in FILL mode -----------------
	glColor3f(1, 1, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	sideSurface(a, b, c, 40, 20);
	//sideSurface2(a, b, c, 40, 20);
	//surface(a, b, c, 40, 20);
	//ellipsoid(a, b, c, 40, 20);

	//------- draw in LINE mode -----------
	glColor3f(1, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	sideSurface(a, b, c, 40, 20);
	//sideSurface2(a, b, c, 40, 20);
	//surface(a, b, c, 40, 20);
	//ellipsoid(a*1.005, b*1.005, c*1.005, 40, 20);

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

	back = -4.0 * REGION_DIM;
	front = 4.0 * REGION_DIM;
	glOrtho(left, right, bottom, top, back, front);
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

	back = -4.0 * REGION_DIM;
	front = 4.0 * REGION_DIM;
	glOrtho(left, right, bottom, top, back, front);
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
	if (k == 'p' || k == 'P')
		direction = 1.0;
	else if (k == 'n' || k == 'N')
		direction = -1.0;
	else if (k == 'a' || k == 'A')
		a += dA * direction;
	else if (k == 'b' || k == 'B')
		b += dB * direction;
	else if (k == 'c' || k == 'C')
		c += dC * direction;
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