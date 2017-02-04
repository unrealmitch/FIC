#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>


GLfloat anguloCubo = 0.0;
GLfloat anguloY = 0.0;
int tecla = 1, invertir = 1;

GLint ancho=400;
GLint alto=400;
 
int flag = 0;
 
void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
   
    glOrtho(-3, 3, -3, 3, -20, 20);

    glMatrixMode(GL_MODELVIEW);
 
    ancho = width;
    alto = height;
}


//0 izquierda
void drawToroide(int opc)
{
    glPushMatrix();

    glColor3f(1.0, 0, 0);
    glutWireTorus(0.1,1,10,20);
    glPopMatrix();

}
//0 arriba
void drawCube(int tor){

    if(tor == 0){
	glTranslatef(0,1,0);
	glRotatef(anguloCubo-90,0,0,1);
	glTranslatef(1,0,0);
	glColor3f(0,0,1);
	glutSolidCube(0.1);
    }
    else{
      glTranslatef(0,-1,0);
	glRotatef(90+anguloCubo,0,0,1);
	glTranslatef(1,0,0);
	glColor3f(0,0,1);
	glutSolidCube(0.1);
    }
}
void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();    

    glRotatef(anguloY,0,1,0);

    glTranslatef(0,1,0);
    drawToroide(0);

    glTranslatef(0,-2,0);
    drawToroide(0);

    glTranslatef(0,1,0);
    drawCube(flag);

    if(tecla){
	if (flag==1) {
	    anguloCubo = ((int)anguloCubo - invertir)%360;
	}
	else{
	    anguloCubo = ((int)anguloCubo + invertir)%360;
	}
	if (anguloCubo == 0) flag = (flag + 1)%2;
    }

    glFlush();
    glutSwapBuffers();

}

void keyboard(unsigned char key, int x, int y)
{    
    switch(key)
    {
    case 'R':
    case 'r':
      invertir *= -1;
      reshape(ancho,alto);
      break;
    }
}

void init()
{
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    ancho = 400;
    alto = 400;
}

void TimerFunction(){

    display();
    glutTimerFunc(10, TimerFunction, 1);

}

void processMouse(int boton, int estado, int x, int y){


    if ((boton == GLUT_LEFT_BUTTON)&&(estado == GLUT_DOWN)){
	if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
	    tecla = (tecla + 1)%2;
	}
    }

}

void processMouseActiveMotion(int x, int y) {
    anguloY +=1;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(ancho, alto);
    glutCreateWindow("Ocho");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(10, TimerFunction, 1);
    glutKeyboardFunc(keyboard);

    //Añadimos aquí los callbacks de procesado del ratón

    glutMouseFunc(processMouse);
    glutMotionFunc(processMouseActiveMotion);

    glutMainLoop();
    return 0;
}
