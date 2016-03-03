/*line clipping using cohen-sutherland algorithm
 *
 */

#include<iostream>
using namespace std;
#include<GL/glut.h>
#include<math.h>
#define w 500
#define h 500
#define max 20
int win[4][2],k=0,flag=0,m=0,n=0,flag1=0,wino[4][2];
int xmin,ymin,xmax,ymax;

class edge	//edge is used to represent the abrl outcode for the end points of the line
{
      public:
      int xc,yc;
      int code[4];
};
 edge e[max];	//GLOBAL object of the class e (edge)
void setpixel(GLint x, GLint y)	//used to display the pixel
{
	glColor3f(1.0,0.0,0.0);	//used to set the color of the pixel which is going to be displayed
	glPointSize(2.0);	//to set the size of the pixel
	glBegin (GL_POINTS);	//use to display the points under this according to the parameter condition passed to it
		glVertex2f(x,y);	//to display the vertex whose coordinates are passed to it
	glEnd();
	glFlush();	//used to flush the contents of the buffer on the screen
}

class clipping
{
      public:
      int check_zero(edge e)	//to check whether the point lies inside the window or not
      {
            if(e.code[0]==0&&e.code[1]==0&&e.code[2]==0&&e.code[3]==0)	//to check the abrl outcode
                 return 1;	//IF THE POINT IS INSIDE THE WINDOW
            else
                 return 0;	//IF THE POINT IS OUTSIDE THE WINDOW
      }
      edge outcode(edge ed)	//IS USED TO GET THE OUTCODE OF THE END POINT ed OF THE LINE
      {

            if(win[0][0]<win[2][0])
            {
                 xmin=win[0][0];
                 xmax=win[2][0];
            }
            else
            {
                 xmin=win[2][0];
                 xmax=win[0][0];
            }
            if(win[0][1]<win[2][1])
            {
                 ymin=win[0][1];
                 ymax=win[2][1];
            }
            else
            {
                 ymin=win[2][1];
                 ymax=win[0][1];
            }
            cout<<"\nxmin:"<<xmin;
             cout<<"\nymin:"<<ymin;
              cout<<"\nxmax:"<<xmax;
               cout<<"\nymax:"<<ymax;

          if(ed.xc<xmin)	//TO CHECK IF THE POINT IS ON THE LEFT SIDE OF THE WINDOW
                       ed.code[0]=1;
          else
                       ed.code[0]=0;
          if(ed.xc>xmax)	//TO CHECK IF THE POINT IS ON THE RIGHT SIDE OF THE WINDOW
                       ed.code[1]=1;
          else
                       ed.code[1]=0;
          if(ed.yc<ymin)	//TO CHECK IF THE POINT IS BELOW THE WINDOW
                      ed.code[2]=1;
          else
                       ed.code[2]=0;
          if(ed.yc>ymax)	//TO CHECK IF THE POINT IS ABOVE THE WINDOW
                       ed.code[3]=1;
          else
                       ed.code[3]=0;
                       cout<<"\n";
            for(int j=3;j>=0;j--)
                                {
                                cout<<ed.code[j];	//TO DISPLAY THE OUTCODE  OF THE END POINT OF THE LINE
                                }
          return ed;
       }

       int ad_check(int ad[])	//TO CHECK IF ATLEAST ONE BIT OF THE OUTCODE ABRL IS 1(IT IS OUTSIDE THE WINDOW OR NOT)
       {
            if(ad[0]!=0||ad[2]!=0||ad[1]!=0||ad[3]!=0)
           {
             return 0;

           }
           else return 1;

       }

      void hand(edge e, edge e1,int ad[4])	//IT IS USED FOR LOGICAL AND OPERATION
      {
           for(int i=0;i<4;i++)
           {
                   if(e.code[i]==1 && e1.code[i]==1)
                   {
                     ad[i]=1;
                   }
                   else
                       ad[i]=0;
           }
      }

