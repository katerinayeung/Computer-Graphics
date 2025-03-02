#include <math.h>
#include <iostream>
#include <time.h>
#include <GL/glut.h>

GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left = -2.0;
GLfloat right = 2.0;
GLfloat bottom = -2.0;
GLfloat top = 2.0;
float DtoR = 0.017453; // the ratio of degree to radian

float x = 0.0;
float y = 0.0;
float radius = 1.0;
float secondAngle = 90;  // starting at 0 seconds
float minuteAngle = 180; // starting at 45 minutes
float hourAngle = -22.5;   // starting at 3:00
float multiple = 1000;  // Normal speed

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
    0x00, 0x00, 0xff, 0xff 
 };

// Function Prototypes
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void drawclock(void);
void secondHand(float angle);
void minuteHand(float angle);
void hourHand(float angle);
void timer(int v);
void mouse(int button, int state, int x, int y);

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawclock();
    hourHand(hourAngle);
    minuteHand(minuteAngle);
    secondHand(secondAngle);

    glFlush();
}

void drawclock(void)
{
    float r = 1.0;
    float x, y;
    float theta = 0.0;

    // Draw the clock face with stippling
    glColor3f(0.0, 0.3, 0.3);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10)
    {
        theta = i * DtoR;
        x = r * cos(theta);
        y = r * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();

    // Apply stippling
    glEnable(GL_POLYGON_STIPPLE);
    glColor3f(1, 0, 0);
    glPolygonStipple(mask);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10)
    {
        theta = i * DtoR;
        x = r * cos(theta);
        y = r * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
    glDisable(GL_POLYGON_STIPPLE);

    // Draw 12 ticks (hour markers)
    glColor3f(1, 1, .3);
    glBegin(GL_LINES);
    for (int i = 0; i < 360; i += 30) // 30 degrees per tick
    {
        theta = i * DtoR;
        glVertex2f(r * cos(theta), r * sin(theta));
        glVertex2f(0.9 * cos(theta), 0.9 * sin(theta));
    }
    glEnd();
}

void hourHand(float angle)
{
    glColor3f(0, 0, 0);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(0.5 * cos(angle * DtoR), 0.5 * sin(angle * DtoR));
    glEnd();
}

void minuteHand(float angle)
{
    glColor3f(0, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(0.7 * cos(angle * DtoR), 0.7 * sin(angle * DtoR));
    glEnd();
}

void secondHand(float angle)
{
    glColor3f(1, 1, 0.3);
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(0.85 * cos(angle * DtoR), 0.85 * sin(angle * DtoR));
    glEnd();
}

void timer(int v)
{
    secondAngle -= 6.0;  // 6 degrees per second
    minuteAngle -= 6.0 / 60.0;  // 1 minute = 6 degrees
    hourAngle -= 6.0 / 720.0;  // 1 hour = 30 degrees

    // Wrap angles
    if (secondAngle < -360.0) secondAngle += 360.0;
    if (minuteAngle < -360.0) minuteAngle += 360.0;
    if (hourAngle < -360.0) hourAngle += 360.0;

    glutPostRedisplay();
    glutTimerFunc(multiple, timer, v);  // Recursive call for continuous animation
}

void mouse(int button, int state, int x, int y)
{
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
    {
        multiple = 1000;  // Normal speed
    }
    if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN))
    {
        multiple = 25;  // Fast speed
    }
}

void init(void)
{
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(left, right, bottom, top);
    glMatrixMode(GL_MODELVIEW);
}

void reshape(GLsizei w, GLsizei h)
{
    float ratio = w * 1.0 / (h * 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (ratio >= 1)
        gluOrtho2D(left * ratio, right * ratio, bottom, top);
    else
        gluOrtho2D(left, right, bottom / ratio, top / ratio);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
}

int main()
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(ww, wh);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Katerina Yeung");
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(multiple, timer, 1);
    glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
}
