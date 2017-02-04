#include <GL/glut.h>

#define NORIA_R 10.0f

//Config
GLint scr_w=800;
GLint scr_h=600;

//Control
GLfloat noria_angle=0;
GLfloat noria_angle_mouse=0;
GLfloat noria_speed=1;
GLint 	noria_direction=1;

//Scene
GLfloat noria_z=-25.0f;

//Input
int mouse[2] = {0,0};

//Figures Config
GLfloat noria_radio = 10.0f;

GLfloat noria_box_s = 1.0f;
GLfloat noria_radio_r = 0.05f;
GLfloat noria_radio_h = NORIA_R;
GLfloat noria_circle_r = 0.05f;
GLfloat noria_circle_h = NORIA_R;
GLfloat noria_bar_r = 0.1f;
GLfloat noria_bar_h = 1.0f;

GLfloat base_s = 1.0f;
GLfloat base_bar_r = 0.15f;
GLfloat base_bar_h = NORIA_R*1.5;
GLfloat base_baru_r = 0.15f;
GLfloat base_baru_h = 3.0f;

GLfloat colours[7][3] = { {0.0f,0.0f,1.0f},		//Noria, c exterior
						{0.5f,0.5f,0.0f},		//Noria, barrotes
						{0.0f,0.0f,0.0f},		//Noria, barrotes 2
						{1.0f,0.0f,0.0f},		//Cajas
						{0.0f,1.0f,0.0f},		//Base
						{0.1f,0.5f,0.5f},		//Base, barrotes
						{0.0f,0.0f,0.0f}};		

void setColor(int i){
	glColor3f(colours[i][0],colours[i][1],colours[i][2]);
}

void reshape(int width, int height){
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (GLfloat)width/(GLfloat)height, 1.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);

	scr_w = width;
	scr_h = height;
}

void background(){

	glBegin(GL_QUADS);

	  glColor3f(0.5f, 0.5f, 1.0f);
	  glVertex3f(-20.0f, -40.0f, -80.0f);
	  glVertex3f(20.0f, -40.0f, -80.0f);
	  glVertex3f(20.0f, 40.0f, -80.0f);
	  glVertex3f(-20.0f, 40.0f, -80.0f);

	  glColor3f(0.8f, 0.8f, 1.0f);
	  glVertex3f(-20.0f, -40.0f, 0.0f);
	  glColor3f(0.5f, 0.5f, 1.0f);
	  glVertex3f(-20.0f, -40.0f, -80.0f);
	  glVertex3f(-20.0f, 40.0f, -80.0f);
	  glColor3f(0.8f, 0.8f, 1.0f);
	  glVertex3f(-20.0f, 40.0f, 0.0f);

	  glColor3f(0.8f, 0.8f, 1.0f);
	  glVertex3f(20.0f, -40.0f, 0.0f);
	  glColor3f(0.5f, 0.5f, 1.0f);
	  glVertex3f(20.0f, -40.0f, -80.0f);
	  glVertex3f(20.0f, 40.0f, -80.0f);
	  glColor3f(0.8f, 0.8f, 1.0f);
	  glVertex3f(20.0f, 40.0f, 0.0f);

	  glColor3f(0.8f, 0.8f, 1.0f);
	  glVertex3f(-20.0f, -40.0f, 0.0f);
	  glColor3f(0.5f, 0.5f, 1.0f);
	  glVertex3f(-20.0f, -40.0f, -80.0f);
	  glVertex3f(20.0f, -40.0f, -80.0f);
	  glColor3f(0.8f, 0.8f, 1.0f);
	  glVertex3f(20.0f, -40.0f, 0.0f);

	  glColor3f(0.8f, 0.8f, 1.0f);
	  glVertex3f(-20.0f, 40.0f, 0.0f);
	  glColor3f(0.5f, 0.5f, 1.0f);
	  glVertex3f(-20.0f, 40.0f, -80.0f);
	  glVertex3f(20.0f, 40.0f, -80.0f);
	  glColor3f(0.8f, 0.8f, 1.0f);
	  glVertex3f(20.0f, 40.0f, 0.0f);

 
	glEnd(); 
}
void draw_boxes(GLfloat angle){
	int i = 0;
	setColor(3);

	for(; i < 8; i++){
		glPushMatrix();
			glTranslatef(0.0f,-0.5f,0.0f);
			glRotatef(angle+i*45,0.0f,0.0f,1.0f);
			glTranslatef(NORIA_R,0.0f,0.0f);
			glRotatef(-angle+i*45,0.0f,0.0f,1.0f);
			glutSolidCube(noria_box_s);
		glPopMatrix(); 
	}
}

void draw_cylinder(char object){

	GLfloat c_r = 0, c_h = 0;

	switch (object){
		case 'r':	//radios noria
			c_r=noria_radio_r; c_h=noria_radio_h; break;
		case 'b':	//barras base
			c_r=base_bar_r; c_h=base_bar_h; break;
		case 'u':	//barras base union
			c_r=base_baru_r; c_h=base_baru_h; break;
		case 'n':	//barras noria
			c_r=noria_bar_r; c_h=noria_bar_h; break;
		default: break;
	}
	gluCylinder(gluNewQuadric(), c_r, c_r, c_h, 20, 5);

}
#define glutSolidCylinder(radio, altura, slices, stacks) gluCylinder(gluNewQuadric(), radio, radio, altura, slices, stacks)