      void cohen_suth()
      {
           int ad[4],y0,x0,flag=0;
           float m;

           for(int i=0;i<n;i+=2)
           {
                   do
                   {
                            flag=0;

                       if(check_zero(e[i])&&check_zero(e[i+1]))
                       {
                          break;
                       }
                       else
                       {
                           hand(e[i],e[i+1],ad);
                           if(!ad_check(ad))
                           {
                             e[i].yc =900;
                             e[i+1].yc =900;
                             break;
                           }
                           else
                           {
                               m=(float)(e[i+1].yc-e[i].yc)/(e[i+1].xc-e[i].xc);
                               if(e[i].code[0]==1&&e[i+1].code[0]==0)
                               {
                                 e[i].yc +=(int)(m*(xmin-e[i].xc));
                                 cout<<"\ny coordinate is:"<<e[i].yc;
                                 e[i].xc=xmin;
                                  cout<<"\nx coordinate is:"<<e[i].xc;
                                 e[i]=outcode(e[i]);
                                 flag=1;
                               }
                               else if(e[i+1].code[0]==1&&e[i].code[0]==0)
                               {
                                    e[i+1].yc +=(int)(m*(xmin-e[i+1].xc));
                                    e[i+1].xc=xmin;
                                    e[i+1]=outcode(e[i+1]);
                                    flag=1;
                               }
                               if(e[i].code[1]==1&&e[i+1].code[1]==0&&flag==0)
                               {
                                 e[i].yc +=(int)(m*(xmax-e[i].xc));
                                 e[i].xc=xmax;
                                 e[i]=outcode(e[i]);
                                 flag=1;
                               }
                               else if(e[i+1].code[1]==1&&e[i].code[1]==0&&flag==0)
                               {
                                    e[i+1].yc +=(int)(m*(xmax-e[i+1].xc));
                                    e[i+1].xc=xmax;
                                    e[i+1]=outcode(e[i+1]);
                                    flag=1;
                               }
                               if(e[i].code[2]==1&&e[i+1].code[2]==0&&flag==0)
                               {
                                 e[i].xc +=(int)((ymin-e[i].yc)/m);
                                 e[i].yc=ymin;
                                 e[i]=outcode(e[i]);
                                 flag=1;
                               }
                               else if(e[i+1].code[2]==1&&e[i].code[2]==0&&flag==0)
                               {
                                    e[i+1].xc +=(int)((ymin-e[i+1].yc)/m);
                                    e[i+1].yc=ymin;
                                    e[i+1]=outcode(e[i+1]);
                                    flag=1;
                               }
                               if(e[i].code[3]==1&&e[i+1].code[3]==0&&flag==0)
                               {
                                 e[i].xc +=(int)((ymax-e[i].yc)/m);
                                 e[i].yc=ymax;
                                 e[i]=outcode(e[i]);
                                 flag=1;
                               }
                               else if(e[i+1].code[3]==1&&e[i].code[3]==0&&flag==0)
                               {
                                    e[i+1].xc +=(int)((ymax-e[i+1].yc)/m);
                                    e[i+1].yc=ymax;
                                    e[i+1]=outcode(e[i+1]);
                                    flag=1;
                               }


                           }
                       }
                   }while(ad_check(ad));

                   e[i].yc -=250;
                   e[i+1].yc -=250;
                   glColor3f(0.0,1.0,0.0);
                   glBegin(GL_LINES);
                   glVertex2i(e[i].xc,e[i].yc);
                   glVertex2i(e[i+1].xc,e[i+1].yc);
                   glEnd();
           }


       }

};

void mydisplay (void)
{
     int i,ch;
	glColor3f(1.0,0.0,0.0);
	glPointSize(4.0);
	glFlush();
	for(i=-w;i<=w;i++)
	{
	//	setpixel(i,0);
	}
}
void init()
{

     glClear(GL_COLOR_BUFFER_BIT);
     glClearColor(0.0,1.0,0.0,0.0);
     glColor3f(0.0f,1.0f,0.0f);
     glPointSize(2.0);
     glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 gluOrtho2D(-w/2,w/2,-h/2,h/2);
	 glFlush();

}

