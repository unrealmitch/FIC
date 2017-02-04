/*
 * feria.c
 */


#include <GL/glut.h>   /* Oh, GLUT, qué haríamos sin ti */
#include <math.h>      /* Algunas virguerías necesitan un poco de matemática */
#include <stdio.h>     /* Y las clásicas */
#include <stdlib.h>

#define DELAY 10       /* Retardo del temporizador */
#define FARNESS 2      /* Alejamiento de los objetos. La distancia por defecto. */

/* Colores para borrado de la escena. */
#define CLEAR_COLOR_RED   0
#define CLEAR_COLOR_GREEN 0
#define CLEAR_COLOR_BLUE  0
#define CLEAR_COLOR_ALPHA 0

#define INCREMENT 0.5

int rotate_flag;       /* Bandera de rotación.
                          La usaremos para rotar el
                          modelo. En BSS siempre a cero. */
                          
int last_x;            /* Último valor en X. */

int speed_factor = 1;  /* Factor de velocidad (si usado) */

/* Colores disponibles */
int colors[7][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 1.0, 0.0},
                    {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}, {0.0, 1.0, 1.0},
                    {1.0, 1.0, 1.0}};

int active_cube_color = 3;
      
int perspective_mode = 1;
double base_angle;     /* Ángulo de la base. */
double second_base_angle;     /* Ángulo de la base. */

double reverse_factor = -1.0; /* Factor de reversión */
double basculate_angle = 0.0; /* El tema del ángulo de la base */

/* Es mejor poner aquí todos los contadores, ángulos y
   desplazamientos para poder tenerlos todos en el mismo sitio. */
int saved_width;
int saved_height;

int z_position; 

void display (void);

/* 
 * reshape: Reescribe la matriz de proyección
 * cuando hay cambios en la ventana.
 *
 * TODO: Adecuar la proyección en función de lo que pida el ejercicio.
 */
void
reshape (int width, int height)
{
  saved_width = width;
  saved_height = height; /* Para otras llamadas a reshape */
  glViewport (0, 0, width, height);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  // glOrtho (left, right, botton, top, near, far) 
  // void gluPerspective( GLdouble	fovy,  GLdouble	aspect, GLdouble	zNear,  GLdouble	zFar )

  if (perspective_mode)
    gluPerspective (60.0f, (GLfloat)width / (GLfloat)height, 1.0f, 20.0f);
  else
    glOrtho(-FARNESS / 2, FARNESS / 2, -FARNESS / 2, FARNESS / 2, -2 * FARNESS, 2 * FARNESS);
    
  glMatrixMode (GL_MODELVIEW);
}

/*
 * keyboard: Todas las pulsaciones de teclado van aquí.
 */
void
keyboard (unsigned char key, int x, int y)
{
  switch (key)
  {
    case 27:
      exit (0); /* Escape */
      break;
      
    case 'o':
    case 'O':
      perspective_mode = 0;
      reshape (saved_width, saved_height);
      break;
      
    case 'p':
    case 'P':
      perspective_mode = 1;
      reshape (saved_width, saved_height);
      break;
      
    case 'A':
    case 'a':
      z_position--;
      break;
      
    case 'Q':
    case 'q':
      z_position++;
      break;
    
    case 'R':
    case 'r':
      reverse_factor *= -1.0;
      break;
      
    default:
      printf ("Keycode %p not known!\n", key);
  }
}


/*
 * mouse_active_motion_event: Procesa el movimiento del ratón.
 * Si se activa rotate_flag, actualizamos la rotación.
 */
void
mouse_active_motion_event (int x, int y) 
{
  /* Ojo. El movimiento del ratón produce INCREMENTOS en
     los ángulos de vista. Tengamos eso presente. */
  if (rotate_flag)
  {
    basculate_angle += (last_x - x) * 0.045;
    last_x = x;
  }
}

/*
 * mouse_button_event: Procesa un evento de pulsación de ratón.
 */
void
mouse_button_event (int button, int status, int x, int y)
{
  int modifiers;
  
  modifiers = glutGetModifiers ();
  
  
  if (status == GLUT_DOWN && modifiers & GLUT_ACTIVE_CTRL)
  {
    rotate_flag = 1; /* Listos para rotar */
    last_x = x;
  }
  else
  {
    rotate_flag = 0; /* Ya hemos acabado */
  }
}

/*
 * timer_event: Evento de temporizador.
 */
void
timer_event (int value)
{
  display();

  base_angle += INCREMENT;
  second_base_angle += INCREMENT * reverse_factor;
  /* Reiniciamos el temporizador. Y volvemos a pasar el valor. */
  glutTimerFunc (DELAY, timer_event, value); 
}

/*
 * draw_something: Pinta el componente X del modelo.
 */
inline void
draw_base (void)
{
  glPushMatrix ();
  
  glColor3f (0.0, 0.0, 1.0);
  glRotatef (-90.0, 1.0, 0.0, 0.0);
  glutSolidCone (1.0, 0.15, 15, 5);
  
  glPopMatrix ();
}

inline void
draw_base_2 (void)
{
  int i;
  
  
  glPushMatrix ();
  
  glColor3f (0.0, 0.9, 0.2);
  
  glPushMatrix ();
  glRotatef (90.0, 1.0, 0.0, 0.0);
  glutSolidCone (0.35, 0.1, 15, 5);
  glPopMatrix ();
  
  glColor3f (colors [active_cube_color][0],
             colors [active_cube_color][1],
             colors [active_cube_color][2]);
  
  for (i = 0; i < 4; i++)
  {
    glPushMatrix ();
    glRotatef (90 * i, 0.0, 1.0, 0.0);
    glTranslatef (0.0, 0.0, 0.25);
    glRotatef (-2 * 90 * i, 0.0, 1.0, 0.0);
    
    glTranslatef (0.0, 0.05, 0.0);
    
    glutSolidCube (0.1f);
    glPopMatrix ();
  }
  glPopMatrix ();
}

