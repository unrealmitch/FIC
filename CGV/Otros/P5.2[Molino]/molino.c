#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>


#define WORLD_RADIUS    20.0f
#define BASE_RADIUS     0.5f
#define BASE_HEIGHT     2.0f
#define BLADE_RADIUS    1.0f

#define ZOOM_INC        0.2f   // Increments
#define OBS_INC         10.0f;
#define BLADE_ANGLE_INC  2.0f


int width = 500, height = 600; // Window size

GLfloat obs_x = 10.0f;         // Observer angles
GLfloat obs_y = 10.0f;
GLfloat obs_z = -2.0f;
GLfloat head_y = 10.0f;        // Head angle
int orto = 0;                  // Wether or not to apply ortogonal projection
int oy = 0;                    // Origin of coordinates of the mouse

GLfloat blade_spin = 0.0f;     // Blade spinning angle
GLfloat blade_spin_inc = 2;    // Blade spinning speed
GLfloat blade_angle = 0.0f;

int rotable = 0;               // Wether or not the figure is rotable
int spin = 1;                  // Spinning way


// Some material properties
GLfloat mat_diffuse_red[]   = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat mat_diffuse_green[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat mat_diffuse_blue[]  = { 0.1f, 0.3f, 1.0f, 1.0f };
GLfloat mat_diffuse_white[] = { 1.0f, 1.0f, 1.0f, 1.0f };


void reshape(int _width, int _height) {

  width = _width;
  height = _height;
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();  

  if (orto)
	glOrtho(-2.0, 2.0, -2.0, 2.0, 0.1, 10.0);
  else
	gluPerspective(90.0f, (GLfloat)width/(GLfloat)height, 0.1f, 2.0f*WORLD_RADIUS);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
}

void setObserver() {

  glTranslatef(0.0f, BASE_HEIGHT*0.25f, obs_z);
  glRotatef(obs_x, 0.1f, 0.0f, 0.0f);
  glRotatef(obs_y, 0.0f, 0.1f, 0.0f);

}

void drawBackground() {

  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_green);

  glPushMatrix(); {

	glTranslatef(0.0f, -6.0f, 0.0f);

	glBegin(GL_QUADS); {
	  
	  // Floor
	  glVertex3f( WORLD_RADIUS, 0.0f, -WORLD_RADIUS);
	  glVertex3f(-WORLD_RADIUS, 0.0f, -WORLD_RADIUS);
	  glVertex3f(-WORLD_RADIUS, 0.0f,  WORLD_RADIUS);
	  glVertex3f( WORLD_RADIUS, 0.0f,  WORLD_RADIUS);
	  
	}
	glEnd();
	
	glCullFace(GL_FRONT);
	glutSolidSphere(WORLD_RADIUS, 50, 50);
	glCullFace(GL_BACK);

  }
  glPopMatrix();

	

}

void drawBody() {

  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_white);

  glPushMatrix(); {
	
	glTranslatef(0.0f, -BASE_HEIGHT, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

	// Base
	glutSolidCone(BASE_RADIUS/3.0f, BASE_HEIGHT+0.14f, 10, 10);

	// Body
	glScalef(1.0f, 1.0f, 0.1f);
	glutSolidTorus(BASE_RADIUS, 0.0f, 20, 20);
	
  }
  glPopMatrix();

}

void drawHead() {

  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_white);


  // Head
  glPushMatrix(); {

	glScalef(0.5f, 0.5f, 1.0f);

	// shearing
	GLfloat m[] = { 1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, -0.5f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f };
	// wow
	GLfloat n[] = { 1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.1f, 0.5f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f };
	//glMultMatrixf(m);
	//glMultMatrixf(n);

	glutSolidCube(BASE_RADIUS);
	
  }
  glPopMatrix();

  
  // Anemometer base
  glPushMatrix(); {

	glTranslatef(0.0f, BASE_RADIUS/2.0f, -0.2f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.02, 0.3, 10, 10);
	
  }
  glPopMatrix();

}

void drawBlades() {

  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_white);


  glPushMatrix(); {

	glRotatef(blade_spin, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, 0.0f, BASE_RADIUS/2.0);


	// Nose
	glPushMatrix(); {
	
	  glScalef(1.0f, 1.0f, 2.0f);
	  glutSolidSphere(0.07f, 10, 10);
	
	}
	glPopMatrix();


	// Blades
	glPushMatrix(); {

	  glTranslatef(0.0f, 0.0f, 0.02);
  
	  int i;
	  for (i=0; i<360; i+=120) {
	  
		glPushMatrix(); {
		
		  glRotatef(i, 0.0f, 0.0f, 2.0f);
		  glRotatef(blade_angle, 1.0f, 0.0f, 0.0f);
		  glScalef(1.0f, 0.2f, 0.02f);

		  // 2x shearing combo
		  GLfloat m[] = { 1.0f, 0.0f, 0.0f, 0.0f,
						  -0.5f, 1.0f, 0.0f, 0.0f,
						  0.0f, 0.0f, 1.0f, 0.0f,
						  0.0f, 0.0f, 0.0f, 1.0f };
		  GLfloat n[] = { 1.0f, 0.0f, 0.0f, 0.0f,
						  0.0f, 1.0f, 0.0f, -2.0f,
						  0.0f, 0.0f, 1.0f, 0.0f,
						  0.0f, 0.0f, 0.0f, 1.0f };
		  glMultMatrixf(m);
		  glMultMatrixf(n);

		  glTranslatef(BLADE_RADIUS/2.0f+0.08f, -BLADE_RADIUS*0.4f, 0.0f);
		  glutSolidCube(BLADE_RADIUS);
		
		}
		glPopMatrix();
	  
	  }

	}
	glPopMatrix();

  }
  glPopMatrix();

}