void draw_window()
{
            win[1][0]=win[0][0];
            win[1][1]=win[2][1];
            win[3][0]=win[2][0];
            win[3][1]=win[0][1];


            glColor3f(0.0f,0.0f,1.0f);
            glBegin(GL_LINE_LOOP);
            for(int i=0;i<4;i++)
			  glVertex2f(win[i][0],win[i][1]);
			glEnd();
			glFlush();
 }
 void draw_winoutput()
 {
            wino[0][0]=win[0][0];
            wino[1][0]=win[1][0];
            wino[2][0]=win[2][0];
            wino[3][0]=win[3][0];
            wino[0][1]=win[0][1]-250;
            wino[1][1]=win[1][1]-250;
            wino[2][1]=win[2][1]-250;
            wino[3][1]=win[3][1]-250;
            glColor3f(1.0f,0.0f,0.0f);
            glBegin(GL_LINE_LOOP);
            for(int i=0;i<4;i++)
			  glVertex2f(wino[i][0],wino[i][1]);
			glEnd();
			glFlush();
}

void keyboard (unsigned char key, int x, int y)
{
     if (key == 27)
        exit (0);
     else
         cout<<"You pressed %c\n"<< key;
}


void menu(int item)
{ /* Callback called when the user clicks the middle mouse button */
    clipping c;
    cout<<"menu: you clicked item:\t" <<item;
    if(item==1)
    {
          draw_winoutput();
          c.cohen_suth();

    }
    if(item==2)
               exit(0);
}


void mouseClick(int button, int state, int x, int y)
{

   clipping c;
   if(state== GLUT_DOWN)
	{

		if(button==GLUT_LEFT_BUTTON)
		{
            if(flag==1)
            {
                       	e[m].xc=(x-250);
			            e[m].yc=(250-y);
                        e[m]=c.outcode(e[m]);
                        cout<<"\nxc : "<<e[m].xc;
                        cout<<"\nyc : "<<e[m].yc;
			            glBegin(GL_POINTS);
		                	glVertex2f(e[m].xc,e[m].yc);
	                     glEnd();
	                     m++;
	                 	glFlush();
	                 	flag1=1;
            }
            else
            {
			win[k][0]=(x-250);
			win[k][1]=(250-y);
			glColor3f(1,0,0);
			glBegin(GL_POINTS);
			glVertex2f(win[k][0],win[k][1]);
			glEnd();
			k=k+2;
			glFlush();
           }
		}
		if(button==GLUT_RIGHT_BUTTON)
		{
                                     flag=1;
            if(flag1==1)
            {
                         glColor3f(1.0f,0.0f,0.0f);
                         glBegin(GL_LINES);

			             glVertex2f(e[n].xc,e[n].yc);
			             n++;
			             glVertex2f(e[n].xc,e[n].yc);

			             glEnd();
			             glFlush();
			             n++;
            }
            else
            {
            			draw_window();
            }
        }
    }
}

int main(int argc, char **argv)
{
    glutInit (&argc, argv); //initialise the device(glut window)
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);//initialise the display mode (single,double or multiple)
    glutInitWindowSize(w,h);
    glutCreateWindow (": LINE Clipping :");

    glutDisplayFunc (mydisplay); //call backs are function pointers
    init();
    glutKeyboardFunc (keyboard);	//USED TO REGISTER THE CALL BACK FUNCTION FOR  KEYBOARD
    glutMouseFunc(mouseClick);	//USED TO REGISTER THE CALL BACK FUNCTION FOR MOUSE

    glutCreateMenu (menu); /* Create the first menu & add items */
    	glutAddMenuEntry ("Line clipping", 1);
    	glutAddMenuEntry ("Exit", 2);

    glutAttachMenu (GLUT_MIDDLE_BUTTON); //attach menu to middle button of mouse

    glutMainLoop();	//TO DISPLAY THE OUTPUT DISPLAY WINDOW UNTIL AND UNLESS THE USER EXPLICITLY CLOSES IT
    return 0;
}

