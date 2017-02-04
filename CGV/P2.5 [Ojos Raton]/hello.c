/*
 * Capitulo 2
 * 'Hello World' de OpenGL
 * Aberto Jaspe Villanueva
 */

#include <stdio.h>
#include <GL/glut.h>

int scr_w = 600;
int scr_h = 600;
float size = 2;
float pos_x = 0;
float pos_y = 0;
float pos_z = -30;
float rot_x = 0;
float rot_y = 0;


float size2 = 2;
float pos2_x = 0;
float pos2_y = 0;
float pos2_z = -30;


void reshape(int width, int height)
{

	scr_w = width;
	scr_h = height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-25, 25, -25, 25, 5, -5);
	gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.01f,100.0f);
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
	glTranslatef((GLfloat)pos_x-4, (GLfloat)pos_y, (GLfloat)pos_z);
	glRotatef((GLfloat)rot_x*10, 0.0f, 1.0f, 0.0f);
	glRotatef((GLfloat)rot_y*10, 1.0f, 0.0f, 0.0f);
	glutWireSphere((GLfloat)size,30,30);

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

	glFlush();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{

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
	exit(0);
		break;
	}

	display();
}

void processMousePassiveMotion(int x, int y){

		
		int width = scr_w/2;
		int height = scr_h/2;

		rot_x = (x-width)/50.0f;
		rot_y = (y-height)/50.0f;

	char str[16];
	sprintf(str, "x:%d y:%d", x-width, y-height);

	glutSetWindowTitle(str);
	display();
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
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(processMousePassiveMotion);
	glutMainLoop();
	return 0;
}
