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
GLfloat res_arm = 2.0;

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

int solid = 0;
int mov_automatic = 0;
GLfloat speed = 0.1;

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
	glColor3f(1.0f,1.0f,1.0f);
	glTranslatef(0, pos_arm[1]+2, pos_arm[2]);
	glPushMatrix();
	glScalef(3, 4.0, 1.0);
	glutWireCube(size_c);
	glPopMatrix();
	glTranslatef(0, 3.25, 0);

	glutWireSphere(1,16,16);

	glPopMatrix();
}


void makearm(int arm){

	glPushMatrix();
	//Primera Esfera
	glLineWidth(1.0);

	glColor3f(.5f,.0f,.0f);
	glLoadIdentity();
	glTranslatef(pos_arm[0]+ (GLfloat) arm*4, pos_arm[1]+4.0, pos_arm[2]);
	glRotatef(rot_arm[arm][0]*10, 0.0f, 0.0f, 1.0f);
	glRotatef(rot_arm[arm][1]*10-180, 1.0f, 0.0f, 0.0f);
	glRotatef(rot_arm[arm][2]*10, 0.0f, 1.0f, 0.0f);
	if(!solid) glutWireSphere(size_e,8,8); else glutSolidSphere(size_e,8,8);
	
	//Primer Cubo
	glColor3f(.0f,.0f,1.0f);
	glTranslatef(0, (size_e + size_c/2) + (res_arm-1)/2, 0);
	glPushMatrix();

	glScalef(1.0, res_arm, 1.0);
	if(!solid) glutWireCube(size_c); else glutSolidCube(size_c);
	glPopMatrix();

	//Segunda Esfera
	glColor3f(.5f,.0f,.0f);
	glTranslatef(0, size_c/2+size_e2 + (res_arm-1)/2, 0);
	glRotatef(rot_arm_2[arm][0]*10, 0.0f, 0.0f, 1.0f);
	glRotatef(rot_arm_2[arm][1]*10, 1.0f, 0.0f, 0.0f);
	glRotatef(rot_arm_2[arm][2]*10, 0.0f, 1.0f, 0.0f);
	if(!solid) glutWireSphere(size_e2,8,8); else glutSolidSphere(size_e2,8,8);
	
	//Segundo Cubo
	glLineWidth(1.0);
	glColor3f(.5f,.5f,1.0f);
	glTranslatef(0, size_e2+size_c2/2 + (res_arm-1)/4, 0);
	glPushMatrix();
	glScalef(1.0, res_arm, 1.0);
	if(!solid) glutWireCube(size_c2); else glutSolidCube(size_c2);
	glPopMatrix();

	//Tarcera Esfera
	glTranslatef(0, size_e2 + (res_arm-1)/4, 0);
	if(!solid) glutWireSphere(size_e/2,4,4); else glutSolidSphere(size_e/2,4,4);

	glPopMatrix();
}

