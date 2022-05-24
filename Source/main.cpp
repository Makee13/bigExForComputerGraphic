#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>`	

static int day= 0;
GLfloat t=1.0f;  
GLfloat t1=1.0f,t2=1.0f,t3=0.0f;
GLfloat windowWidth;
GLfloat windowHeight;
GLfloat xstep=0.1f; 
GLfloat ystep=0.1f; 
void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);

//  Ve mat phang
	glPushMatrix();
	glColor3f(0.0,1.0,0.0);
	glScalef(5,0.6,5);
	glTranslatef((GLfloat) day/5 , -9, 0);	
	glutSolidCube(1.0);
	glPopMatrix();
	
//	gluLookAt (5.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, .0);	
	glPushMatrix();
		glColor3f (1.0, 0.5, 0.0);
		glTranslatef(t1,t2,t3); 
		glutWireSphere(1.0,200.0,200.0); 
	glPopMatrix(); 
	
	
	glutSwapBuffers();
}
// xu ly bong
void TimerFunctionForObject(int value)
    {   	
    	t1+=xstep;
		t2+=ystep;
		if(t1>=5 || t1<=-5)
			 xstep=-xstep;
		if(t2>=5 || t2<=-5)
			 ystep=-ystep;  
//		|| t2<=-5    
		
		t1+=xstep;
		t2+=ystep;    
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
	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (0, 1, 10, 0.0, 0.0, 0.0, 0, 1, 0);
//	gluLookAt (5.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, .0);	
}

void limitLeft() {
	if(day <= -10+day/5)
		day = -10;
}

void limitRight() {
	if(day >= 10-day/5)
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
}


void init(void) 
{
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glShadeModel (GL_FLAT);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (1000, 1000); 
	glutInitWindowPosition (0, 0);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutSpecialFunc(keyboard);
	glutTimerFunc(33, TimerFunctionForObject, 1);
	glutMainLoop();
	return 0;
}