void draw_noria(GLfloat angle)
{
	int i;

	glPushMatrix();

		glRotatef(angle,0.0f,0.0f,1.0f);
		glTranslatef(0.0f,0.0f,-0.5f);

		glPushMatrix();
			setColor(1);
			glRotatef(90,1.0f,0.0f,0.0f);
			for(i=0;i<8;i++)
			{
				glRotatef(45,0.0f,1.0f,0.0f);
				draw_cylinder('r');
			}
		glPopMatrix();

		setColor(0);
		glutSolidTorus(noria_circle_r,noria_circle_h,20,20);
		glTranslatef(0.0f,0.0f,1.0f);
		glutSolidTorus(noria_circle_r,noria_circle_h,20,20);

		glPushMatrix();
			setColor(1);
			glRotatef(90,1.0f,0.0f,0.0f);
			for(i=0;i<8;i++)
			{
				glRotatef(45,0.0f,1.0f,0.0f);
				draw_cylinder('r');
			}
		glPopMatrix();

		int x, n_bars; 
		GLfloat inc_angle_bar;
		GLfloat inc = -NORIA_R/3;

		for(x = 1; x < 4;x++){
			glPushMatrix();
				if(x == 3){
					n_bars = 32;
					inc_angle_bar = 11.25;
				}else{
					n_bars = 8;
					inc_angle_bar = 45;
				}

				for(i=0;i<n_bars;i++){
					glPushMatrix();
					glRotatef(inc_angle_bar*i,0.0f,0.0f,1.0f);
					glTranslatef(inc*x,0.0f,-1.0f);
					draw_cylinder('n');
					glPopMatrix();
				}
			glPopMatrix();
		}

	glPopMatrix();

}

void draw_struct()
{
	glPushMatrix();

		//BASÊ
		glPushMatrix();
			setColor(4);
			glTranslatef(0.0f,-NORIA_R-2.0f,0.0f);
			glScalef(NORIA_R*5,0.1f,10.0f);
			glutSolidCube(0.5f);
		glPopMatrix();

		//Barras
		glPushMatrix();
			setColor(5);
			glTranslatef(0.0f,0.0f,1.0f);
			glRotatef(40,0.0f,0.0f,1.0f);
			glRotatef(90,1.0f,0.0f,0.0f);
			draw_cylinder('b');
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0f,0.0f,1.0f);
			glRotatef(-40,0.0f,0.0f,1.0f);
			glRotatef(90,1.0f,0.0f,0.0f);
			draw_cylinder('b');
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0f,0.0f,-1.0f);
			glutSolidCylinder(0.15f,1.6f,10,1);
			glRotatef(40,0.0f,0.0f,1.0f);
			glRotatef(90,1.0f,0.0f,0.0f);
			draw_cylinder('b');
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0f,0.0f,-1.0f);
			glRotatef(-40,0.0f,0.0f,1.0f);
			glRotatef(90,1.0f,0.0f,0.0f);
			draw_cylinder('b');
		glPopMatrix();

		//Barra Union Lados
		glPushMatrix();
			glTranslatef(0.0f,0.0f,-1.4f);
			draw_cylinder('u');
		glPopMatrix();

	glPopMatrix();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	background();
	glTranslatef(0.0f, 0.0f, noria_z);
	glRotatef(noria_angle_mouse,1.0f,0.0f,0.0f);
	draw_boxes(noria_angle);
	draw_noria(noria_angle);
	draw_struct();
	glFlush();
	glutSwapBuffers();

}

void Noria_move()
{
	display();
	noria_angle+=noria_speed;
	glutTimerFunc(33, Noria_move, 1);
}

void menuapp(int value){
	switch(value){
		case 1: noria_speed=noria_direction*1;break;
		case 2: noria_speed=noria_direction*2;break;
		case 3: noria_speed=noria_direction*4;break;
		case 0: exit(0);
		default: break;
	}
}



void Keyboard(unsigned char key, int x, int y){
	switch(key){
		case '+': noria_z+=0.1f;break;
		case '-': noria_z-=0.1f;break;
		case 'r': case 'R':
		noria_speed=-noria_speed;
		noria_direction=-noria_direction;break;
		case 27:exit(0);break;
	}
}

void Move_mouse(int Button, int State, int x, int y){
	mouse[0]=x;mouse[1]=y;
}


void Noria_mouse(int x, int y)
{
	noria_angle_mouse+=(y-mouse[1]);
	mouse[0]=x;mouse[1]=y;
	display();
}

void init(){
	glClearColor(0,0,0,0);
	glEnable(GL_DEPTH_TEST);
	scr_w = 400; scr_h = 400;

	glutCreateMenu(menuapp);
	glutAddMenuEntry("x1", 1);
	glutAddMenuEntry("x2", 2);
	glutAddMenuEntry("x4", 3);
	glutAddMenuEntry("Exit",0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);  // Asignamos el menú a la pulsación del botón derecho del ratón
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(800-scr_w/2,450-scr_h/2);
	glutInitWindowSize(scr_w, scr_h);
	glutCreateWindow("Noria");
	init();
	glutTimerFunc(33, Noria_move, 1);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Move_mouse);
	glutMotionFunc(Noria_mouse);
	glutMainLoop();
	return 0;
}