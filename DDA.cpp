#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<iostream>
using namespace std;
float x1,x2,y1,y2;
int ch;
void display(){
	float dx,dy,step,x,y,xin,yin;
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(5);
	glLineWidth(5);
	dx=x2-x1;
	dy=y2-y1;
	if(abs(dx)>abs(dy)){
		step=abs(dx);
	}
	else{
		step=abs(dy);
	}
	xin=dx/step;
	yin=dy/step;
	x=x1;
	y=y1;
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	switch(ch){
		int i;
		case 1: {                  // Dashed Line
				for(i=1;i<=step;i++){
					x=x+xin;
					y=y+yin;
					if(i%6<=8){       // Draw 9 points, skip 1
						glBegin(GL_POINTS);
							glVertex2i(x,y);
						glEnd();
					}
				}
				break;
			}
		case 2: {                  // Dotted Line
				for(i=1;i<=step;i++){
					x=x+xin;
					y=y+yin;
					if(i%8==0){      // Plot every 8th point
						glBegin(GL_POINTS);
							glVertex2i(x,y);
						glEnd();
					}
				}
				break;
			}
		case 3: {         // Center-dotted Line
				for(i=1;i<=step;i++){
					x=x+xin;
					y=y+yin;
					if(i%16<=4){
						glBegin(GL_POINTS);
							glVertex2i(x,y);
						glEnd();
					}
					if(i%8==2){
						glBegin(GL_POINTS);
							glVertex2i(x,y);
						glEnd();
					}
				}
				break;
			}
		case 4: {     // Simple solid line
				for(i=1;i<=step;i++){
					x=x+xin;
					y=y+yin;
					glBegin(GL_POINTS);
						glVertex2i(x,y);
					glEnd();
				}
				
			}
	}
	glBegin(GL_LINES);       // Draw X and Y axes
		glVertex2i(-500,0);
		glVertex2i(500,0);
		glVertex2i(0,-500);
		glVertex2i(0,500);
	glEnd();
	glFlush();
}

int main(int argc,char**argv){
	cout<<"Enter x1 and y1-"<<endl;
	cin>>x1>>y1;
	cout<<"Enter x2 and y2-"<<endl;
	cin>>x2>>y2;
	cout<<"1:Dashed 2:Dotted 3:Center 4:Simple"<<endl;
	cout<<"Enter your choice-"<<endl;
	cin>>ch;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("DDA Algorithm");
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);

	glClearColor(1,1,1,1); //white background
	glColor3f(0,0,0);       // Black drawing color

	gluOrtho2D(-500,500,-500,500);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
