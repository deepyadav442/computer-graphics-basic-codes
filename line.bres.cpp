#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
using namespace std;
GLint count=-1,x1,y1,x2,y2;
int round(GLfloat a)
{
    return GLint(a+0.5);
}
void myInit(void)
{
	glClearColor(0.6,0.6,0.6,0.0);
	glColor3f(1.0f,0.0f,0.0f);
	glPointSize(10.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-400.0,400.0,-300.0,300.0);
}
void BRES()
{
    GLint i,step,p,x,y,temp;
    GLfloat slop,dx,dy;
	glColor3f(1.0f,0.0f,0.0f);
	glPointSize(5.0);
    if(x1>x2)
    {
    	temp=x1;
    	x1=x2;
    	x2=temp;
    	temp=y1;
    	y1=y2;
    	y2=temp;

    }

    glBegin(GL_POINTS);
    glVertex2f(x1,y1);
    glEnd();
    glFlush();

     dx=x2-x1;
     dy=y2-y1;
      if(dx==0 && dy>0)
    	  slop=10;
      else
      if(dx==0 && dy<0)
       	  slop=-10;
      else
    	 slop=(dy/dx);

  if(slop>=0 && slop<1)
   { p=2*dy-dx;
     step=dx;

        x=x1;
        y=y1;
   for(i=0;i<step;i++)
   {      if(p<0)
	        p=p+2*dy;
          else
          {
        	  p=p+2*dy-2*dx;
        	  y++;
          }
	     x++;
	        glBegin(GL_POINTS);
	        glVertex2f(x,y);
	        glEnd();
	        glFlush();
	    }
   }
  else
  {
   if(slop>=1)
	   {    p=2*dx-dy;
		     step=dy;

		        x=x1;
		        y=y1;
		   for(i=0;i<step;i++)
		   {      if(p<0)
			        p=p+2*dx;
		          else
		          {
		        	  p=p+2*dx-2*dy;
		        	  x++;
		          }
			     y++;
			        glBegin(GL_POINTS);
			        glVertex2f(x,y);
			        glEnd();
			        glFlush();
			}

	   }
   else
   {
	   if(-1<=slop && slop<=0)
	   {   p= 2*dy-dx;
		     step=dx;

		        x=x1;
		        y=y1;
		   for(i=0;i<step;i++)
		   {      if(p<0)
			        p=p-2*dy;
		          else
		          {
		        	  p=p-2*dx-2*dy;
		        	  y--;
		          }
			     x++;
			        glBegin(GL_POINTS);
			        glVertex2f(x,y);
			        glEnd();
			        glFlush();
			}


	   }
	   else{
		     if(slop<-1)
		     {
                     p= 2*dy-dx;
				     step=-dy;

				        x=x1;
				        y=y1;
				   for(i=0;i<step;i++)
				   {      if(p<0)
					        p=p+2*dx;
				          else
				          {
				        	  p=p+2*dy+2*dx;
				        	  x++;
				          }
					     y--;
					        glBegin(GL_POINTS);
					        glVertex2f(x,y);
					        glEnd();
					        glFlush();
					}



		        }

	        }
   }
	   }

    return;
}
void DDA()
{
    GLint i,step;
    GLfloat dx,x,y,dy,dx1,dy1,xinc,yinc;
	glColor3f(0.0f,0.0f,1.0f);
	glPointSize(3.0);
     dx=x2-x1;
     dy=y2-y1;
     if(dx<=0)
	    dx1= -dx;
     else
    	 dx1=dx;
    if(dy<=0)
         dy1= -dy;
    else
    	dy1=dy;
   if(dx1>dy1)
	   step=dx1;
   else
	   step=dy1;
   if(step<0)
	   step=(-step);


   xinc=(dx/step);
   yinc=(dy/step);

      glBegin(GL_POINTS);
      glVertex2f(x1,y1);
      glEnd();
      glFlush();
        x=x1;
        y=y1;
   for(i=0;i<step;i++)
   {  x=x+xinc;
      y=y+yinc;
	        glBegin(GL_POINTS);
	        glVertex2f(round(x),round(y));
	        glEnd();
	        glFlush();
	}

    return;
}
void processMenuEvents(GLint opt)
{
  switch(opt)
  {
  case 1:DDA(); break;
  case 2 : BRES(); break;
  default : exit(0);
  }


}
void myMouse(int button,int state,int x,int y)
{
    if(state==GLUT_DOWN)
    {
    	if(button==GLUT_LEFT_BUTTON)
    	{if(count==-1)
    	{
    		x1=-400,y1=0,x2=400,y2=0;
    		DDA();
    		x1=0,y1=-300,x2=0,y2=300;
    		DDA();
    		count++;
    	}
    	else
    	  if(count==0)
           {
        	   x1=x-400;
        	   y1=300-y;
              count++;
           }
           else
            if(count==1)
            {
            	x2=x-400;
            	y2=300-y;
            	count++;
            }
           if(count==2)
           {
               glBegin(GL_POINTS);
            		 glVertex2f(x1,y1);
            		 glVertex2f(x2,y2);
            	 glEnd();
            	 glFlush();
        	   count=0;
           }
    	}
    	else
    	{   glClear(GL_COLOR_BUFFER_BIT);
    		glClearColor(0.6,0.6,0.6,0.0);
    		glColor3f(1.0f,0.0f,0.0f);
    		glFlush();
    		count=-1;
    	}

    }

	return;
}
void mydisp(void)
{

}
int main(int argc, char **argv)
{

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(0,0);
	glutCreateWindow("My First Program");

	glutDisplayFunc(mydisp);
	glutMouseFunc(myMouse);
	myInit();
    glutCreateMenu(processMenuEvents);
     glutAddMenuEntry("DDA algorithm(blue)",1);
     glutAddMenuEntry("BRES algorithm(red)",2);
     glutAddMenuEntry("EXIT",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}
