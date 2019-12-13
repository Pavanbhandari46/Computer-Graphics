#include <GL/glut.h>
#include <stdbool.h>
#include <stdio.h>

int xmin=50;
int xmax=100;
int ymin=50;
int ymax=100;
int x0=70,y0=20;
int x1=80,y1=120;
int bottom =1,left=2,top=4,right=8;

void init()
{
	gluOrtho2D(0,300,0,300);
}

int compute(int x, int y)
{
	int code=0;
	if(x<xmin)
		code=code|left;
	if(x>xmax)
		code=code|right;
	if(y<ymin)
		code=code|bottom;
	if(y>ymax)
		code=code|top;
	return code;
}

void cohen(int x0,int y0,int x1,int y1)
{
	int code0,code1;
	float x,y;
	bool done=false,accept=false;
	float m =(float)(y1-y0)/(x1-x0);
	code0=compute(x0,y0);
	code1=compute(x1,y1);
	do
	{
		if(code0 & code1)
			done=true;
		else if(!(code0 | code1))
		{
			done=true;
			accept=true;
		}
		else
		{
			int out;
			out=code0?code0:code1;
			if(out & top)
			{
				x=x0+((ymax-y0)/m);
				y=ymax;
			}
			if(out & bottom)
			{
				y=ymin;
				x=x0+((ymin-y0)/m);
			}
			if(out & left)
			{
				x=xmin;
				y=y0+((xmin-x0)*m);
			}
			if(out & right)
			{
				y=y0+((xmax-x0)*m);
				x=xmax;
			}
			if(out==code0)
			{
				x0=x;
				y0=y;
				code0=compute(x0,y0);
			}
			if(out==code1)
			{
				x1=x;
				y1=y;
				code1=compute(x1,y1);
			}
		}
	}while(!done);
	if(accept)
	{
		glTranslatef(100,100,0);
		glColor3f(0,1,0);
		glBegin(GL_LINE_LOOP);
		glVertex2i(xmin,ymin);
		glVertex2i(xmax,ymin);
		glVertex2i(xmax,ymax);
		glVertex2i(xmin,ymax);
		glEnd();
		glColor3f(1,0,0);
		glBegin(GL_LINES);
		glVertex2i(x0,y0);
		glVertex2i(x1,y1);
		glEnd();
	}
}

void display()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,1,0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(xmin,ymin);
	glVertex2i(xmax,ymin);
	glVertex2i(xmax,ymax);
	glVertex2i(xmin,ymax);
	glEnd();
	glColor3f(1,0,0);
	glBegin(GL_LINES);
	glVertex2i(x0,y0);
	glVertex2i(x1,y1);
	glEnd();
	
	cohen(x0,y0,x1,y1);
	glFlush();
}

void main(int argc,char **argv)
{
	printf("enter the points : ");
	scanf("%d%d%d%d",&x0,&y0,&x1,&y1);	
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	
	glutCreateWindow("Line Clipping");
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}
