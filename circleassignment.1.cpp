
#include <GL/Gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#define w 500
#define h 380
GLint x1,x2,zz,y2,r;
GLint xc,yc;
GLfloat a1,b1,c1;
void set(GLint x,GLint y)
 {
	glColor3f(3.0,5.0,.0);
	glPointSize(5.0);
	glBegin(GL_POINTS);
    glVertex2i(x,y);
	glEnd();
	glFlush();
 }
class circle
 {
   public:
	void Mid_Point()
	{
		int x,y;
		float dp;
		x=0;
		y=r;
		dp=1-r;
		set(xc,yc);
		glBegin(GL_LINES);
            glVertex2f(xc,yc);
            glVertex2f(xc,yc+r);
		glEnd();
		while(x<=y)
		{
			if(dp<=0)
			 {
				x++;
				dp+=(2*x)+1;
			 }
			else
			{
				x++;
				y--;
				dp+=2*(x-y)+1;
			}
			display(x,y);
		}
	}
	void Bresenham()
	{
		int x,y;
		float dp;
		x=0;
		y=r;
		dp=3-2*r;
		glBegin(GL_LINES);
		glVertex2f(xc,yc);
		glVertex2f(xc,yc+r);
		glEnd();
		set(xc,yc);
		while(x<=y)
		{
			if(dp<0)
			{
				dp=dp+(4*x)+6;
			}
			else
			{
				dp=dp+4*(x-y)+10;
				y--;
			}
			x++;
			display(x,y);
		}
	}
	void DDA()
	{
		int x,y;
		float i=0;
		glBegin(GL_LINES);
		glVertex2f(xc,yc);
		glVertex2f(xc,yc+r);
		glEnd();
		set(xc,yc);
		while(i<360)
		{
			x=xc+r*cos(i);
			y=yc+r*sin(i);
			set(x,y);
			i=i+0.5;
		}
	}
void display(int x,int y)
	{
                     set(xc+x,yc+y);
		             set(xc+x,yc-y);
		             set(xc-x,yc+y);
		             set(xc-x,yc-y);
		             set(xc+y,yc+x);
		             set(xc+y,yc-x);
		             set(xc-y,yc+x);
		             set(xc-y,yc-x);
	}
 };

void myInit(void)
 {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.2,0.3,0.4,0.0);
	glColor3f(0.0f,0.0f,1.0f);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-w/2,w/2,-h/2,h/2);
 }

void myDisplay()
 {
	glClearColor(0.9,0.9,0.6,0.8);
	int i;
	for(i=-w;i<=w;i++)
	{
	    if(i%5== 0)
        {
           set(0,i);
		   set(i,0);
        }
	}
    glFlush();
 }

void menu(int item)
 {
    circle *c1;
		switch (item) {
		case 1 :
                c1->DDA();
                break;
		case 2 :
                c1->Bresenham();
                break;
		case 3 :
                c1->Mid_Point();
                    break;
		}
 }
void mouse1(int button,int state,int x,int y)
 {
    int p,q;
	if(state==GLUT_DOWN)
	{
		if(button==GLUT_LEFT_BUTTON)
		{
            xc=x-w/2;
            yc=h/2-y;
            set(xc,yc);
		}
		if(button==GLUT_RIGHT_BUTTON)
		{
			x1=x-w/2;
            zz=h/2-y;
			p=xc-x1;
			q=yc-zz;
			r=sqrt((p*p)+(q*q));
			set(x1,zz);
		}
	}
	glFlush();
 }
int main(int argc, char **argv)
 {
    int x,y,z;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(w,h);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Circle");
    glClearColor(1.0,7.0,4.0,6.0);
	glutDisplayFunc(myDisplay);
    glutMouseFunc(mouse1);
	glutCreateMenu(menu);
	glutAddMenuEntry("1 : DDA",1);
	glutAddMenuEntry("2 : Bresenham",2);
	glutAddMenuEntry("3 : Mid_Point",3);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	myInit();
	glutMainLoop();
	return 0;
 }

