#include<GL/glut.h>
#include<fstream>
int knap[3][3]={{20,20},{40,20},{60,20}};//,{8,2},{10,2}
int out[3][3]={{20,70},{40,70},{60,70}};//,{8,7},{10,7}
	FILE *fp;
	char line[80];
	int present[4]={0};
	void draw(int x,int y)
	{
		glPushMatrix();
		glTranslated(x,y,0);
		glutSolidSphere(1,50,50);
		glPopMatrix();
	}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
fp=fopen("knaps.txt","r");

 while(fgets(line, 80, fp) != NULL)
   {
	 if(line[0]=='a'&&present[int(line[4])]==0)
	 {
	 	glColor3f(1.0,1.0,1.0);
	 	draw(out[int(line[4])-1][0],out[int(line[4])-1][1]);//vanish
	 
	 	glColor3f(1.0,0.0,0.0);
	 	draw(knap[int(line[4])-1][0],knap[int(line[4])-1][1]);//display
	 	}
	 else
	 if(present[int(line[4])]==1)
	 {
		glColor3f(1.0,1.0,1.0);
	 	draw(knap[int(line[4])-1][0],knap[int(line[4])-1][1]);//vanish
	 	glColor3f(1.0,0.0,0.0);
	 	draw(out[int(line[4])-1][0],out[int(line[4])-1][1]);//display
	 
	 }
	 for(long j=0;j<30000;j++)
	 {
	 	for(int k=0;k<=j;k++)
	 	{;
	 	}
	 }
   }

fclose(fp);
glFlush();
display();
	
}
int main(int argc,char **argv)
{
	
	glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowPosition(0,0);
glutInitWindowSize(150,150);
glutCreateWindow("0-1 knapsack");
glutDisplayFunc(display);
glClearColor(1.0,1.0,1.0,1.0);
gluOrtho2D(0,150,0,150);
glutMainLoop();
return 0;
}