void drawAnemometer() {

  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_white);

  // Blades
  glPushMatrix(); {

	glTranslatef(0.0f, BASE_RADIUS/2.0, -0.2f);
	glRotatef(-blade_spin*1.5, 0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.03f, 10, 10);
  
	int i;
	for (i=0; i<360; i+=120) {
	  
	  glPushMatrix(); {
		
		glRotatef(i, 0.0f, 1.0f, 0.0f);


		// Axis
		glPushMatrix(); {

		  glScalef(1.0f, 0.05f, 0.05f);
		  glTranslatef(0.1f, 0.0f, 0.0f);
		  glutSolidCube(0.2);

		}
		glPopMatrix();


		// Cones
		glPushMatrix(); {

		  glTranslatef(0.24f, 0.00f, -0.01f);
		  glutSolidCone(0.05, 0.08, 10, 5);

		  // Inverting the culling face, so we can see the
		  // interior of the interior cone
		  glCullFace(GL_FRONT);
		  glutSolidCone(0.05, 0.04, 10, 5);
		  glCullFace(GL_BACK);

		}
		glPopMatrix();
		
	  }
	  glPopMatrix();
	  
	}

  }
  glPopMatrix();

}


void display() {

  glLoadIdentity();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  drawBackground();
  setObserver();


  drawBody();
  
  glPushMatrix(); {
	glRotatef(head_y, 0.0f, 1.0f, 0.0f);

	drawHead();
	drawBlades();
	drawAnemometer();
  }
  glPopMatrix();

  
  glFlush();
  glutSwapBuffers();


  blade_spin += blade_spin_inc;

  usleep(10000);

}

void menuapp(int value) {

  switch(value) {
  case 1: 
	blade_spin_inc = -blade_spin_inc;
	spin = -spin;
	break;
  case 2:  exit(2);                    break;
  case 3:  blade_spin_inc += 2*spin;  break;
  case 4:  blade_spin_inc -= 2*spin;  break;
  default:                             break;
  }

}

void cmouse(int button, int state, int x, int y) {

  switch (button) {
	
  case GLUT_LEFT_BUTTON:
	switch (state) {
	case GLUT_DOWN:  rotable = 1;  break;
	case GLUT_UP:    rotable = 0;  break;
	default:                       break;
	}
	break;

  default:
	break;

  }

  oy = x;

}

void amouse(int x, int y) {

  if (rotable) {
	head_y += x-oy;
	oy = x;
  }

}

void keyboard_s(int key, int y, int x) {

  switch(key) {

  case GLUT_KEY_UP:    obs_x += OBS_INC;  break;
  case GLUT_KEY_DOWN:  obs_x -= OBS_INC;  break;
  case GLUT_KEY_RIGHT: obs_y += OBS_INC;  break;
  case GLUT_KEY_LEFT:  obs_y -= OBS_INC;  break;
	
  default:                                break;
	
  }

}

void keyboard(unsigned char key, int y, int x) {

  switch(key) {

  case 'w':  blade_angle += BLADE_ANGLE_INC;     break;
  case 's':  blade_angle -= BLADE_ANGLE_INC;     break;

  case 'o':  orto = 1; reshape(width, height); break;
  case 'p':  orto = 0; reshape(width, height); break;

  case 'q':  obs_z += ZOOM_INC;                break;
  case 'a':  obs_z -= ZOOM_INC;                break;
	
  case 27:  exit(0);                           break;
  default:                                     break;
	
  }

}

void init() {

  glClearColor (0.0, 0.0, 0.0, 0.0);

  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(keyboard_s);
  glutMotionFunc(amouse);
  glutMouseFunc(cmouse);

  glShadeModel(GL_SMOOTH);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_CCW);


  //glEnable(GL_POLYGON_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


  // Ride the Lighting

  glEnable(GL_LIGHTING);
  {
	GLfloat light_ambient[]   = { 0.05f, 0.0f, 0.0f, 1.0f };
	GLfloat light_diffuse[]   = { 0.5f, 0.6f, 0.7f, 1.0f };
	GLfloat light_specular[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_position[]  = { 4.0f, 0.0f, -2.0f, 1.0f };
	GLfloat light_direction[] = { -0.5f, 0.7f, -2.0f};
	GLfloat light_cutoff = 30.0f;
	
	glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, light_cutoff);

	GLfloat mat_ambient[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_diffuse[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_specular[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 80.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  
	glEnable(GL_LIGHT0);

  }


  // Fog
  
  glEnable(GL_FOG);
  {
	GLfloat fogColor[4] = {0.5, 0.5, 0.5, 1.0};
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.05);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	//glFogf(GL_FOG_START, 1.0);
	//glFogf(GL_FOG_END, 10.0);
  }


  // Menus

  int submenu = glutCreateMenu(menuapp);
  glutAddMenuEntry("Incrementar", 3);
  glutAddMenuEntry("Decrementar", 4);

  glutCreateMenu(menuapp);
  glutAddMenuEntry("Invertir", 1);
  glutAddSubMenu("Velocidad", submenu);
  glutAddMenuEntry("Salir", 2);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  
  reshape(width, height);

}

int main(int argc, char **argv) {

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(width, height);
  glutCreateWindow("glWindmill");
  //glutFullScreen(); // win

  init();

  glutMainLoop();

  return 0;

}

