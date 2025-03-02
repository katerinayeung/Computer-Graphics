#include <math.h>
#include <GL\glut.h>

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left, right, bottom, top, back, front;
const float REGION_DIM = 2;
const GLfloat DtoR = 0.017453;
GLfloat c_x = 0, c_y = 0, c_z = 3;
GLfloat dx = 0.5, dy = 0.5, dz = 0.5;
GLfloat direction = 1;

//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void mouse(int, int, int, int);
void axes(void);

void axes()
{
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	glVertex3f(-0.8*REGION_DIM, 0, 0);
	glVertex3f(0.8 * REGION_DIM, 0, 0);

	glVertex3f(0, -0.8 * REGION_DIM, 0);
	glVertex3f(0, 0.8 * REGION_DIM, 0);

	glVertex3f(0, 0, -0.8 * REGION_DIM);
	glVertex3f(0, 0, 0.8 * REGION_DIM);
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(c_x, c_y, c_z, 0, 0, 0, 0, 1, 0);

	axes();

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
		c_x = c_x + dx * direction;
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		c_y = c_y + dy * direction;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		c_z = c_z + dz * direction;
	}
}

void keys(unsigned char k, int x, int y)
{
	if (k == 'p')
		direction = 1;
	else if (k == 'n')
		direction = -1;
	else
	{
		c_x = 0; c_y = 0; c_z = 3;
	}
}

int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // GLUT_DOUBLE work with glutPostRedisplay
	glutInitWindowSize(ww, wh);	// default size 300 by 300
	glutInitWindowPosition(800, 200); // defualt at (0, 0)
	glutCreateWindow("cube");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keys);
	glutMouseFunc(mouse);

	glutMainLoop();
	return 0;
}