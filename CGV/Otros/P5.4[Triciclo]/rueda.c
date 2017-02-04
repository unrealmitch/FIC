/* Francisco J. Gómez López (inffgl00) */

#include <GL/glut.h>
 
GLfloat anguloGiroZ = 0.0f;
GLfloat anguloGiroY = 0.0f;

GLint ancho=600;
GLint alto=600;

int posicionX=0;
int posicionY=0;
int giro=-1;
int girarY=0;
GLfloat velocidad=2.0f;
int hazPerspectiva = 0;
int zoom = 0;
 
void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(hazPerspectiva)
      gluPerspective(60.0f, (GLfloat)width/(GLfloat)height, 0.01f, 100.0f);
    else
      glOrtho(-5, 5, -5, 5, -50, 50);

    glMatrixMode(GL_MODELVIEW);
 
    ancho = width;
    alto = height;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -10.0f+zoom);
    glRotatef(anguloGiroY, 0.0f, 1.0f, 0.0f);
    glRotatef(anguloGiroZ, 0.0f, 0.0f, 1.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glutSolidTorus(0.5f, 3.0f, 15, 50);

    glColor3f(1.0f, 0.0f, 0.0f);

    glPushMatrix();
    glTranslatef(0.0f, 2.8f, 2.2f);
    glRotatef(-anguloGiroZ, 0.0f, 0.0f, 1.0f);
    glScalef(1.0f, 0.5f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -2.8f, -2.2f);
    glRotatef(-anguloGiroZ, 0.0f, 0.0f, 1.0f);
    glScalef(1.0f, 0.5f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 0.0f);

    glPushMatrix();
    glScalef(0.2f, 0.2f, 3.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 1.4f, 1.6f);
    glScalef(0.2f, 3.0f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -1.4f, -1.6f);
    glScalef(0.2f, 3.0f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}


void menu(int value)
{
    if(value==1) velocidad*=2;
    if(value==2) velocidad/=2;
    if(value==3) giro*=-1;
}


void init()
{
    glutCreateMenu(menu);
    glutAddMenuEntry("Velocidad +", 1);
    glutAddMenuEntry("Velocidad -", 2);
    glutAddMenuEntry("Invertir giro", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

 
void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    { 
    case 'o':
    case 'O':
      hazPerspectiva = 0;
      reshape(ancho,alto);
      break;

    case 'p':
    case 'P':
      hazPerspectiva = 1;
      reshape(ancho,alto);
      break;

    case 'q':
    case 'Q':
      zoom++;
      break;

    case 'a':
    case 'A':
      zoom--;
      break;
    }
}

void processMouse(int boton, int estado, int x, int y)
{
    switch(boton)
    {
    case GLUT_LEFT_BUTTON:
      if (estado==GLUT_DOWN) girarY=1;
      if (estado==GLUT_UP) girarY=0;
      break;
    }
}

void processMouseActiveMotion(int x, int y)
{
   if (girarY) anguloGiroY+=x-posicionX;
   posicionX=x;
   posicionY=y;
}

void processMousePassiveMotion(int x, int y)
{
   posicionX=x;
   posicionY=y;
}


void TimerFunction()
{
    anguloGiroZ+=giro*velocidad;
    display();
    glutTimerFunc(33, TimerFunction, 1);
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(ancho, alto);
    glutCreateWindow("Rueda");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(33, TimerFunction, 1);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(processMouse);
    glutMotionFunc(processMouseActiveMotion);
    glutPassiveMotionFunc(processMousePassiveMotion);
    glutMainLoop();
    return 0;
}
