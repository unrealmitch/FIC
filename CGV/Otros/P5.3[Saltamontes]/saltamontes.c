
#include <GL/glut.h>

GLfloat rotateX= 0.0f; //Movimiento arriba y abajo de un grupo de asientos
GLfloat rotateX_2= 45.0f; //Movimiento arriba y abajo del otro grupo de asientos
int haciaarriba=1; //define la direccion de movimiento de un grupo de asientos
int haciaarriba2=0; //define la direccion de movimiento del otro grupo de asientos
int maxangulo=45;


int dirgiro=0; //direccion de giro del saltamontes
GLfloat rotateY=0.0f; //angulo que controla el giro del saltamontes
int aumento=1;

int muevebrazos=1; //flag que determina si se mueven o no los brazos de la atraccion

GLfloat giracamara=0; //giro de la camara en el eje X

int color=0; //Color actual

int colors[7][3]={{1,1,1},{0,0,1},{1,0,0},{0,1,0},{0,1,1},{1,0,1}, {1,1,0}};

GLint ancho=600;
GLint alto=600;
 
int hazPerspectiva = 1;


int prevposx=0, prevposy=0;


void menuapp(int value)
{
    if(value==1) {
		if(color==7)
			color=0;
		else
		   color++;
    }
	else if (value==2){
		exit(0);
	}
	else if (value==3){
		if(maxangulo<45)
			maxangulo=maxangulo+5;
	}
	else if(value==4){
		if(maxangulo>10)
			maxangulo=maxangulo-5;
	}

    glutPostRedisplay();
	
}



void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if(hazPerspectiva){
     gluPerspective(60.0f, (GLfloat)width/(GLfloat)height, 1.0f, 50.0f);
     glTranslatef(0, 0, -15);
}
    else

      glOrtho(-20,20, -20, 20, 61, 10);

    glMatrixMode(GL_MODELVIEW);
 
    ancho = width;
    alto = height;
}

void hazBrazo(float grado, float direccion){
	float x=0;
	float y=2.2;
	float z=0.75;

		glPushMatrix();
			glRotatef(grado,0,0,1);
			
			
			   if(direccion)
				glRotatef(rotateX,1,0,0);
			   else
				glRotatef(rotateX_2,1,0,0);
			

			glTranslatef(x,y,z);
			glColor3f(1,0,1);
			glScalef(0.3,3.5,0.3);
			glutWireCube(1);
		glPopMatrix();

		glColor3f(colors[color][0],colors[color][1],colors[color][2]);
		glPushMatrix();
			glRotatef(grado,0,0,1);
			
			
			if(direccion)
				glRotatef(rotateX,1,0,0);
			else
				glRotatef(rotateX_2,1,0,0);
			
			
			glTranslatef(x,y+2,z-0.5);
			
			if(direccion)
				glRotatef(-rotateX,1,0,0);
			else
				glRotatef(-rotateX_2,1,0,0);
			

			glutSolidCube(1);
		glPopMatrix();
}

void display()
{
    int grado=0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(giracamara,1,0,0);

    glPushMatrix(); //Cono del centro
	glColor3f(1,1,0);
    	glutSolidCone(1,1.5,20,20);
    glPopMatrix();
	if(dirgiro)    
		glRotatef(rotateY,0,0,1);
	else
		glRotatef(-rotateY,0,0,1);
	
   	for(grado=0;grado<=6;grado++){
		hazBrazo(grado*60,grado%2);
	}

    glColor3f(1,1,1);

    glFlush();
    glutSwapBuffers();
}

void init()
{
	
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    ancho = 400;
    alto = 400;

    int submenu1;

    submenu1=glutCreateMenu(menuapp);
    glutAddMenuEntry("Aumentar ángulo", 3);
    glutAddMenuEntry("Disminuir ángulo", 4);

    glutCreateMenu(menuapp);
    glutAddMenuEntry("Cambiar Color",1);
    glutAddSubMenu("Angulo de giro", submenu1);
    glutAddMenuEntry("Salir",2);
	
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
 

void idle()
{
    rotateY=rotateY+aumento;
   if(muevebrazos){
    if(rotateX>=maxangulo)
		haciaarriba=-1;
    else if(rotateX<=0)
		haciaarriba=1;

    if(rotateX_2>=maxangulo)
		haciaarriba2=-1;
    else if(rotateX_2<=0)
		haciaarriba2=1;
   }

   

    rotateX=rotateX+1*haciaarriba;
    rotateX_2=rotateX_2+1*haciaarriba2;

    glutPostRedisplay();
}

 
void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
	case 'R':
	case 'r':
		if(dirgiro)
			dirgiro=0;
		else
			dirgiro=1;
		break;
	case 'P':
	case 'p':
		if(muevebrazos==1)
			muevebrazos=0;
		else if(muevebrazos==0)
			muevebrazos=1;
		break;
    case 27:   // escape
      exit(0);
      break;
    }
    glutPostRedisplay();
}
 
void raton (int button, int state, int x, int y){
}

void movimiento(int x,int y){
	if(prevposy<y){
		giracamara=giracamara-2;
		prevposy=y;
	}
	else if(prevposy>y){
		giracamara=giracamara+2;
		prevposy=y;
	}

}

void TimerFunction()
{
    
    rotateY=rotateY+aumento;
    
    if(muevebrazos){
    	if(rotateX>=maxangulo)
			haciaarriba=-1;
    	else if(rotateX<=0)
			haciaarriba=1;
	if(rotateX_2>=maxangulo)
			haciaarriba2=-1;
   	else if(rotateX_2<=0)
			haciaarriba2=1;
    

    	rotateX=rotateX+1*haciaarriba;
    	rotateX_2=rotateX_2+1*haciaarriba2;
    }
    glutPostRedisplay();  
    glutTimerFunc(23, TimerFunction, 1);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(ancho, alto);
    glutCreateWindow("Queco");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    //glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(raton);
     glutMotionFunc(movimiento);
    //glutPassiveMotionFunc(processMousePassiveMotion);
    glutTimerFunc(23, TimerFunction, 1);
    glutMainLoop();
    return 0;
}

