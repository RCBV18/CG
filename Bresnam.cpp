#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<iostream>
using namespace std;
int x1,x2,y1,y2;
int ch;
int sign(int a){
	if(a>0){
		return 1;
	}
	else if(a<0){
		return(-1);
	}
	else{
		return 0;
	}
}
void display(){
	int dx,dy,step,x,y,G,S1,S2;
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2);
	glLineWidth(5);
	dx=abs(x2-x1);
	dy=abs(y2-y1);
	if((dx)>(dy)){
		step=(dx);
	}
	else{
		step=(dy);
	}
	S1=sign(x2-x1);
	S2=sign(y2-y1);
	G=(2*dy)-dx;      //Decision parameter e
	x=x1;
	y=y1;
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	switch(ch){
		int i;
		case 1: {         //Dashed 
			for(i=1;i<=step;i++){
				while(G>=0){
					y=y+S2;
					G=G-(2*dx);
				}
				x=x+S1;
				G=G+(2*dy);
				if(i%16<=8){     // Draw a segment, then skip
					glBegin(GL_POINTS);
						glVertex2i(x,y);
					glEnd();
				}
				break;
			}
			}    
			
		
		case 2: {        //Dotted
				for(i=1;i<=step;i++){
					while(G>=0){
						y=y+S2;
						G=G-(2*dx);
					}
					x=x+S1;
					G=G+(2*dy);
					if(i%8==0){       // Plot every 8th point
						glBegin(GL_POINTS);
							glVertex2i(x,y);
						glEnd();
					}
				}
				break;
			}
		case 3: {    //Center Line
				for(i=1;i<=step;i++){
					while(G>=0){
						y=y+S2;
						G=G-(2*dx);
					}
					x=x+S1;
					G=G+(2*dy);
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
		
	}
	glBegin(GL_LINES);   //Draws X and Y axes
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
	glutCreateWindow("BRESENHAM's Algorithm");
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glClearColor(1,1,1,1);
	glColor3f(0,0,0);
	gluOrtho2D(-500,500,-500,500);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
