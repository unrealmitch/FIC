#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

#define glCube glutSolidCube
#define glSolidCube glutSolidCube
#define gluSolidCube glutSolidCube
#define glColor glColor3f
#define gluColor glColor3f
#define glutColor glColor3f
#define glTranslate glTranslatef
#define glTranslate3f glTranslatef
#define gluTranslate glTranslatef
#define glutTranslate glTranslatef
#define glRotate glRotatef
#define gluRotate glRotatef
#define glutRotate glRotatef
#define glSolidTorus glutSolidTorus
#define glSolidTorusf glutSolidTorus
#define gluSolidTorus glutSolidTorus
#define glSolidTorus3f glutSolidTorus
#define glScale glScalef
#define gluScale glScalef
#define glutScale glScalef


int hazPerspectiva=0 ;
int global_width, global_height ;
int milisegundos = 20 ;
int moviendo_segmento2 = 0 ;

// Tamanos
float tamano_segmento=40.0f ;
float radio_codo=6.0f ;
float tamano_segmento_salido = 38.0f ;
float tamano_cesta = 13.0f ;

// Raton
int raton_ant_x, raton_ant_y ;

// Sentido rotacion
int sentido = 1 ;

// Segmento 1
float seg1_rotacion_y = 0 ;
float seg1_angulo_x = 45 ; // Angulo formado con el suelo

//Segmento 2
float seg2_angulo_x = 45 ; // Angulo formado con el segmento 1

//Segmento 3 (color verde, extension)
float seg3_salido = 5 ; // Unidades salidas del segmento 2

//Zoom
float zoom = -80 ;

//Cesta
float color_cesta_r = 0;
float color_cesta_g = 0;
float color_cesta_b = 1;

void reshape(int width, int height)
{
    global_width = width ;
    global_height = height ;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(hazPerspectiva) {
        gluPerspective(60.0f, (GLfloat)width/(GLfloat)height, 0.01f,60000.0f);
    } else {
        glOrtho(-50, 50, -60, 60, -400, 400);
    }

    glMatrixMode(GL_MODELVIEW);
}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslate(0,-30,zoom) ;

    // Base
        glColor(0,0,1.0f) ;
        glPushMatrix() ;
            glRotate(90,1,0,0) ;
            glutSolidTorus(2,8,15,15) ;
        glPopMatrix() ;

    //Segmento 1
        glColor(0.7f,0.7f,0.7f);
        glRotate(seg1_rotacion_y,0.0f,1.0f,0.0f) ;
        glRotate(seg1_angulo_x,1.0f,0.0f,0.0f) ;
        glTranslate(0,0,-tamano_segmento/2) ;
        glPushMatrix() ;
            glScale(14,5,tamano_segmento);
            glutSolidCube(1);
        glPopMatrix();

    //Codo
        glTranslate(0,0,-(tamano_segmento/2)-radio_codo);
        glPushMatrix() ;
            glutSolidSphere(radio_codo,20,20) ;
        glPopMatrix() ;

   //Segmento 2
        glRotate(180.0f-seg2_angulo_x,1.0f,0.0f,0.0f) ;
        glTranslate(0,0,-(tamano_segmento/2)-radio_codo);
        glPushMatrix() ;
            glScale(14,5,40);
            glutSolidCube(1);
        glPopMatrix();

    //Segmento 3
        glColor(0,1,0) ;
        glTranslate(0,0,-(tamano_segmento-tamano_segmento_salido)/2-seg3_salido) ;
        glPushMatrix() ;
            glScale(13,4,tamano_segmento_salido);
            glutSolidCube(1);
        glPopMatrix();

    //Cabina
        glColor(color_cesta_r,color_cesta_g,color_cesta_b) ;
        glTranslate(0,-tamano_cesta/2+2.0f,-tamano_segmento_salido/2-tamano_cesta/2);
        glRotate(-seg1_angulo_x-(180.0f-seg2_angulo_x),1,0,0) ;
        glCube(tamano_cesta) ;


    glFlush();
    glutSwapBuffers();

}

