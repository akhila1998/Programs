
#include <GL/glut.h>
//#endif

#include <stdlib.h>
#define RANDOM (10-20*((double)rand()/RAND_MAX))

const int width = 32;
const int height = 32;
const int featuresize = 16;
/* GLUT callback Handlers */
double values[width*height];

GLfloat angle, angle2;
int moving, startx, starty;
static void resize(int width, int height)
{


	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0f, 20.0f, -1.0f, 20.0f, -100.0f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
double sample(int x, int y)
{
	return values[(x & (width - 1)) + (y & (height - 1))*width];
}

void setSample(int x, int y, double value)
{
	values[(x & (width - 1)) + (y & (height - 1)) * width] = value;
}

void sampleSquare(int x, int y, int size, double value)
{
	int hs = size / 2;

	// a     b
	//
	//    x
	//
	// c     d

	double a = sample(x - hs, y - hs);
	double b = sample(x + hs, y - hs);
	double c = sample(x - hs, y + hs);
	double d = sample(x + hs, y + hs);

	setSample(x, y, ((a + b + c + d) / 4.0) + value);

}

void sampleDiamond(int x, int y, int size, double value)
{
	int hs = size / 2;

	//   c
	//
	//a  x  b
	//
	//   d

	double a = sample(x - hs, y);
	double b = sample(x + hs, y);
	double c = sample(x, y - hs);
	double d = sample(x, y + hs);

	setSample(x, y, ((a + b + c + d) / 4.0) + value);
}
void DiamondSquare(int stepsize, double scale)
{

	int halfstep = stepsize / 2;



	for (int y = halfstep; y < height + halfstep; y += stepsize)
	{
		for (int x = halfstep; x < width + halfstep; x += stepsize)
		{
			sampleSquare(x, y, stepsize, RANDOM * scale);
		}
	}

	for (int y = 0; y < height; y += stepsize)
	{
		for (int x = 0; x < width; x += stepsize)
		{
			sampleDiamond(x + halfstep, y, stepsize, RANDOM * scale);
			sampleDiamond(x, y + halfstep, stepsize, RANDOM * scale);

		}
	}

}

static void display(void)
{



	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(angle, 0, 1, 0);
	glRotatef(angle2, 0, 0, 1);

	glPointSize(3.0f);

	glColor3f(0, 0, 0);

	//   glVertex2f(0,0);

	for (int y = 0; y < height; y += 1)
		for (int x = 0; x < width; x += 1)
		{

			glBegin(GL_LINE_LOOP);
			glVertex3f(x, y, sample(x, y));
			glVertex3f(x + 1, y, sample(x + 1, y));
			glVertex3f(x, y + 1, sample(x, y + 1));
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex3f(x + 1, y + 1, sample(x + 1, y + 1));
			glVertex3f(x + 1, y, sample(x + 1, y));
			glVertex3f(x, y + 1, sample(x, y + 1));
			glEnd();
		}

	glFlush();
	glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
	case 'q':
		exit(0);
		break;


	}

	//    glutPostRedisplay();
}

static void idle(void)
{
	//  glutPostRedisplay();
}
void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON&&state == GLUT_DOWN)
	{
		moving = 1;
		startx = x;
		starty = y;
	}
	if (btn == GLUT_LEFT_BUTTON&&state == GLUT_UP)
	{
		moving = 0;
	}
}
void motion(int x, int y)
{
	if (moving)
	{
		angle = angle + (x - startx);
		angle2 = angle2 + (y - starty);
		startx = x;
		starty = y;
		glutPostRedisplay();
	}
}

void init()
{
	const double t = glutGet(GLUT_ELAPSED_TIME);
	srand((int)t);


	for (int y = 0; y < height; y += featuresize)
		for (int x = 0; x < width; x += featuresize)
		{
			setSample(x, y, RANDOM);  //IMPORTANT: frand() is a random function that returns a value between -1 and 1.
		}

	int samplesize = featuresize;

	double scale = 1.0;

	while (samplesize > 1)
	{

		DiamondSquare(samplesize, scale);

		samplesize /= 2;
		scale /= 2.0;
	}

}
/* Program entry point */


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(10, 10);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("Diamond Square Algorithm");
	init();

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);

	glutMotionFunc(motion);
	glClearColor(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);



	glutMainLoop();

	return 0;
}