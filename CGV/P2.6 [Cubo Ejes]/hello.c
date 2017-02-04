/*
 * Capitulo 2
 * 'Hello World' de OpenGL
 * Aberto Jaspe Villanueva
 */

#include <stdio.h>
#include <GL/glut.h>

int scr_w = 600;
int scr_h = 600;

GLfloat size_c = 1.0;
GLfloat size_e = 0.5;

GLfloat pos_c[3] = {.0,.0,-5};
GLfloat pos_e[3] = {.0,.0,-5};

GLfloat rot_c[3] = {.0,.0,.0};
GLfloat rot_c2[3] = {.0,.0,.0};

void reshape(int width, int height)
{

	scr_w = width;
	scr_h = height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-5, 5, -5, 5, 10, -10);
	gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.001f,100.0f);
	//gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, -10.0f, 10.0f);
	glMatrixMode(GL_MODELVIEW);

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*
	glBegin(GL_TRIANGLES);
		glVertex3f(-1,-1,-1);
		glVertex3f(19,-1,-1);
		glVertex3f(0,1,40);
	glEnd();
	*/


	glColor3f(.0f,.5f,.5f);


	glLoadIdentity();


	//glTranslatef(pos_c[0]*0.1, pos_c[1]*0.1, pos_c[2]*0.1);

	glTranslatef(pos_c[0]*0.1, pos_c[1]*0.1, pos_c[2]*0.1);
	glRotatef(rot_c[0], 1.0f, 0.0f, 0.0f);
	glRotatef(rot_c[1], 0.0f, 1.0f, 0.0f);
	glRotatef(rot_c[2], 0.0f, 0.0f, 1.0f);
	
	
	//glTranslatef(0.0, 0.0, 0.0);
	
	glColor3f(.5f,.0f,.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, 0.0f);
	glEnd();

	glColor3f(.0f,.5f,.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glEnd();

	glColor3f(.0f,.0f,.5f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 2.0f);
	glEnd();

	glColor3f(1.0f,1.0f,0.0f);
	glutWireCube(size_e);

	/*
	//glLoadIdentity();
	//glTranslatef(0.0f, 0.0f, -10.0f);
	//glRotatef(rot_c[2], 1.0f, 0.0f, 0.0f);
	//glRotatef(rot_c[0], 0.0f, 1.0f, 0.0f);
	//glRotatef(rot_c[1], 0.0f, 0.0f, 1.0f);
	glTranslatef(size_e*1.5, 0, 0);
	glutWireSphere(size_e,30,30);
	
	//glLoadIdentity();
	//glTranslatef(0.0f, 0.0f, -10.0f);
	glRotatef(rot_c2[2], 1.0f, 0.0f, 0.0f);
	glRotatef(rot_c2[0], 0.0f, 1.0f, 0.0f);
	glRotatef(rot_c2[1], 0.0f, 0.0f, 1.0f);
	glTranslatef(size_e*1.5, 0, 0);
	glutWireCube(size_e);
	*/

	//glTranslatef(2.0, 0, 0);
	
	//glRotatef(rot_c[1], 0.0f, 1.0f, 0.0f);

	
	/*
	glColor3f(.0f,.5f,.5f);
	glLoadIdentity();
	glTranslatef((GLfloat)pos_x+4, (GLfloat)pos_y, (GLfloat)pos_z);
	glRotatef((GLfloat)rot_x*10, 0.0f, 1.0f, 0.0f);
	glRotatef((GLfloat)rot_y*10, 1.0f, 0.0f, 0.0f);
	glutWireSphere((GLfloat)size,30,30);


	glColor3f(1,1,1);
	glLoadIdentity();
	glTranslatef((GLfloat)pos2_x-4, (GLfloat)pos2_y, (GLfloat)pos2_z);
	glutSolidSphere((GLfloat)size2,20,20);

	glColor3f(1,1,1);
	glLoadIdentity();
	glTranslatef((GLfloat)pos2_x+4, (GLfloat)pos2_y, (GLfloat)pos2_z);
	glutSolidSphere((GLfloat)size2,20,20);
	*/

	glFlush();
	glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{

	//

	case '1': rot_c[0]++; break;
	case 'q':rot_c[0]--;break;

	case '2':rot_c[1]++;break;
	case 'w':rot_c[1]--;break;

	case '3':rot_c[2]++;break;
	case 'e':rot_c[2]--;break;

	case 'a': pos_c[0]++; break;
	case 'z':pos_c[0]--;break;

	case 's':pos_c[1]++;break;
	case 'x':pos_c[1]--;break;

	case 'd':pos_c[2]++;break;
	case 'c':pos_c[2]--;break;


	case 't':
		rot_c2[0]++;
	break;

	case 'g':
		rot_c2[0]--;
	break;

	case 'y':
		rot_c2[1]++;
	break;

	case 'h':
		rot_c2[1]--;
	break;

	case 'u':
		rot_c2[2]++;
	break;

	case 'j':
		rot_c2[2]--;
	break;
	/*
	//Figura 1
	case 'q':
		pos_z--;
	break;

	case 'e':
		pos_z++;
	break;


	case 'a':
		pos_x--;
	break;

	case 'd':
		pos_x++;
	break;

	case 'w':
		pos_y++;
	break;

	case 's':
		pos_y--;
	break;

	case '+':
		size++;
	break;

	case '-':
		size--;
	break;

	case 'z':
		rot_x--;
		break;
	case 'x':
		rot_x++;
		break;

	case 'c':
		rot_y--;
		break;
	case 'v':
		rot_y++;
		break;

	//Figura 2
	case 'j':
		pos2_x--;
	break;

	case 'l':
		pos2_x++;
	break;

	case 'i':
		pos2_y++;
	break;

	case 'k':
		pos2_y--;
	break;

	case '.':
		size2++;
	break;

	case ',':
		size2--;
	break;

	case 'u':
		pos2_z--;
	break;

	case 'o':
		pos2_z++;
	break;

	case 27:   // escape

	*/
	exit(0);
		break;
	}



	display();
}


void processMousePassiveMotion(int x, int y){

		
		int width = scr_w/2;
		int height = scr_h/2;

		rot_c[1] = (x-width)/50.0f;
		rot_c[0] = (y-height)/50.0f;

	//char str[16];
	//sprintf(str, "x:%d y:%d", x-width, y-height);

	//glutSetWindowTitle(str);
	//display();
}

void TimerFunction()
{
    display();
    glutTimerFunc(45, TimerFunction, 1);
}

void init()
{
	glClearColor(0,0,0,0);

	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(scr_h, scr_w);
	glutCreateWindow("EYE_GL");
	glEnable(GL_DEPTH_TEST);
	glLineWidth(2.0);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(processMousePassiveMotion);
	glutTimerFunc(45, TimerFunction, 1);
	
	glutMainLoop();
	return 0;
}
