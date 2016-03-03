#include <GL/gl.h>
#include <GL/glu.h>
#include<iostream>
#include<cmath>
#include<stdlib.h>
#include <GL/glut.h>
#define W 640
#define H 480
#define STEP 0.0001
using namespace std;
int numpoints=0;
class point{
	public: int x,y;
};
point *ctrl,*aux;
int i,j,f; float t;
int factorial(int number){
		int temp;
        if(number <= 1) return 1;
		temp = number * factorial(number - 1);
		return temp;
}
double binomial( int f, int n){
	double com=factorial(n)/(factorial(f)*factorial(n-f));
	return com;
}
void myDisp()
{

}
point bezier(point *ctrl,float t,int n){
	point N;
	N.x=N.y=0;
	for(i=0;i<=n;i++){
		N.x+=ctrl[i].x*binomial(i,n)*pow(t,i)*pow((1-t),(n-i));
		N.y+=ctrl[i].y*binomial(i,n)*pow(t,i)*pow((1-t),(n-i));
	}
	return N;
}
void init(){
	glClearColor(1.0,1.0,1.0,0.0);
	glColor3f(1.0,0.5,0.0);
	glPointSize(3.0);
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glLoadIdentity();
	gluOrtho2D(0.0,W,0.0,H);
}
void drawpoint(int x,int y){
	glColor3f(1.0,0.0,1.0);
	glPointSize(6.0);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	glFlush();
}
void setpixel(point p1,point p2,float col){
	if(col<1) glColor3f(0.0,1.0,0.0);
	else glColor3f(0.0,0.0,.5);
	glLineWidth(2.5);
	glBegin(GL_LINES);
		glVertex2f(p1.x,p1.y);
		glVertex2f(p2.x,p2.y);
	glEnd();
	glFlush();
}
void mouse(int button,int state,int x,int y){
	point M,P=ctrl[0];
	int a,b;
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		a=ctrl[numpoints].x=x;
		b=ctrl[numpoints].y=H-y;
		numpoints++;
		drawpoint(x,H-y);
	}
	else if(button==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN){
			for(t = 0;t <= 1.0; t += STEP){
					M=bezier(ctrl,t,numpoints-1);
					setpixel(P,M,t);
					P=M;
			}
		}
		else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
			for(i=0;i<numpoints-1;i++)
				setpixel(ctrl[i],ctrl[i+1],5);
		}
}
int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(W,H);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Bezier Curve");
    glutDisplayFunc(myDisp);
    ctrl=(point *)malloc(sizeof(point));
    glutMouseFunc(mouse);
    init();
    glutMainLoop();
    free(ctrl);
    return 0;
}

