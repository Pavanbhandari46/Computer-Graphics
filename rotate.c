#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

float tri[3][3]={{100,150,200},{100,200,100},{1,1,1}};

float rotate[3][3]={{0,0,0},{0,0,0},{0,0,0}};

float res[3][3]={{0,0,0},{0,0,0},{0,0,0}};

float h=100,k=100;

float m=0,n=0;

float theta;

void init()
{
	gluOrtho2D(0,500,0,500);
}

void multiply()
{
	
	int i,j,p;
	
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			res[i][j]=0;
			for(p=0;p<3;p++)
			{
				res[i][j]+=(rotate[i][p])*(tri[p][j]);
				
			}
		}
	}
}

void rot(float x,float y)
{
	
	rotate[0][0]=cos(theta);
	rotate[0][1]=-sin(theta);
	rotate[0][2]=x;
	
	rotate[1][0]=sin(theta);
	rotate[1][1]=cos(theta);
	rotate[1][2]=y;
	
	rotate[2][0]=0;
	rotate[2][1]=0;
	rotate[2][2]=1;
	
	multiply();
}

void drawTriangle(float a[3][3])
{
	glBegin(GL_POLYGON);
	glVertex2f(a[0][0],a[1][0]);
	glVertex2f(a[0][1],a[1][1]);
	glVertex2f(a[0][2],a[1][2]);
	glEnd();
}


void display()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(1,0,0);
	drawTriangle(tri);
	
	glColor3f(0,1,0);
	rot(0,0);
	drawTriangle(res);
	
	glColor3f(0,0,1);
	m=-h*(cos(theta)-1)+k*(sin(theta));
	n=-k*(cos(theta)-1)-h*(sin(theta));
	rot(m,n);
	drawTriangle(res);
	
	glFlush();
}

void main(int argc,char **argv)
{
	printf("enter the angle of rotation : ");
	scanf("%f",&theta);
	//theta*=(3.14/180);
	theta*=(22.0/7.0)/180.0;	
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	
	glutCreateWindow("rotate");
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}
