/*
 * Capitulo 2
 * 'Hello World' de OpenGL
 * Aberto Jaspe Villanueva
 */

#include <stdio.h>
#include <GL/glut.h>

int scr_w = 600;
int scr_h = 800;

int part_selected=0;

GLfloat size_e = 0.5;
GLfloat size_e2 = 0.5;
GLfloat size_c = 1.0;
GLfloat size_c2 = 0.5;

GLfloat size_body = 10;
GLfloat res_arm = 1.5;

GLfloat pos_leg[3] = {-1.0,-2,-15};
GLfloat pos_arm[3] = {-2.0,-1.5,-15};

GLfloat rot_arm[2][3] = {{.0,.0,.0},{.0,.0,.0}};
GLfloat rot_arm_2[2][3] = {{.0,.0,.0},{.0,.0,.0}};

GLfloat rot_leg[2][3] = {{.0,.0,.0},{.0,.0,.0}};
GLfloat rot_leg_2[2][3] = {{.0,.0,.0},{.0,.0,.0}};


GLfloat pos_c[3] = {.0,.0,-5};

GLfloat rot_c[3] = {.0,.0,.0};
GLfloat rot_c2[3] = {.0,.0,.0};

GLfloat res_all[3] = {1.0,1.0,1.0};

bool solid = false;
bool mov_automatic = false;
GLfloat speed = 2s;


void reshape(int width, int height)
{

	scr_w = width;
	scr_h = height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-5, 5, -5, 5, 10, -10);
	gluPerspective(60.0f, (GLfloat)width/(GLfloat)height, 0.001f,100.0f);
	//gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, -10.0f, 10.0f);
	glMatrixMode(GL_MODELVIEW);

}

void body(){
	glPushMatrix();
		glTranslatef(0, pos_arm[1]+2, pos_arm[2]);
		glScalef(3, 4.0, 1.0);
		glutWireCube(size_c);

	glPopMatrix();
}


void makearm(int arm){

	glPushMatrix();
	//Primera Esfera
	glLineWidth(1.0);

	glColor3f(.5f,.5f,.5f);
	glLoadIdentity();
	glTranslatef(pos_arm[0]+ (GLfloat) arm*4, pos_arm[1]+4.0, pos_arm[2]);
	glRotatef(rot_arm[arm][0]*10, 0.0f, 0.0f, 1.0f);
	glRotatef(rot_arm[arm][1]*10-180, 1.0f, 0.0f, 0.0f);
	glRotatef(rot_arm[arm][2]*10, 0.0f, 1.0f, 0.0f);
	glutWireSphere(size_e,30,30);
	
	//Primer Cubo
	glColor3f(.5f,.5f,.0f);
	glTranslatef(0, (size_e + size_c/2) + (res_arm-1)/2, 0);
	glPushMatrix();

	glScalef(1.0, res_arm, 1.0);
	glutWireCube(size_c);
	glPopMatrix();

	//Segunda Esfera
	glColor3f(.5f,.5f,.5f);
	glTranslatef(0, size_c/2+size_e2 + (res_arm-1)/2, 0);
	glRotatef(rot_arm_2[arm][0]*10, 0.0f, 0.0f, 1.0f);
	glRotatef(rot_arm_2[arm][1]*10, 1.0f, 0.0f, 0.0f);
	glRotatef(rot_arm_2[arm][2]*10, 0.0f, 1.0f, 0.0f);
	glutWireSphere(size_e2,30,30);
	
	//Segundo Cubo
	glLineWidth(1.0);
	glColor3f(.5f,.3f,.0f);
	glTranslatef(0, size_e2+size_c2/2 + (res_arm-1)/4, 0);
	glScalef(1.0, res_arm, 1.0);
	glPushMatrix();
	glutWireCube(size_c2);
	glPopMatrix();

	//Tarcera Esfera
	glTranslatef(0, size_e2, 0);
	glutWireSphere(size_e2/2,30,30);

	glPopMatrix();
}

