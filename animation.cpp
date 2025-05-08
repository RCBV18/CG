#include<GL/glut.h>

#define ESCAPE 27 //Define ASCII value of ESC key for exit
int window;
float rtri = 0.0f;//rtri will be used to move the triangle (car body) left to right.

void InitGL(int Width,int Height)
{
	glClearColor(0.0f,0.0f,0.0f,0.0f);//set window bgcolor black
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
}
float ballX=-0.5f;// define the starting position of the first bal
float ballY=0.0f;
float ballZ=0.0f;
void drawBall(void)
{
	glColor3f(1.0,0.0,1.0);//set the ball color
	glTranslatef(ballX,ballY,ballZ);// Move to ball1 position
	glRotatef(ballX,ballX,ballY,ballZ);// Rotate
	glutSolidSphere(0.3,50,50); // Draw first ball
	glTranslatef(ballX+1.5,ballY,ballZ); // Move to second ball's position
	glutSolidSphere(0.3,50,50); // Draw second ball
}
void DrawGLScene()
{
	
	glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity();
	glTranslatef(rtri,0.0f,-6.0f);
	glBegin(GL_POLYGON);// Draw triangle as car body
	glColor3f(1.0f,0.0f,0.0f);//set triangle color red
	glVertex3f(-1.0f,1.0f,0.0);
	glVertex3f(0.4f,1.0f,0.0f);
	glVertex3f(1.0f,0.4f,0.0f);
	
	glEnd();

	drawBall(); // Draw the two wheels
	rtri+=0.005f; // Move car right slowly
	if(rtri>2)
	{
		rtri=-2.0f;   // If it goes too far right, reset to left
	}
	
	glutSwapBuffers();
}
void keyPressed(unsigned char key,int x,int y)
{
	if(key==ESCAPE)
	{
		glutDestroyWindow(window);
		exit(0);
	}
}
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(0,0);
	window=glutCreateWindow("Moving Car");
	glutDisplayFunc(DrawGLScene);
	glutIdleFunc(DrawGLScene);
	glutKeyboardFunc(keyPressed);
	InitGL(640,480);
	glutMainLoop();
	return(0);	
}


































