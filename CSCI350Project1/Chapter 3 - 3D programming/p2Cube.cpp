#include <math.h>
#include <GL\glut.h>

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left, right, bottom, top, back, front;
const float REGION_DIM = 2;

//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(2, 1, -3, 0, 0, 0, 0, 1, 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	//--------- face 1-------------------------------
	glColor3f(0, 0, 0); glVertex3f(-1, -1, -1);
	glColor3f(0, 1, 1); glVertex3f(1, -1, -1);
	glColor3f(1, 1, 1); glVertex3f(1, 1, -1);
	glColor3f(1, 0, 1); glVertex3f(-1, 1, -1);
	//-----------------------------------------------

	//--------- face 2-------------------------------
	glColor3f(1, 1, 1); glVertex3f(1, 1, -1);
	glColor3f(1, 0, 1); glVertex3f(-1, 1, -1);
	glColor3f(1, 0, 0); glVertex3f(-1, 1, 1);
	glColor3f(1, 1, 0); glVertex3f(1, 1, 1);
	//-----------------------------------------------

	//--------- face 3-------------------------------
	glColor3f(0, 1, 0); glVertex3f(1, -1, 1);
	glColor3f(0, 0, 0); glVertex3f(-1, -1, 1);
	glColor3f(1, 0, 0); glVertex3f(-1, 1, 1);
	glColor3f(1, 1, 0); glVertex3f(1, 1, 1);
	//-----------------------------------------------

	//--------- face 4-------------------------------
	glColor3f(0, 1, 0); glVertex3f(1, -1, 1);
	glColor3f(0, 0, 0); glVertex3f(-1, -1, 1);
	glColor3f(0, 0, 1); glVertex3f(-1, -1, -1);
	glColor3f(0, 1, 1); glVertex3f(1, -1, -1);
	//-----------------------------------------------

	//--------- face 5-------------------------------
	glColor3f(0, 1, 0); glVertex3f(1, -1, 1);
	glColor3f(0, 1, 1); glVertex3f(1, -1, -1);
	glColor3f(1, 1, 1); glVertex3f(1, 1, -1);
	glColor3f(1, 1, 0); glVertex3f(1, 1, 1);
	//-----------------------------------------------

	//--------- face 6-------------------------------
	glColor3f(0, 0, 1); glVertex3f(-1, -1, -1);
	glColor3f(1, 0, 1); glVertex3f(-1, 1, -1);
	glColor3f(1, 0, 0); glVertex3f(-1, 1, 1);
	glColor3f(0, 0, 0); glVertex3f(-1, -1, 1);
	//-----------------------------------------------

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
	front = 4 * REGION_DIM;

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
	front = 4 * REGION_DIM;

	glOrtho(left, right, bottom, top, back, front);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);		// important!

	//------ reset the window size
	ww = w;
	wh = h;
}

int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowSize(ww, wh);	
	glutInitWindowPosition(800, 200); 
	glutCreateWindow("cube");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}