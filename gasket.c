#include<stdio.h>
#include<GL/glut.h>
float v[4][3] = { {0,0,-1}, {0,1,1}, {-1,-1,1}, {1,-1,1} };
int m;
void display();
void init();
void triangle(float a[],float b[],float c[]);
void d_triangle(float a[],float b[],float c[],int m);

void init(){
	glOrtho(-2,2,-2,2,2,-2);
}

void triangle(float a[3], float b[3], float c[3]){
	glBegin(GL_POLYGON);
		glVertex3fv(a);
		glVertex3fv(b);
		glVertex3fv(c);
	glEnd();
	
}


void display(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0,0,0);
	d_triangle(v[1],v[2],v[3],m);
	glColor3f(1,0,0);
	d_triangle(v[0],v[1],v[2],m);
	glColor3f(0,1,0);
	d_triangle(v[0],v[2],v[3],m);
	glColor3f(0,0,1);
	d_triangle(v[0],v[1],v[3],m);
	glFlush();

}

void d_triangle(float a[],float b[],float c[],int m){

float v1[3],v2[3],v3[3];
int i;
if(m > 0){
	for(i = 0; i < 3; i++){
		v1[i] = (a[i] + b[i])/2;
		v2[i] = (a[i] + c[i])/2;
		v3[i] = (c[i] + b[i])/2;		
	}	
	d_triangle(a,v1,v2,m-1);
	d_triangle(v1,b,v3,m-1);
	d_triangle(v2,v3,c,m-1);
} else {
	triangle(a,b,c);
}
}


void main(int argc, char **argu){
	printf("Enter the number of divisions: ");
	scanf("%d",&m);
	glutInit(&argc,argu);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH | GLUT_RGB);
	glutCreateWindow("gasket");
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	init();
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
