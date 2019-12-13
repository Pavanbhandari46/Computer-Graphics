#include <stdio.h>
#include <GL/glut.h>

float x0=0;
float y0=0;
float x1=0;
float y1=0;

void init()
{
	gluOrtho2D(0,100,0,100);
}

void drawpixel(int x,int y)
{
	glColor3f(1,0,0);
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();

}

void swap()
{
	int temp;
	temp=x0;
	x0=x1;
	x1=temp;
	temp=y0;
	y0=y1;
	y1=temp;
}

void linedrawing(float x0,float y0,float x1, float y1, float m)
{
	float x,y,dx,dy,ppos,pneg;
	if(x0>x1)
		swap();
	dx=abs(x1-x0);
	dy=abs(y1-y0);
	x=x0;
	y=y0;
	pneg=2*dy;
	ppos=2*(dy-dx);
	float p = (2*dy)-dx;
	drawpixel(x,y);
	while(x<x1)
	{
		x++;
		if(p<0)
			p+=pneg;
		else
		{
			if(m<0)
				y--;
			else
				y++;
			p+=ppos;
		}
		drawpixel(x,y);
	}
}

void linedrawing1(float x0,float y0,float x1, float y1, float m)
{
	float x,y,dx,dy,ppos,pneg;
	if(x0>x1)
		swap();
	dx=abs(x1-x0);
	dy=abs(y1-y0);
	x=x0;
	y=y0;
	pneg=2*dx;
	ppos=2*(dx-dy);
	float p = (2*dx)-dy;
	drawpixel(x,y);
	while(y<y1)
	{
		y++;
		if(p<0)
			p+=pneg;
		else
		{
			x++;
			p+=ppos;
		}
		drawpixel(x,y);
	}
}

void display()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	float m= (y1-y0)/(x1-x0);
	if(m<1)
		linedrawing(x0,y0,x1,y1,m);
	else
		linedrawing1(x0,y0,x1,y1,m);
	glFlush();	
}

void main(int argc,char **argv)
{
	printf("enter the starting vertex : ");
	scanf("%f%f",&x0,&y0);
	printf("enter the end vertex : ");
	scanf("%f%f",&x1,&y1);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB);
	glutCreateWindow("Line Drawing Algorithm");
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}
