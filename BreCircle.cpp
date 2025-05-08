#include<stdio.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
int xc=320,yc=240;
void plot_point(int x,int y){
	glBegin(GL_POINTS);          // 8-way symmetry 
		glVertex2i(x+xc, y+yc);  
		glVertex2i(-x+xc, y+yc);
		glVertex2i(-x+xc, -y+yc);
		glVertex2i(x+xc, -y+yc);
		glVertex2i(y+xc, x+yc);
		glVertex2i(-y+xc, x+yc);
		glVertex2i(-y+xc, -x+yc);
		glVertex2i(y+xc, -x+yc);
	glEnd();
}
void bresenham_circle(int r){
	int x=0,y=r;
	float s=3-(2*r);     // Decision parameter
	plot_point(x,y);
	int k;
	while(x<=y){
		if(s<=0){
			s=s+(4*x)+6;
			x++;
		}
		else{
			s=s+(4*x)-(4*y)+10;
			x++;
			y=y-1;
		}
		plot_point(x,y);
	}
	glFlush();
}
void concentric_circles(void){
	glClear(GL_COLOR_BUFFER_BIT);  // Clear screen to white
	int radius1=100, radius2=200;
	bresenham_circle(radius1);
	bresenham_circle(radius2);
}
int main(int argc,char**argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("BRESENHAM's CIRCLE");
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glClearColor(1.0,1.0,1.0,0);
	glColor3f(0,0,0);
	gluOrtho2D(0,640,0,480);
	glutDisplayFunc(concentric_circles);
	glutMainLoop();
	
	return 0;
}