/*
 * draw_something: Pinta el componente X del modelo.
 */
inline void
draw_arm (void)
{
  glPushMatrix ();
  
  glColor3f (0.5, 0.5, 0.5);
  
  glScalef (0.15, 1.2, 0.25);
  glutSolidCube (0.5);
  
  glPopMatrix ();
}

/*
 * draw_model: Pinta el modelo.
 */
inline void
draw_model (void)
{
  glPushMatrix ();


  glRotatef (base_angle * speed_factor, 0.0, 1.0, 0.0);
  
  glTranslatef (0.0, -0.5, 0.0);
  draw_base ();
  
  /* Vamos a elevar nuestro brazo para que no esté dentro de la base */
  glTranslatef (0.0, 0.15, 0.0);
  glRotatef (22.5 - sin (basculate_angle / 2.0) * 22.5 - 90.0, 0.0, 0.0, 1.0);
  glTranslatef (0.0, 0.3, 0.0); /* Sabemos que nuestro invento mide 0.6 */
  /* Las cosas las ponemos 0.3 más allá en Y */
  
  draw_arm ();
  glTranslatef (0.0, 0.3, 0.0);
  
  
  
  
  /* Y deshacemos el ángulo del brazo */
  glRotatef (- 22.5 + sin (basculate_angle / 2.0) * 22.5 + 90.0, 0.0, 0.0, 1.0);
  /* Y el de la base */
  glRotatef (- base_angle * speed_factor, 0.0, 1.0, 0.0);
  
  glRotatef (2 * second_base_angle * speed_factor, 0.0, 1.0, 0.0); /* Ahora vamos hacia un lado o hacia otro */
  glTranslatef (0.0, 0.1, 0.0);
  draw_base_2 ();
  
  glPopMatrix ();
}


/*
 * display: Pintado del modelo.
 */
void
display (void)
{
  glMatrixMode (GL_MODELVIEW);
  glShadeModel (GL_SMOOTH);
  
  /* Limpiamos este buffer */
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glLoadIdentity (); /* Y partimos de una matriz identidad */
  /* Realmente esto no es necesario más que una vez, porque
     podríamos jugar con glPushMatrix y glPopMatrix para
     que funcionase con el mismo efecto. */
  
  /* Movemos los objetos hacia atrás para poder apreciarlos mejor */
  glTranslatef (0.0, 0.0, (GLfloat) z_position / 10.0 - FARNESS);


  /* EMPEZAMOS A PINTAR AQUÍ */
  draw_model ();
  /* TERMINAMOS DE PINTAR AQUÍ */
  
  glutSwapBuffers (); /* Intercambiamos los buffers. */
  /* Oh, sí Double Buffering */
}


/*
 * menu_event: Maneja eventos del ratón.
 * TODO: Usar #define's para mayor claridad.
 */
void
menu_event (int entry)
{
  if (!entry)
    exit (0);
  else if (entry >= 10 && entry < 17)
    active_cube_color = entry - 10;
  else if (entry == 20)
    speed_factor = 1;
  else if (entry == 21)
    speed_factor = 2;
  else if (entry == 22)
    speed_factor = 4;
}

/*
 * init: Función de inicialización.
 */
 
void
init (void)
{
  int submenu_1, submenu_2;
  
  glEnable (GL_DEPTH_TEST); /* Activamos el z-buffer */
  glClearColor (CLEAR_COLOR_RED,
                CLEAR_COLOR_GREEN,
                CLEAR_COLOR_BLUE,
                CLEAR_COLOR_ALPHA);   /* Y limpiamos para empezar.  */

  
  /* Ahora los menuses. */
  
  submenu_1 = glutCreateMenu (menu_event); /* Acepta el manejador. */
  glutAddMenuEntry ("Rojo", 10);
  glutAddMenuEntry ("Verde", 11);
  glutAddMenuEntry ("Amarillo", 12);
  glutAddMenuEntry ("Azul", 13);
  glutAddMenuEntry ("Magenta", 14);
  glutAddMenuEntry ("Cian", 15);
  glutAddMenuEntry ("Blanco", 16);
  
  submenu_2 = glutCreateMenu (menu_event);
  glutAddMenuEntry ("Modo relax", 20);
  glutAddMenuEntry ("Modo fiesta", 21);
  glutAddMenuEntry ("Modo \"el revientaestómagos\"", 22);
  
  /* Menú principal */
  glutCreateMenu (menu_event);

 
  /* Ahora los añadimos */
  glutAddSubMenu ("Colorinchos", submenu_1);
  glutAddSubMenu ("Velocidades", submenu_2);
  glutAddMenuEntry ("Salir", 0);

  /* Y hala, asociados al botón derecho */
  glutAttachMenu (GLUT_RIGHT_BUTTON);

}

int
main (int argc, char *argv[])
{
    glutInit (&argc, argv);
    
    /* Usamos Double Buffering, para variar. */
    /* GLUT_DEPTH ha de quitarse si no funciona. */
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowPosition (50, 50);
    glutInitWindowSize (500, 500);
    
    glutCreateWindow ("Ejercicio OpenGL");
    
    init();
    
    glutDisplayFunc (display);
    glutReshapeFunc (reshape);
    glutKeyboardFunc (keyboard);
    glutMouseFunc (mouse_button_event);
    glutMotionFunc (mouse_active_motion_event);
    glutTimerFunc (DELAY, timer_event, 1);
    
    /* Venga, vamos allá. */

    glutMainLoop ();
    
    return 0;
}

