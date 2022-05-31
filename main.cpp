#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <string.h> 

using namespace std;

static int day= 0;
GLfloat t=1.0f;  
GLfloat t1=0.0f,t2=0.0f,t3=0.0f;
GLfloat windowWidth;
GLfloat windowHeight;
GLfloat xstep=0.1f; 
GLfloat ystep=0.1f; 
// thuoc tinh cho nguon sang chieu vao qua bong
GLfloat light_ambientball[]={0.0,1.0,1.0,1.0};
GLfloat light_diffuseball[]={0.0,1.0,1.0,1.0};
// thuoc tinh cho nguon sang chieu vao thanh truot
GLfloat light_ambientThanh[]={1.0,0.5,1.0,1.0};
GLfloat light_diffuseThanh[]={1.0,0.5,1.0,1.0}; 

//khai bao ham
void welcomeDisplay();
void endDisplay();
//khai bao bien ham mytime


void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //Ve mat phang
	glPushMatrix();
		glColor3f(0.0,1.0,0.0);
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambientThanh);
 		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuseThanh);
		glScalef(5,1,5);
		glTranslatef((GLfloat) day/5 , -5, 0);	
		glutSolidCube(1.0);
	glPopMatrix();
//  ve qua bong
	glPushMatrix();
		glColor3f (1.0, 0.5, 0.0);
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambientball);
 		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuseball);
		glTranslatef(t1,t2,t3); 
		glutSolidSphere(1.0,30.0,30.0); 
	glPopMatrix(); 
	
	glutSwapBuffers();
}

// xu ly bong
void TimerFunctionForObject(int value)
    { 
    	t1+=xstep;
		t2+=ystep;
		// bat dieu kien de bong di chuyen
		if(t1>=10 || t1<=-10)
			 xstep=-xstep;
		if(t2>=5 )
			ystep=-ystep;  
		if(t2<=-3.5 ){
			if(t1> (GLfloat) day-2.5 && t1< (GLfloat) day+2.5 ){// bat dieu kien de bong cham vao thanh truot se bat len
				ystep=-ystep; 
				t2=-3.5;
			}
		}
		
		// bat dieu kien cho game ket thuc
		if( t2<-3.5){
			glutDisplayFunc(endDisplay); 
//			exit(0);
			
			
		}
		  
    glutPostRedisplay();
    glutTimerFunc(30,TimerFunctionForObject, 1);
}




// Setup the rendering state
void SetupRC(void)
    {
    // Set clear color to blue
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    }

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(80.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (0, 1, 10, 0.0, 0.0, 0.0, 0, 1, 0);
}

void limitLeft() {
	if(day <= -10)
		day = -10;
}

void limitRight() {
	if(day >= 10)
		day = 10;
}

void moveLeft() {
	day = (day - 1); // di chuyen
	limitLeft();
}

void moveRight() {
	day = (day + 1); // di chuyen
	limitRight();
}


void keyboard (int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_LEFT: // (>)
			moveLeft();
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT: // (<)
			moveRight();
			glutPostRedisplay();
			break;
		default:
			break;
	}
	if(key=='z') {
		glutDisplayFunc(display);
		glutPostRedisplay();
	}
//	if(key=='y') {
//		glutDisplayFunc(welcomeDisplay);
//	}
//	glutPostRedisplay();
}

void myTime(int val){
	 if(val==0) 
	 {
	 	glutDisplayFunc(display);
	 	glutTimerFunc(50,TimerFunctionForObject, 1);
	 }
	else if (val==1)
	{
		glutDisplayFunc(welcomeDisplay); 
		glutTimerFunc(50, myTime, 1);
	 } 
	glutPostRedisplay();
	
} 

void init(void) 
{
	GLfloat mat_specular[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glClearColor (1.0, 1.0, 1.0, 1.0);
 
	glShadeModel (GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	 
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel (GL_FLAT);
}

void welcomeDisplay() {
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0,0.0,0);
	glRasterPos3f(-0.8,1.5,0);
	char msg[] ="GAME START!!!";
	for(int i=0;i<strlen(msg);i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg[i]); 
	}
	
	glRasterPos3f(-0.8,-1.5,0);
	char msg1[] ="WELCOME BAll";
	for(int i=0;i<strlen(msg1);i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg1[i]); 
	}
	glutSwapBuffers();
}

void endDisplay() {
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0,0.0,0);
	glRasterPos3f(-0.8,1.5,0);
	char msg[] ="GAME OVER!!!";
	for(int i=0;i<strlen(msg);i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg[i]); 
	}
	
	glRasterPos3f(-0.8,-1.5,0);
	char msg1[] ="GOODBYE BAll";
	for(int i=0;i<strlen(msg1);i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg1[i]); 
	}
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (1000, 1000);
	 
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Game");
	init ();
	glutDisplayFunc(welcomeDisplay); 
	glutReshapeFunc(reshape);
	glutSpecialFunc(keyboard);
	glutTimerFunc(500, myTime, 0);
	glutMainLoop();
	return 0;
}
