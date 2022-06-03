#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <ctime>

#define LIMITED_MOVE 8
#define LIMITED_Y_COORDINATE 5

#define WIDTH_WINDOW 500
#define HEIGHT_WINDOW 500
#define TITLE_GAME "Bouncing Ball Game"

#define IS_START_GAME 0
#define IS_PLAY_GAME 1
#define IS_STOP_GAME 2


using namespace std;

// Set up for circle
GLfloat x = 1.0f;  
GLfloat x1 = 0.0f, x2 = 0.0f, x3 = 0.0f;
GLfloat xstep = 0.1f; 
GLfloat ystep = 0.1f; 

// Set up for bar
int distanceMoveBar = 0;
int barScaleX = 5;
int barScaleY = 1;
int barScaleZ = 5;

// Window
GLfloat windowWidth;
GLfloat windowHeight;

// Set up for light ball 3D
GLfloat light_ambient_ball[] = {0.0,1.0,1.0,1.0};
GLfloat light_diffuse_ball[] = {0.0,1.0,1.0,1.0};
// Set up for light bar 3D
GLfloat light_ambient_bar[] = {1.0,0.5,1.0,1.0};
GLfloat light_diffuse_bar[] = {1.0,0.5,1.0,1.0}; 

int user_control = IS_START_GAME;
int score = 0;

void reset(){
	x = 1.0f;
	x1 = 0.0f;
	x2 = 0.0f;
	x3 = 0.0f;
	
	xstep=0.1f;
	ystep=0.1f;
	score = 0;
	distanceMoveBar = 0;
}

void welcomeDisplay() {
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0,0.0,0);
	glRasterPos3f(0,1.5,0);
	char msg[] ="GAME START!!!";
	for(int i=0;i<strlen(msg);i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg[i]); 
	}

	glRasterPos3f(0,0,0);
	char msg1[] ="WELCOME BAll";
	for(int i=0;i<strlen(msg1);i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg1[i]); 
	}
	glColor3f(1.0,0.0,1.0);
	glRasterPos3f(0,-1.5,0);
	char msg2[] ="PRESS: p to play.";
	for(int i=0;i<strlen(msg2);i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg2[i]); 
	}
	char msg3[] ="PRESS: s to start.";
	for(int i=0;i<strlen(msg3);i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg3[i]); 
	}
	char msg4[] ="PRESS: e to end.";
	for(int i=0;i<strlen(msg4);i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg4[i]); 
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

	string result;          
	ostringstream convert;
	convert << score;      
	result = "Your score is " + convert.str() +" ^^";

	glColor3f(1.0,0.0,0);
	glRasterPos3f(-0.8,-1.5,0);
	for(int i=0;i<result.length();i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,result[i]); 
	}

	glRasterPos3f(-0.8,-3,0);
	char msg1[] ="GOODBYE BAll";
	for(int i=0;i<strlen(msg1);i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg1[i]); 
	}
	glutSwapBuffers();
}

void display(void)
{
	if(user_control == IS_PLAY_GAME) {
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//  Draw and shading for ball
		glPushMatrix();
			glColor3f(0.0,1.0,0.0);
			
			glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient_ball);
	 		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse_ball);
	 		
			glScalef(barScaleX, barScaleY, barScaleZ);
			glTranslatef((GLfloat) distanceMoveBar/5 , -5, 0);
				
			glutSolidCube(1.0);
		glPopMatrix();
		
	//  Draw and shading for bar
		glPushMatrix();
			glColor3f (1.0, 0.5, 0.0);
			
			glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient_bar);
	 		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse_bar);
	 		
			glTranslatef(x1, x2, x3);
			
			glutSolidSphere(1.0, 30.0, 30.0); 
		glPopMatrix(); 
		glutSwapBuffers();
	}
	
	else if(user_control == IS_START_GAME) {
		welcomeDisplay();
	}
	
	else if(user_control == IS_STOP_GAME) {
		endDisplay();
	}
}

// Handle ball for collide
void timerFunctionForObject(int value)
{ 
	if(user_control == IS_PLAY_GAME) {
	    x1 += xstep;
		x2 += ystep;
	
		if(x1 >= LIMITED_MOVE || x1 <= -LIMITED_MOVE) {
			xstep = -xstep;
		}
			
		if(x2 >= LIMITED_Y_COORDINATE) {
			ystep = -ystep;  
		}
			
		int spaceCoordinate = LIMITED_Y_COORDINATE - barScaleY;
		if(x2 <= -spaceCoordinate) {
			GLfloat frontBarCoordinate = distanceMoveBar - (barScaleX / 2.0);
			GLfloat backBarCoordinate = distanceMoveBar + (barScaleX / 2.0);
			
			if(x1 > frontBarCoordinate && x1 < backBarCoordinate){
				ystep = -ystep; 
				x2 = -spaceCoordinate;
				
				score++;
			}
		}
		if(x2 < -spaceCoordinate) {
			user_control = IS_STOP_GAME;
			glutPostRedisplay();
		}
	
	    glutPostRedisplay();
	    glutTimerFunc(30, timerFunctionForObject, 1);
	}
	else if (user_control == IS_START_GAME || user_control == IS_STOP_GAME){
	    glutPostRedisplay();
	    glutTimerFunc(1000, timerFunctionForObject, 0);
	}
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
	if(distanceMoveBar <= - LIMITED_MOVE)
		distanceMoveBar = - LIMITED_MOVE;
}

void limitRight() {
	if(distanceMoveBar >= LIMITED_MOVE)
		distanceMoveBar = LIMITED_MOVE;
}

void moveLeft() {
	distanceMoveBar = (distanceMoveBar - 1); // di chuyen
	limitLeft();
}

void moveRight() {
	distanceMoveBar = (distanceMoveBar + 1); // di chuyen
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
		case GLUT_KEY_HOME: // (HOME)
			user_control = IS_START_GAME;
			reset();
			glutPostRedisplay();
			break;
		default:
			break;
	}
}

void userKeyboard (unsigned char key, int x, int y)
{
	switch (key) {
		case 's':
			user_control = IS_START_GAME;
			reset();
			break;
		case 'p':
			if(user_control == IS_START_GAME){
				user_control = IS_PLAY_GAME;
			}
			break;
		case 'e':
			user_control = IS_STOP_GAME;
			break;
		default:
			break;
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


int main(int argc, char** argv)
{		
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (WIDTH_WINDOW, HEIGHT_WINDOW); 
	glutInitWindowPosition (0, 0);
	glutCreateWindow(TITLE_GAME);
	init ();
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutSpecialFunc(keyboard);
	glutKeyboardFunc(userKeyboard);
	glutTimerFunc(33, timerFunctionForObject, 1);
	glutMainLoop();
	return 0;
}