void menuapp(int value)
{
    switch (value) {
    case 0: exit(0); break;
    case 1: milisegundos = 60; break;
    case 2: milisegundos = 20; break;
    case 3: milisegundos = 1; break;
    case 4: color_cesta_r= 1; color_cesta_g= 0; color_cesta_b= 0; break; 
    case 5: color_cesta_r= 0; color_cesta_g= 1; color_cesta_b= 0; break; 
    case 6: color_cesta_r= 0; color_cesta_g= 0; color_cesta_b= 1; break; 
    }
}

void init()
{
    int submenu1, submenu2 ;

    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);

    submenu1=glutCreateMenu(menuapp);
    glutAddMenuEntry("Lento", 1);
    glutAddMenuEntry("Normal", 2);
    glutAddMenuEntry("Rapido", 3);

    submenu2=glutCreateMenu(menuapp);
    glutAddMenuEntry("Roja", 4);
    glutAddMenuEntry("Verde", 5);
    glutAddMenuEntry("Azul", 6);

    glutCreateMenu(menuapp);
    glutAddSubMenu("Cesta", submenu2);
    glutAddSubMenu("Velocidad", submenu1);
    glutAddMenuEntry("Salir",0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void TimerFunction()
{
    seg1_rotacion_y++ ;
    display();
    glutTimerFunc(milisegundos, TimerFunction, 1);
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'Q':
    case 'q': if (!hazPerspectiva) return ;
              if (zoom<(-10)) {zoom+=10;}
                 else {zoom=0;}
              reshape(global_width, global_height);
              break;

    case 'A':
    case 'a': if (!hazPerspectiva) return ;
              zoom-=10;
              reshape(global_width, global_height);
              break;

    case 'W':
    case 'w': if (seg3_salido<33) {seg3_salido+=5;} else {seg3_salido=38;} break;

    case 'S':
    case 's': if (seg3_salido>5) {seg3_salido-=5;} else {seg3_salido=0;} break;

    case 'R':
    case 'r': if (sentido == 1) {sentido=-1;}  else {sentido = 1;} break;

    case 'O':
    case 'o': hazPerspectiva=0; reshape(global_width, global_height); break;

    case 'P':
    case 'p': hazPerspectiva=1; reshape(global_width, global_height); break;


    case 27: exit(0) ; break;

    }
}

void processMouse(int boton, int estado, int x, int y) {
    switch (boton)
    {
        case GLUT_LEFT_BUTTON:

            if (estado==GLUT_DOWN) {
                moviendo_segmento2 = 1;
                raton_ant_x = x ;
                raton_ant_y = y ;

                if (glutGetModifiers() == GLUT_ACTIVE_SHIFT){
                    }
                if (glutGetModifiers() == GLUT_ACTIVE_ALT){
                    }
                if (glutGetModifiers() == GLUT_ACTIVE_CTRL){
                    }
                }
            else {
                moviendo_segmento2 = 0;

                if (glutGetModifiers() == GLUT_ACTIVE_SHIFT){
                    }
                if (glutGetModifiers() == GLUT_ACTIVE_ALT){
                    }
                if (glutGetModifiers() == GLUT_ACTIVE_CTRL){
                    }
                }
            break ;
        case GLUT_MIDDLE_BUTTON:
            if (estado==GLUT_UP) {}
            else {}
            break ;
/*        case GLUT_RIGHT_BUTTON:
            if (estado==GLUT_UP) {}
            else {}
            break ;
*/    }

}

void processMouseActiveMotion(int x, int y) {

    seg2_angulo_x -= (raton_ant_x - x) ;
    if (seg2_angulo_x<15) seg2_angulo_x=15 ;
    if (seg2_angulo_x>160) seg2_angulo_x=160 ;
    raton_ant_x = x ;

}

void processMousePassiveMotion(int x, int y) {

    if (moviendo_segmento2) return ;

    seg1_angulo_x -= (raton_ant_x - x) ;
    if (seg1_angulo_x<0) seg1_angulo_x=0 ;
    if (seg1_angulo_x>160) seg1_angulo_x=160 ;
    raton_ant_x = x ;

}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Examen OpenGL");
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

