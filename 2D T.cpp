#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<iostream>
using namespace std;
int A[20][3], C[20][3],tx,ty,sx,sy,shx,shy,n;
/*A: Original coordinates of the shape (homogeneous form with [x, y, 1]).
C: Transformed coordinates.
B: 3×3 transformation matrix.
tx, ty: translation values.
sx, sy: scaling factors.
shx, shy: shearing factors.
n: number of vertices.*/
float B[3][3];
void multiply(){
	int i,j,k;
	for(i=0;i<n;i++){
		for(j=0;j<3;j++){
			C[i][j]=0;
			for(k=0;k<3;k++){
				C[i][j]+=A[i][k]*B[k][j];//Performs standard matrix multiplication.
			}
		}
		C[i][2]=1;
	}
	for(i=0;i<n;i++){
		for(j=0;j<3;j++){
			cout<<"\n"<<C[i][j];//Prints the transformed coordinates.
		}
	}
}
void lineDDA(int x1, int y1, int x2, int y2){
	int i,dx,dy,steps;
	float incx,incy,x,y;
	dx=x2-x1;
	dy=y2-y1;
	if(abs(dx)>abs(dy)){
		steps=abs(dx);
	}
	else{
		steps=abs(dy);
	}
	incx=(float)dx/steps;
	incy=(float)dy/steps;
	x=x1;
	y=y1;
	glBegin(GL_POINTS);
		glVertex2f(x,y);
		for(i=1;i<=steps;i++){
			x=x+incx;
			y=y+incy;
			glVertex2f(round(x),round(y));
		}
	glEnd();
}
void unit(){
	int i,j;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(i==j){
				B[i][j]=1;
			}
			else{
				B[i][j]=0;
			}
		}
	}
}
void translation(){
	cout<<"\nEnter the value of tx and ty-\n";
	cin>>tx>>ty;
	unit();
	B[2][0]=tx;
	B[2][1]=ty;
	multiply();
}
void scaling(){
	cout<<"\nEnter the value of sx and sy-\n";
	cin>>sx>>sy;
	unit();
	B[0][0]=sx;
	B[1][1]=sy;
	multiply();
}
void shearing(){                             //shape destortion
	int ch;
	cout<<"\nEnter the choice-\n";
	cout<<"\n1:X-axis\n2:Y-axis\n3:XY-line\n";
	cin>>ch;
	unit();
	if(ch==1){
		cout<<"\nEnter the value shx-\n";
		cin>>shx;
		B[1][0]=shx;
		multiply();
	}
	else{
		if(ch==2){
			cout<<"\nEnter the value shy-\n";
			cin>>shy;
			B[0][1]=shy;
			multiply();
		}
		else{
			if(ch==3){
				cout<<"\nEnter the value shx-\n";
				cin>>shx;
				B[1][0]=shx;
				cout<<"\nEnter the value shy-\n";
				cin>>shy;
				B[0][1]=shy;
				multiply();
			}
			else{
				cout<<"\nWrong Choice!\n";
			}
		}
	}
}
void rotation(){
	float t,ch1;
	cout<<"\nEnter the value of Angle-\n";
	cin>>t;
	float r;
	r=(t*3.14)/180;
	unit();
	cout<<"\n____MENU____\n";
	cout<<"\n1:Clockwise Rotation\n2:Anti-clockwise Rotation\n";
	cout<<"\nEnter your choice-\n";
	cin>>ch1;
	if(ch1==1){
		B[0][0]=B[1][1]=cos(r);
		B[1][0]=sin(r);
		B[0][1]=-sin(r);
		multiply();
	}
	else if(ch1==2){
		B[0][0]=B[1][1]=cos(r);
		B[1][0]=-sin(r);
		B[0][1]=sin(r);
		multiply();
	}
	else{
		cout<<"\nWrong Choice!";
	}
}
void rotation_arbi(){
	float t,ch1;
	int i,j;
	cout<<"\nEnter the value of tx and ty-\n";
	cin>>tx>>ty;
	cout<<"\nEnter the value of angle-\n";
	cin>>t;
	float r;
	r=(t*3.14)/180;
	unit();
	B[0][0]=B[1][1]=cos(r);
	B[1][0]=-sin(r);
	B[0][1]=sin(r);
	B[2][0]=-tx*cos(r)+ty*sin(r)+tx;
	B[2][1]=-tx*sin(r)-ty*cos(r)+ty;
	multiply();
}
void reflection(){
	int ch;
	cout<<"\nEnter choice-\n";
	cout<<"\n1: About X-axis\n2: About Y-axis\n3:About X=Y line\n4:About X=-Y line\n5:About Origin\n";
	cin>>ch;
	unit();
	if(ch==1){
		B[1][1]=-1;
		multiply();
	}
	else if(ch==2){
		B[0][0]=-1;
		multiply();
	}
	else if(ch==3){
		B[0][0]=B[1][1]=0;
		B[0][1]=B[1][0]=1;
		multiply();
	}
	else if(ch==4){
		B[0][0]=B[1][1]=0;
		B[1][0]=-1;
		B[0][1]=-1;
		multiply();
	}
	else if(ch==5){
		B[0][0]=B[1][1]=-1;
		multiply();
	}
	else{
		cout<<"\nWrong Choice!\n";
	}
}
void display(){
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	lineDDA(320,0,320,480);
	lineDDA(0,240,640,240);
	glColor3f(0.0,0.0,1.0);
	for(i=0;i<n-1;i++){
		lineDDA(A[i][0]+320,A[i][1]+240,A[i+1][0]+320,A[i+1][1]+240);
	}
	lineDDA(A[n-1][0]+320,A[n-1][1]+240,A[0][0]+320,A[0][1]+240);
	glColor3f(0.0,1.0,0.0);
	for(i=0;i<n-1;i++){
		lineDDA(C[i][0]+320,C[i][1]+240,C[i+1][0]+320,C[i+1][1]+240);
	}
	lineDDA(C[n-1][0]+320,C[n-1][1]+240,C[0][0]+320,C[0][1]+240);
	glFlush();
}
int main(int argc,char**argv){
	int i,ch;
	cout<<"\n____TRANSFORMATION____\n";
	cout<<"\n1:Translation\n2:Scaling\n3:Shearing\n4:Rotation\n5:Reflection\n6:Rotation about arbitary point\n";
	cout<<"\nEnter your choice-\n";
	cin>>ch;
	cout<<"\nEnter no. of vertices-\n";
	cin>>n;
	for(i=0;i<n;i++){
		cout<<"\nEnter the value of X-"<<i+1<<","<<"Y"<<i+1;
		cin>>A[i][0]>>A[i][1];
		A[i][2]=1;
	}
	switch(ch){
		case 1: translation();
				break;
		case 2: scaling();
				break;
		case 3: shearing();
				break;
		case 4: rotation();
				break;
		case 5: reflection();
				break;
		case 6: rotation_arbi();
				break;
		default: cout<<"\nWrong Choice!";
	}
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("TRANSFORMATION");
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glClearColor(1.0,1.0,1.0,0.0);
	gluOrtho2D(0,640,0,480);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}



