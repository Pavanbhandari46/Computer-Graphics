#include <stdio.h>
#include <GL/glut.h>

int flag=0;
float x0=100,y0=100,x1=50,y1=150,x2=100,y2=200,x3=150,y3=150;

void init()
{
	gluOrtho2D(0,200,0,200);
}


void edgedetect(float x0,float y0,float x1,float y1,float le[],float re[])
{
	if(y0>y1)
	{
		float temp;
		temp=x0;
		x0=x1;
		x1=temp;
		temp=y0;
		y0=y1;
		y1=temp;
	}
	
	
	float m;
	float x=x0;
	
	
	m=(x1-x0)/(y1-y0);
	
	for(int i=y0;i<y1;i++)
	{
		if(x<le[i])
			le[i]=x;
		if(x>re[i])
			re[i]=x;
		x+=m;	
	}
	
}


void scanfill(float x0,float y0,float x1,float y1,float x2,float y2,float x3,float y3)
{
     float le[500],re[500];
	for(int i=0;i<500;i++)
	{
		le[i]=500;
		re[i]=0;
	}
	
	edgedetect(x0,y0,x1,y1,le,re);
	edgedetect(x1,y1,x2,y2,le,re);
	edgedetect(x2,y2,x3,y3,le,re);
	edgedetect(x3,y3,x0,y0,le,re);
	
	for(int y=0;y<500;y++)
	{
		if(le[y]<re[y])
		{
			for(int i=le[y];i<re[y];i++)
			{
				glPointSize(10.0);
				glColor3f(1,0,0);
				glBegin(GL_POINTS);
				glVertex2f(i,y);
				glEnd();		
			}
		}
	}
}

void display()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x0,y0);
	glVertex2f(x1,y1);
	glVertex2f(x2,y2);
	glVertex2f(x3,y3);
	glEnd();
	
	if(flag==1)
		scanfill(x0,y0,x1,y1,x2,y2,x3,y3);
		
	glFlush();
}

void menu(int id)
{
	if(id==1)
		flag=1;
	else
		flag=0;
	display();
}
void main(int argc,char **argv)
{	
	printf("enter the vertices : ");
	scanf("%f%f%f%f%f%f%f%f",&x0,&y0,&x1,&y1,&x2,&y2,&x3,&y3);
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutCreateWindow("scanfill");
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	init();
	glutDisplayFunc(display);
	glutCreateMenu(menu);
	glutAddMenuEntry("fill",1);
	glutAddMenuEntry("clear",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}