void makeleg(int leg){

	glPushMatrix();
	//Primera Esfera
	glLineWidth(1.0);

	glColor3f(.5f,.0f,.0f);
	glLoadIdentity();
	glTranslatef(pos_leg[0] + (GLfloat) leg*2, pos_leg[1], pos_leg[2]);
	glRotatef(rot_leg[leg][0]*10, 0.0f, 0.0f, 1.0f);
	glRotatef(rot_leg[leg][1]*10-180, 1.0f, 0.0f, 0.0f);
	glRotatef(rot_leg[leg][2]*10, 0.0f, 1.0f, 0.0f);
	if(!solid) glutWireSphere(size_e,8,8); else glutSolidSphere(size_e,8,8);
	
	
	//Primer Cubo
	glColor3f(.0f,1.0f,.0f);
	glTranslatef(0, (size_e + size_c/2) + (res_all[0]-1)/2, 0);
	if(!solid) glutWireCube(size_c); else glutSolidCube(size_c);

	//Segunda Esfera
	glColor3f(.5f,.0f,.0f);
	glTranslatef(0, size_c/2+size_e2, 0);
	glRotatef(rot_leg_2[leg][0]*10, 0.0f, 0.0f, 1.0f);
	glRotatef(rot_leg_2[leg][1]*10, 1.0f, 0.0f, 0.0f);
	glRotatef(rot_leg_2[leg][2]*10, 0.0f, 1.0f, 0.0f);
	if(!solid) glutWireSphere(size_e2,8,8); else glutSolidSphere(size_e2,8,8);
	
	//Segundo Cubo
	glLineWidth(1.0);
	glColor3f(.5f,1.0f,.5f);
	glTranslatef(0, size_e2+size_c2/2, 0);
	if(!solid) glutWireCube(size_c2); else glutSolidCube(size_c2);

	//Tarcera Esfera
	glTranslatef(0, size_e2, 0);
	if(!solid) glutWireSphere(size_e/2,4,4); else glutSolidSphere(size_e/2,4,4);
	
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

	glFlush();
	glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y)
{
	switch(key){


	case '1': part_selected = 0; break;	//Brazo 1
	case '2': part_selected = 1; break;	//Brazo 1-2
	case '3': part_selected = 2; break;	//Brazo 2
	case '4': part_selected = 3; break;	//Brazo 2-2
	                                   	
	case '7': part_selected = 4; break;	//Pierna 1-2
	case '8': part_selected = 5; break;	//Pierna 2-2
	case '5': part_selected = 6; break;	//Pierna 1-1
	case '6': part_selected = 7; break;	//Pierna 1-1
	                                   	
	case '0': part_selected = 10; break;	//Pierna 1-1

	//Rotación
	case 'q': 
		switch(part_selected){
			case 0: rot_arm[0][1]+=speed; break;
			case 1: rot_arm_2[0][1]+=speed; break;
			case 2: rot_arm[1][1]+=speed; break;
			case 3: rot_arm_2[1][1]+=speed; break;
			case 4: rot_leg_2[0][1]+=speed; break;
			case 5: rot_leg_2[1][1]+=speed; break;
		}
	break;

	case 'a':
		switch(part_selected){
			case 0: rot_arm[0][1]-=speed; break;
			case 1: rot_arm_2[0][1]-=speed; break;
			case 2: rot_arm[1][1]-=speed; break;
			case 3: rot_arm_2[1][1]-=speed; break;
			case 4: rot_leg_2[0][1]-=speed; break;
			case 5: rot_leg_2[1][1]-=speed; break;
		}
	break;

	case 'w': 
		switch(part_selected){
			case 0: rot_arm[0][2]+=speed; break;
			case 1: rot_arm_2[0][2]+=speed; break;
			case 2: rot_arm[1][2]+=speed; break;
			case 3: rot_arm_2[1][2]+=speed; break;
			case 4: rot_leg_2[0][2]+=speed; break;
			case 5: rot_leg_2[1][2]+=speed; break;
		}
	break;

	case 's':
		switch(part_selected){
			case 0: rot_arm[0][2]-=speed; break;
			case 1: rot_arm_2[0][2]-=speed; break;
			case 2: rot_arm[1][2]-=speed; break;
			case 3: rot_arm_2[1][2]-=speed; break;
			case 4: rot_leg_2[0][2]-=speed; break;
			case 5: rot_leg_2[1][2]-=speed; break;
		}
	break;

	case 'e': 
		switch(part_selected){
			case 0: rot_arm[0][0]+=speed; break;
			case 1: rot_arm_2[0][0]+=speed; break;
			case 2: rot_arm[1][0]+=speed; break;
			case 3: rot_arm_2[1][0]+=speed; break;
			case 4: rot_leg_2[0][0]+=speed; break;
			case 5: rot_leg_2[1][0]+=speed; break;
		}
	break;

	case 'd':
		switch(part_selected){
			case 0: rot_arm[0][0]-=speed; break;
			case 1: rot_arm_2[0][0]-=speed; break;
			case 2: rot_arm[1][0]-=speed; break;
			case 3: rot_arm_2[1][0]-=speed; break;
			case 4: rot_leg_2[0][0]-=speed; break;
			case 5: rot_leg_2[1][0]-=speed; break;
		}
	break;
	}
}


void processMousePassiveMotion(int x, int y){
		int width = scr_w/2;
		int height = scr_h/2;
		int x_rot = (x-width)/50.0f;
		int y_rot = (y-height)/50.0f;;

		switch(part_selected){
			case 0: rot_arm[0][0]=x_rot; rot_arm[0][1]=y_rot; break;
			case 1: rot_arm_2[0][0]=x_rot; rot_arm_2[0][1]=y_rot; break;
			case 2: rot_arm[1][0]=x_rot;rot_arm[1][1]=y_rot; break;
			case 3: rot_arm_2[1][0]=x_rot;rot_arm_2[1][1]=y_rot; break;
			case 4: rot_leg_2[0][0]=x_rot;rot_leg_2[0][1]=y_rot; break;
			case 5: rot_leg_2[1][0]=x_rot;rot_leg_2[1][1]=y_rot; break;
			case 6: rot_leg[0][0]=x_rot;rot_leg[0][1]=y_rot; break;
			case 7: rot_leg[1][0]=x_rot;rot_leg[1][1]=y_rot; break;
		}
}

void TimerFunction()
{
    display();
    glutTimerFunc(45, TimerFunction, 1);
}

void menuapp(int value)
{
    if(value==1) solid=1;
    if(value==2) solid=0;

    if(value==3) speed=.1;
    if(value==4) speed=.2;
    if(value==5) speed=.4;
    if(value==6) speed=.8;

    if(value==7) mov_automatic=0;
    if(value==8) mov_automatic=1;
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
	glutCreateWindow("BODY OpenGL");
	glEnable(GL_DEPTH_TEST);
	glLineWidth(1.0);

    int submenu1=glutCreateMenu(menuapp);
    glutAddMenuEntry("Solido", 1);
    glutAddMenuEntry("Alambre", 2);
    glutCreateMenu(menuapp);

    int submenu2=glutCreateMenu(menuapp);
    glutAddMenuEntry("x1", 3);
    glutAddMenuEntry("x2", 4);
    glutAddMenuEntry("x4", 5);
    glutAddMenuEntry("x8", 6);
    glutCreateMenu(menuapp);

    glutAddSubMenu("Apariencia",submenu1);
    glutAddSubMenu("Velocidad", submenu2);
    glutAddMenuEntry("Mov. Manual",7);
    glutAddMenuEntry("Mov. Automatico",8);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
	

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(processMousePassiveMotion);
	glutTimerFunc(45, TimerFunction, 1);
	
	glutMainLoop();
	return 0;
}
