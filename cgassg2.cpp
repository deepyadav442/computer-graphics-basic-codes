#include<iostream>
using namespace std;
#include<GL/glut.h>
#include<math.h>
#include<stdlib.h>
#define w 500
#define h 500
GLint x1,x2,yi,y2,r,xc,yc;
GLfloat a1,b1,c1;
int ch;
void set(GLint x,GLint y)
{
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
	glFlush();
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
void mydisp(void)
{
	int i;
	glColor3f(1.0,0.0,1.0);
	for(i=0;i<=w/2;i++)
	{
		if(i%5==0)
		{
			set(i,0);
			set(-i,0);
			set(0,i);
			set(0,-i);
		}
	}
}

class circle
{
public:
	void midpoint()
	{
		GLint x,y;
		GLfloat dp;
		x=0;
		y=r;
		dp=1-r;
		glColor3f(0.0,1.0,0.0);
		set(xc,yc);
		while(x<=y)
		{
			if(dp<0)
			{
				x++;
				dp+=2*x+1;
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
	void dda()
	{
		glColor3f(1.0,0.0,0.0);
		int x,y;
				float i=0;
				//glBegin(GL_POINTS);
				//glVertex2f(xc,yc);
				//glVertex2f(xc,yc+r);
				//glEnd();
				set(xc,yc);
				while(i<360)
				{
					x=xc+r*cos(i);
					y=yc+r*sin(i);
					set(x,y);
					i=i+0.5;
				}
	}
	void bres()
	{
		int x,y;
		float dp;
		x=0;
		y=r;
		dp=3-2*r;
		glColor3f(0.0,0.0,1.0);
		set(xc,yc);
		while(x<=y)
		{
			if(dp<0)
			{
				dp+=(4*x)+6;
			}
			else
			{
				dp+=4*(x-y)+10;
				y--;
			}
			x++;
			display(x,y);
		}
	}
};
void olympics(int xc,int yc,int x1,int yi)
{
	int p,q;
	circle *d;
	p=xc-x1;q=yc-yi;
	r=sqrt((p*p)+(q*q));
	if(ch==1)
	d->dda();
	if (ch==2)
	d->midpoint();
	if(ch==3)
	d->bres();
}
void myInit()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-w/2,w/2,-h/2,h/2);
}
void menu(GLint x)
{
	circle *c;
	switch(x)
	{
		case 1:c->dda();
		break;
		case 2:c->bres();
		break;
		case 3:c->midpoint();
		break;
		case 4:ch=1;
			xc=-100;yc=0;set(xc,yc);
			x1=-100;yi=40;
			olympics(xc,yc,x1,yi);
			ch=2;
			xc=0;yc=0;set(xc,yc);
			x1=0;yi=40;
			olympics(xc,yc,x1,yi);
			ch=3;
			xc=100;yc=0;set(xc,yc);
			x1=100;yi=40;
			olympics(xc,yc,x1,yi);
			ch=3;
			xc=-70;yc=-30;set(xc,yc);
			x1=-70;yi=10;
			olympics(xc,yc,x1,yi);
			ch=1;
			xc=70;yc=-30;set(xc,yc);
			x1=70;yi=10;
			olympics(xc,yc,x1,yi);
			break;
		case 5:glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.0,0.0,0.0,1.0);
			mydisp();
			break;
	}
}

void mouse1(GLint button,GLint state,GLint x,GLint y)
{
	int p,q;
	if(state==GLUT_DOWN)
	{
		if(button==GLUT_LEFT_BUTTON)
		{
			xc=x-w/2;
			yc=h/2-y;
			glColor3f(1.0,1.0,1.0);
			set(xc,yc);
		}
		if(button==GLUT_RIGHT_BUTTON)
		{
			x1=x-w/2;
			yi=h/2-y;
			p=xc-x1;
			q=yc-yi;
			r=sqrt((p*p)+(q*q));
			glColor3f(1.0,1.0,1.0);
			set(x1,yi);
		}
	}
}
int main(int argc,char**argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(w,h);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Circle");
    glutDisplayFunc(mydisp);
    myInit();
	glutMouseFunc(mouse1);
	glutCreateMenu(menu);
	glutAddMenuEntry("1 : DDA(red)",1);
	glutAddMenuEntry("2 : Bresenham(green)",2);
	glutAddMenuEntry("3 : Mid_Point(blue)",3);
	glutAddMenuEntry("4 : Olympic Circle",4);
	glutAddMenuEntry("5 : Clear",5);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutMainLoop();
	return 0;
}