void makeleg(int leg){

	glPushMatrix();
	//Primera Esfera
	glLineWidth(1.0);

	glColor3f(.5f,.5f,.5f);
	glLoadIdentity();
	glTranslatef(pos_leg[0] + (GLfloat) leg*2, pos_leg[1], pos_leg[2]);
	glRotatef(rot_leg[leg][0]*10, 0.0f, 0.0f, 1.0f);
	glRotatef(rot_leg[leg][1]*10-180, 1.0f, 0.0f, 0.0f);
	glRotatef(rot_leg[leg][2]*10, 0.0f, 1.0f, 0.0f);
	glutWireSphere(size_e,30,30);
	
	
	//Primer Cubo
	glColor3f(.5f,.5f,.0f);
	glTranslatef(0, (size_e + size_c/2) + (res_all[0]-1)/2, 0);
	glutWireCube(size_c);

	/*/Lineas Guia
	glColor3f(.5f,.0f,.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, 0.0f);
	glEnd();

	glColor3f(.0f,.5f,.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, -size_e-size_c/2, 0.0f);
	glVertex3f(0.0f, size_e+size_c+size_e2, 0.0f);
	glEnd();

	glColor3f(.0f,.0f,.5f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -2.0f);
	glEnd();
	*/

	//Segunda Esfera
	glColor3f(.5f,.5f,.5f);
	glTranslatef(0, size_c/2+size_e2, 0);
	glRotatef(rot_leg_2[leg][0]*10, 0.0f, 0.0f, 1.0f);
	glRotatef(rot_leg_2[leg][1]*10, 1.0f, 0.0f, 0.0f);
	glRotatef(rot_leg_2[leg][2]*10, 0.0f, 1.0f, 0.0f);
	glutWireSphere(size_e2,30,30);
	
	//Segundo Cubo
	glLineWidth(1.0);
	glColor3f(.5f,.3f,.0f);
	glTranslatef(0, size_e2+size_c2/2, 0);
	glutWireCube(size_c2);

	//Tarcera Esfera
	glTranslatef(0, size_e2, 0);
	glutWireSphere(size_e2/2,30,30);
	
	glPopMatrix();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	body();
	makearm(0);
	makearm(1);

	makeleg(0);
	makeleg(1);

	
	/*/Lineas Guia
	glColor3f(.5f,.0f,.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, 0.0f);
	glEnd();

	glColor3f(.0f,.5f,.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, -size_c2, 0.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glEnd();

	glColor3f(.0f,.0f,.5f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -2.0f);
	glEnd();
	*/

	glFlush();
	glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y)
{
	switch(key){


	case '0': part_selected = 0; break;	//Brazo 1
	case '1': part_selected = 1; break;	//Brazo 1-2
	case '2': part_selected = 2; break;	//Brazo 2
	case '3': part_selected = 3; break;	//Brazo 2-2
	                                   	
	case '4': part_selected = 4; break;	//Pierna 1-2
	case '5': part_selected = 5; break;	//Pierna 2-2

	//Rotación
	case 'q': 
		switch(part_selected){
			case 0: rot_arm[0][1]+=0.1; break;
			case 1: rot_arm_2[0][1]+=0.1; break;
			case 2: rot_arm[1][1]+=0.1; break;
			case 3: rot_arm_2[1][1]+=0.1; break;
			case 4: rot_leg_2[0][1]+=0.1; break;
			case 5: rot_leg_2[1][1]+=0.1; break;
		}
	break;

	case 'a':
		switch(part_selected){
			case 0: rot_arm[0][1]-=0.1; break;
			case 1: rot_arm_2[0][1]-=0.1; break;
			case 2: rot_arm[1][1]-=0.1; break;
			case 3: rot_arm_2[1][1]-=0.1; break;
			case 4: rot_leg_2[0][1]-=0.1; break;
			case 5: rot_leg_2[1][1]-=0.1; break;
		}
	break;

	case 'w': 
		switch(part_selected){
			case 0: rot_arm[0][2]+=0.1; break;
			case 1: rot_arm_2[0][2]+=0.1; break;
			case 2: rot_arm[1][2]+=0.1; break;
			case 3: rot_arm_2[1][2]+=0.1; break;
			case 4: rot_leg_2[0][2]+=0.1; break;
			case 5: rot_leg_2[1][2]+=0.1; break;
		}
	break;

	case 's':
		switch(part_selected){
			case 0: rot_arm[0][2]-=0.1; break;
			case 1: rot_arm_2[0][2]-=0.1; break;
			case 2: rot_arm[1][2]-=0.1; break;
			case 3: rot_arm_2[1][2]-=0.1; break;
			case 4: rot_leg_2[0][2]-=0.1; break;
			case 5: rot_leg_2[1][2]-=0.1; break;
		}
	break;

	case 'e': 
		switch(part_selected){
			case 0: rot_arm[0][1]+=0.1; break;
			case 1: rot_arm_2[0][1]+=0.1; break;
			case 2: rot_arm[1][1]+=0.1; break;
			case 3: rot_arm_2[1][1]+=0.1; break;
			case 4: rot_leg_2[0][1]+=0.1; break;
			case 5: rot_leg_2[1][1]+=0.1; break;
		}
	break;

	case 'd':
		switch(part_selected){
			case 0: rot_arm[0][0]-=0.1; break;
			case 1: rot_arm_2[0][0]-=0.1; break;
			case 2: rot_arm[1][0]-=0.1; break;
			case 3: rot_arm_2[1][0]-=0.1; break;
			case 4: rot_leg_2[0][0]-=0.1; break;
			case 5: rot_leg_2[1][0]-=0.1; break;
		}
	break;
	}
}


void processMousePassiveMotion(int x, int y){
		int width = scr_w/2;
		int height = scr_h/2;

		rot_leg[0][0] = (x-width)/50.0f;
		rot_leg[1][0] = (x-width)/50.0f;
		rot_leg[0][1] =  (y-height)/50.0f;
		rot_leg[1][1] =  (y-height)/50.0f;
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
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(scr_h, scr_w);
	glutCreateWindow("EYE_GL");
	glEnable(GL_DEPTH_TEST);
	glLineWidth(1.0);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(processMousePassiveMotion);
	glutTimerFunc(45, TimerFunction, 1);
	
	glutMainLoop();
	return 0;
}
