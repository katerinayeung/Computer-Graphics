// In this practice, you color a region between two curves y1 = sin(2*x)
// and y2 = cos(2*x). Also, thicken each curve with a different color. 

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
void region(void);

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// clear the background

	//---------- graphics objects -------------
	region();

	glFlush();	// force to render, work with single buffer
}

void region(void)
{
    GLfloat x, y1, y2;
    GLfloat a = -4;      // left end of the interval
    GLfloat b = 4;       // right end of the interval
    GLfloat dx = 0.01;   // increment for the x-values

    // Start shading the region between the curves
    glBegin(GL_QUAD_STRIP);
    x = a;
    while (x <= b) {  // loop through x-values from a to b
        // First curve: y = sqrt(16 - x^2)
        y1 = sqrt(16 - x * x);  // upper semicircle (radius 4)

        // Set color for the region between the curves (Red for shading)
        glColor3ub(255, 0, 0);  // Red color
        glVertex2f(x, y1);

        // Second curve: y = 2 * sqrt(16 - x^2)
        y2 = 2 * sqrt(16 - x * x);  // upper semicircle (scaled by 2)

        // Set color for the second curve (Green for shading)
        glColor3f(0.0, 1.0, 0.0);  // Green color
        glVertex2f(x, y2);

        // Increment x by dx to move to the next point
        x += dx;
    }
    glEnd();

    // Draw the first curve: y = sqrt(16 - x^2) (Red)
    glLineWidth(2);  // Make the curve thicker
    glColor3f(1.0, 0.0, 0.0);  // Red color for the first curve
    glBegin(GL_LINE_STRIP);
    x = a;
    while (x <= b) {  // loop through x-values from a to b
        y1 = sqrt(16 - x * x);  // upper semicircle
        glVertex2f(x, y1);  // plot the point
        x += dx;
    }
    glEnd();

    // Draw the second curve: y = 2 * sqrt(16 - x^2) (Green)
    glLineWidth(2);  // Make the curve thicker
    glColor3f(0.0, 1.0, 0.0);  // Green color for the second curve
    glBegin(GL_LINE_STRIP);
    x = a;
    while (x <= b) {  // loop through x-values from a to b
        y2 = 2 * sqrt(16 - x * x);  // upper semicircle (scaled by 2)
        glVertex2f(x, y2);  // plot the point
        x += dx;
    }
    glEnd();
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
	glutCreateWindow("An Ellipse");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);	

	glutMainLoop();

	return 0;
}