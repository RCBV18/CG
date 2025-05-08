#include<GL/glut.h>
#include<math.h>
GLfloat oldx=-0.5,oldy=0.5;
void drawkoch(GLfloat dir,GLfloat len,int iter)
{
	GLdouble dirRad=0.0174533*dir;   //Converts angle direction from degrees to radians,
	GLfloat newX=oldx+len*cos(dirRad); //Calculates the next point
	float newY=oldy+len*sin(dirRad);
	if(iter==0)
		{
			glVertex2f(oldx,oldy);
			glVertex2f(newX,newY);
			oldx=newX;
			oldy=newY;
		}
	else
	{
		iter--;
		drawkoch(dir,len,iter);   //Breaks the line into 4 parts as per the Koch Curve rules
		dir+=60.0;
		drawkoch(dir,len,iter);  //Turn left 60° and go forward
		dir-=120.0;
		drawkoch(dir,len,iter);  //Turn right 120° and go forward
		dir+=60.0;
		drawkoch(dir,len,iter);  //Turn left 60° and go forward.
	}
}
void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glColor3f(0.0,1.0,0.0);  //Set line color to green
	drawkoch(0.0,0.05,3);
	drawkoch(-120.0,0.05,3);  // Left side (rotated -120°
	drawkoch(120.0,0.05,3);   //Right side (rotated +120°)
	glEnd();
	glFlush();
}
int main(int argc,char**argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("koch snowflake-marcus young");
	glutDisplayFunc(mydisplay);
	glutMainLoop();
}





//Bezier
#include<stdio.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

void init(){
	glClearColor(1, 0, 0, 0); //Background COlor:red
	glColor3f(0, 0, 1); //Foreground COlor:blue
	gluOrtho2D(0, 640, 0, 480);
}

void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	int x[4], y[4], px, py, i;//arrays to hold the 4 control points (x0,y0) to (x3,y3) and (px, py) is used to store calculated curve points
	for(i = 0; i<4; i++){
		x[0] = 320;
		x[1] = 400;
		x[2] = 480;
		x[3] = 560;
		y[0] = 240;
		y[1] = 100;
		y[2] = 380;
		y[3] = 240;
		glBegin(GL_LINES);
		glVertex2i(320, 0); //Vertical center line
		glVertex2i(320, 480);
		glVertex2i(0, 240);//Horizontal center line
		glVertex2i(640, 240);
		glEnd();
	}
	double t;  //t is a parameter that ranges from 0 to 1
	for(t = 0.0; t<=1; t+= 0.001){
		px = (1-t)*(1-t)*(1-t)*x[0] + 3*t*(1-t)*(1-t)*x[1]+3*t*t*(1-t)*x[2]+t*t*t*x[3];  //bezier formula for x
		py = (1-t)*(1-t)*(1-t)*y[0] + 3*t*(1-t)*(1-t)*y[1]+3*t*t*(1-t)*y[2]+t*t*t*y[3];  //bezier formula for y
		glBegin(GL_POINTS);
		glVertex2i(px, py);
		glEnd();
		//delay(2);
	}
	glFlush();
}
int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640, 480);

	glutCreateWindow("Mezier Curve");
	
	init();
	
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}
