#include <ctime>
#include <cstdio>
#include <iostream>
#include <gl/glut.h>
#include <string.h>


using namespace std;
void delay()
{
	int i, q;
	q = 15000;
	while (q != 0)
	{
		q--;
		i = 15000;
		while (i != 0)
		{
			i--;

		}
	}
}

bool state = true;
int j = 15;
char item[100] = { 0 };
int W, N, temp;
bool s[100] = { 0 };
int profit;

void print_Karray(int* price, int* weight, int** K, int N, int W);
void knapsack();

void init(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0f, 500.0f, 0.0f, 500.0f);
}
void draw_string(void* font, const char* str, int x, int y) {
	unsigned int i;
	glRasterPos2i(x, y);
	for (i = 0; i<strlen(str); i++) {
		glutBitmapCharacter(font, str[i]);
	}
}

void draw(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(50, 50, 0);

	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(3.0f);
	glBegin(GL_LINE_STRIP);
	glVertex2i(5, 5);
	glVertex2i(200, 5);
	glVertex2i(200, 350);
	glVertex2i(5, 350);
	glVertex2i(5, 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(120.0f, 420.f, 0.0f);
	glColor3f(1.0f, 0.6f, 0.2f);
	draw_string(GLUT_BITMAP_HELVETICA_18, "KNAPSACK BAG", 0, 0);
	glPopMatrix();




	glColor3f(1.0f, 1.0f, 1.0f);
	int a;
	for (a = 1; a<23; a++) {
		glPushMatrix();
		glTranslatef(300.0f, 400.f - a*j, 0.0f);
		sprintf(item, "Item %d", a);
		if (s[a]) {
			glTranslatef(-220, 0, 0);
			glColor3f(1.0, 1.0, 1.0);
			glRectf(0, 0, 45, 12);
		}
		glColor3f(1.0, 1.0, 1.0);
		glRectf(0, 0, 45, 12);
		glColor3f(0.0, 0.0, 1.0);
		draw_string(GLUT_BITMAP_HELVETICA_12, item, 0, 0);
		glPopMatrix();
	}
	for (a; a<46; a++) {
		glPushMatrix();
		glTranslatef(350.0f, 730.f - a*j, 0.0f);
		sprintf(item, "Item %d", a);
		if (s[a]) {
			glTranslatef(-220, 0, 0);
			glColor3f(1.0, 1.0, 1.0);
			glRectf(0, 0, 45, 12);
		}
		glColor3f(1.0, 1.0, 1.0);
		glRectf(0, 0, 45, 12);
		glColor3f(0.0, 0.0, 1.0);
		draw_string(GLUT_BITMAP_HELVETICA_12, item, 0, 0);
		glPopMatrix();
	}

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(350, 440, 0);
	sprintf(item, "Max Profit : %d", profit);
	draw_string(GLUT_BITMAP_HELVETICA_10, item, 0, 0);
	glPopMatrix();

	glFlush();
}

void idle() {
	if (state) {
		draw();
		knapsack();
		state = false;
	}
}

void knapsack() {
	int i, w, selected, unselected;
	int **K;
	int *price, *weight;
	freopen("test.txt", "r", stdin);
	cin >> W >> N;
	K = new int*[N + 1];
	price = new int[N + 1];
	weight = new int[W + 1];

	for (i = 0; i <= N; i++) {
		K[i] = new int[W + 1];
	}
	for (i = 1; i <= N; i++) {
		cin >> temp >> weight[i] >> price[i];
	}
	clock_t startTime = clock();

	for (i = 0; i <= N; i++)
		K[i][0] = 0;
	for (w = 0; w <= W; w++)
		K[0][w] = 0;

	for (i = 1; i <= N; i++) {
		for (w = 1; w <= W; w++) {
			if (weight[i] <= w) {
				selected = K[i - 1][w - weight[i]] + price[i];
				unselected = K[i - 1][w];
				if (selected > unselected) {
					K[i][w] = selected;
				}
				else {
					K[i][w] = unselected;
				}
			}
			else {
				K[i][w] = K[i - 1][w];
			}
		}
	}

	cout << "N is " << N << ", W is " << W << endl;

	print_Karray(price, weight, K, N, W);

	clock_t finalTime = clock();

	profit = K[N][W];
	cout << "The best price is " << K[N][W] << endl;
	cout << "CPU clock ? : " << finalTime - startTime << endl;
	cout << "?? 12141768 ???? ????????. " << endl;

}
void print_Karray(int* price, int* weight, int** K, int N, int W) {
	/* if (N == 0 || W <= 0) return 0;
	if (N == 1) {
	cout << "K[" << N << "][" << W << "] = " << K[N][W] << endl;
	return 0;
	}

	cout << "K[" << N << "][" << W << "] = max(" << "K[" << N - 1 << "][" << W << "], ";
	cout << price[N] << "+K[" << N - 1 << "][" << W - weight[N - 1] << "]) = ";
	cout << "max(" << K[N - 1][W] << "," << price[N] << "+" << K[N - 1][W - weight[N - 1]] << ")=" << K[N][W] << endl;
	delay();
	draw();

	if (weight[N - 1]>W) return print_Karray(price, weight, K, N - 1, W);
	else {
	if (price[N - 1] + K[N - 1][W - weight[N - 1]] > K[N - 1][W]) {
	profit = price[N - 1] + K[N - 1][W - weight[N - 1]];
	s[N] = 1;
	return print_Karray(price, weight, K, N - 1, W - weight[N - 1]);
	}
	else {
	profit = K[N - 1][W];
	//if condition
	if (weight[N] < W) {
	s[N] =0;
	}
	return print_Karray(price, weight, K, N - 1, W);
	}
	}*/

	int c = W;
	int m = N;
	while (m>0) {
		if (K[m][c] != K[m - 1][c]) {
			cout << "Item" << m << "(weight:" << weight[m] << ",profit:" << price[m] << ")";
			s[m] = 1;
			c = c - weight[m];

		}m--;
		cout << "K[" << N << "][" << W << "] = max(" << "K[" << N - 1 << "][" << W << "], ";
		cout << price[N] << "+K[" << N - 1 << "][" << W - weight[N - 1] << "]) = ";
		cout << "max(" << K[N - 1][W] << "," << price[N] << "+" << K[N - 1][W - weight[N - 1]] << ")=" << K[N][W] << endl;

		delay();
		draw();
	}





}
void knapp(){
	glutInit(&argc, argv);draw
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(600, 70);
	glutCreateWindow("knapsack");
	glutIdleFunc(idle);

	init();
	glutDisplayFunc(draw);
	glutMainLoop();
}