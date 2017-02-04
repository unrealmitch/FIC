/*	UDC:	Sistemas Operativos
 * 	Pract:  1ª
 * 	Autor:	Miguel Mosquera Perez
 * 	Fecha: 	03/10/2013
 * 	Grupo: 	4.2
 *  Horar:	Jueves 3:30-5:30
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>  
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <unistd.h>
#include <errno.h>

//Constantes para llamar funciones

const char * fAUTORES = "autores";
const char * fPID = "getpid";
const char * fDIR = "cdir";
const char * fLS = "list";
const char * fDEL = "delete";
const char * fDELD = "rdir";

//Constantes de los autores
const char * AutorNombre1 = "Miguel Mosquera Pérez";
const char * AutorNombre2 = "Manuel Figueras Gago";
const char * AutorLogin1 = "miguel.mosquera.perez@udc.es";
const char * AutorLogin2 = "manuel.figueiras@udc.es";

int TrocearCadena(char * cadena, char * trozos[]) {

    int i = 1;
    if ((trozos[0] = strtok(cadena, " \n\t")) == NULL)
        return 0;
    while ((trozos[i] = strtok(NULL, " \n\t")) != NULL)
        i++;
    return i;
}

char TipoFichero(mode_t m) {
    switch (m & S_IFMT) { /*and bit a bit con los bits de formato,0170000 */
        case S_IFSOCK: return 's'; /*socket */
        case S_IFLNK:
            return 'l';
            /*symbolic link*/
        case S_IFREG:
            return '-';
            /* fichero normal*/
        case S_IFBLK:
            return 'b';
            /*block device*/
        case S_IFDIR:
            return 'd';
            /*directorio */
        case S_IFCHR:
            return 'c';
            /*char device*/
        case S_IFIFO:
            return 'p';
            /*pipe*/
        default: return '?';
            /*desconocido, no deberia aparecer*/
    }
}

void ConvierteModo(mode_t m, char *permisos) {
    strcpy(permisos, "---------- ");
    permisos[0] = TipoFichero(m);
    if (m & S_IRUSR) permisos[1] = 'r';
    if (m & S_IWUSR) permisos[2] = 'w';
    if (m & S_IXUSR) permisos[3] = 'x';
    if (m & S_IRGRP) permisos[4] = 'r';
    if (m & S_IWGRP) permisos[5] = 'w';
    if (m & S_IXGRP) permisos[6] = 'x';
    if (m & S_IROTH) permisos[7] = 'r';
    if (m & S_IWOTH) permisos[8] = 'w';
    if (m & S_IXOTH) permisos[9] = 'x';
    if (m & S_ISUID) permisos[3] = 's';
    if (m & S_ISGID) permisos[6] = 's';
    if (m & S_ISVTX) permisos[9] = 't';
}

void mylogin() {
    printf("Login de autores: \n\n");
    printf("- %s : %s\n", AutorNombre1, AutorLogin1);
    printf("- %s : %s\n", AutorNombre2, AutorLogin2);
    printf("\n");
}

void mypid() {
    printf("PID de la shell: %d\n", getpid());
    printf("PID del padre: %d\n", getppid());
}

void mypwd() {
    char buffer[512];
    if ((getcwd(buffer, 512)) == NULL)
        perror(fDIR);
    else
        printf("%s\n", buffer);
}

void mycdir(char* trozos[], int numTrozos) {
    if (chdir(trozos[1]) == -1)
        perror(fDIR);
}

void mydelete(char * elementos_cadena) {

    if (fopen(elementos_cadena, "r") == NULL)
        perror("No se encuentra el fichero");
    else
        unlink(elementos_cadena);
}

void myrdir(char *ruta, int f) {

    DIR * directorio;
    struct dirent *archivo;
    directorio = opendir(ruta);

    if (directorio == NULL) {
        perror(fDELD);
    } else {
        while ((archivo = readdir(directorio)) != NULL) {
            if ((strcmp(archivo->d_name, ".") != 0) && (strcmp(archivo->d_name, "..") != 0)) {
                if (f){
                    char * path;
                    path = (char*) malloc(256 * sizeof (char));

                    sprintf(path, "%s/%s", ruta, archivo->d_name);

                    if (DT_DIR == archivo->d_type) myrdir(path, f);
                    else unlink(path);
                    free(path);
                }
                else{
                    perror("Directorio no vacio");
                    return;
                }
            }
        }
        rmdir(ruta);
    }
}


void my_ls(int arg_a, int arg_s, int arg_r, int dir) {

    char * args_ls;
    args_ls = (char*) malloc(32 * sizeof (char));

    strcpy(args_ls, "list");

    if (arg_a) strcat(args_ls, " -a");
    if (arg_s) strcat(args_ls, " -s");
    if (arg_r) strcat(args_ls, " -r");
    if (dir) strcat(args_ls, " /dir");
    printf("%s\n", args_ls);
    free(args_ls);
}

void myls(char ** trozos, int arg_a, int arg_s, int arg_r, int dir) {

    DIR *directorio;
    struct dirent *file_info;
    struct stat datosArchivos;
    struct passwd *pwduser;
    struct passwd *pwdgroup;
    char * ptr;
    char buf[1024];
    int len;
    int close = 0;
    char *dirrec[256];
    int numdir = 0;
    int i = 0;

    char buffer[256] = "";
    char aux[256];
    char * a_permisos;


    printf("\n");
    if (dir == -1) {
        //Obtenemos el directorio actual (no presente en el argumento [dir]) y lo imprimimos
        directorio = opendir(".");
        sprintf(buffer, "%s", ".");
        printf("%s\n", buffer);
    } else {
        //En caso de que se le pase el directorio a listar
        sprintf(buffer, "%s", trozos[dir]);
        printf("%s\n", buffer);
        if ((directorio = opendir(buffer)) == NULL) {
            perror(fLS);
            close = 1;
        }
    }
    if (close == 0) {
        while ((file_info = readdir(directorio)) != NULL) { //Bucle de lectura del directorio
            if ((arg_a == 1) || (file_info->d_name[0] != '.')) { //Para imprimir ocultos [-a]
                printf(" %s ", file_info->d_name);
                sprintf(aux, "%s/%s", buffer, file_info->d_name);
                lstat(aux, &datosArchivos);

                if ((arg_r == 1) && (S_ISDIR(datosArchivos.st_mode)) && (file_info->d_name[0] != '.')) {
                    dirrec[numdir] = strdup(aux);
                    numdir++;
                }

                if (arg_s == 0) { //Imprimir información detallada [-s]

                    printf("%lu %lu ", datosArchivos.st_ino, datosArchivos.st_blocks / 2);

                    //Impime Tipo y Permisos
                    a_permisos = (char*) malloc(16 * sizeof (char));
                    ConvierteModo(datosArchivos.st_mode, a_permisos);
                    printf("%s", a_permisos);
                    free(a_permisos);

                    printf(" %d", datosArchivos.st_nlink);

                    //Detalles de usuario y grupo
                    if ((pwduser = getpwuid(datosArchivos.st_uid)) == NULL) {
                        printf("%d", datosArchivos.st_uid);
                    } else {
                        printf(" %s", pwduser->pw_name);
                    }

                    if ((pwdgroup = getpwuid(datosArchivos.st_gid)) == NULL) {
                        printf("%d", datosArchivos.st_gid);
                    } else {
                        printf(" %s", pwdgroup->pw_name);
                    }

                    printf(" %d", datosArchivos.st_gid);
                    printf(" %lu", datosArchivos.st_size);

                    ptr = ctime(&datosArchivos.st_mtime);
                    printf(" %s", ptr);

		    //Obtenemos la informacion en caso de que el archivo sea link
                    if (S_ISLNK(datosArchivos.st_mode)) {
                        len = readlink(file_info->d_name, buf, sizeof (buf) - 1);
                        buf[len] = '\0';
                        printf(" -> %s\n", buf);
                    }
                }
                printf("\n");
            }
        }
        closedir(directorio);

    }

    while (i < numdir) { //While para el list recursivo [-r]
        myls(dirrec, arg_a, arg_s, arg_r, i);
	free(dirrec[i]);  //free para liberar la memoria reserveda por strdup
        i++;
    }
}

void args_list(char ** trozos, int num_elementos) {

    //Pasamos los argumentos de entrada a booleans para llamar a la funcion myls (list)
    int i = 1;
    int a = 0;
    int s = 0;
    int r = 0;
    int dir = -1;


    while (i < num_elementos) {
        if ((s == 0) && ((strcmp(trozos[i], "-s") == 0))) {
            s = 1;
        }
        else {
            if ((r == 0) && ((strcmp(trozos[i], "-r") == 0))) {
                r = 1;
            } else {
                if ((a == 0) && ((strcmp(trozos[i], "-a") == 0))) {
                    a = 1;
                } else {
                    if (dir == -1) {
                        dir = i;
                    }
                }
            }
        }
        i++;
    }
    myls(trozos, a, s, r, dir);
}

int main() {

    int salir = 0;
    int num_elementos;

    char cadena_origen[256];
    char* elementos_cadena[256];



    while (salir == 0) {

        printf("$");
        fgets(cadena_origen, 256, stdin);
        num_elementos = TrocearCadena(cadena_origen, elementos_cadena);


        if (num_elementos == 0) {
        }
            //Establecemos que el programa finalice
        else if ((strcmp(elementos_cadena[0], "quit") == 0) || (strcmp(elementos_cadena[0], "fin") == 0) || (strcmp(elementos_cadena[0], "exit") == 0)) {
            salir = 1;
        }
            //Accion:Mostrar Autores
        else if (strcmp(elementos_cadena[0], fAUTORES) == 0) {
            mylogin();
        }            //Accion: Obtener PID
        else if (strcmp(elementos_cadena[0], fPID) == 0) {
            mypid();
        }
            //Accion:Cambiar Directorio o Mostrar Actual
        else if ((strcmp(elementos_cadena[0], fDIR) == 0)) {
            if (num_elementos > 1) {
                mycdir(elementos_cadena, num_elementos);
            } else {
                mypwd();
            }
        }
            //Accion:Eliminar Archivo
        else if (strcmp(elementos_cadena[0], fDEL) == 0) {

            if (num_elementos > 1)
                mydelete(elementos_cadena[1]);
            else
                perror(fDEL);
        }
            //Accion:Eliminar Directorio
        else if (strcmp(elementos_cadena[0], fDELD) == 0) {
            if (num_elementos > 2){
                if (strcmp(elementos_cadena[2], "-f") == 0)
                    myrdir(elementos_cadena[1],1);
                else
                    myrdir(elementos_cadena[1],0);
            }
            else if (num_elementos > 1)
                myrdir(elementos_cadena[1], 0);
            else
                perror(fDELD);
        }
            //Accion:Listar Directorio
        else if (strcmp(elementos_cadena[0], fLS) == 0) {
            args_list(elementos_cadena, num_elementos);
        }
        else {
            printf("%s : No se ha encontrado la orden\n", elementos_cadena[0]);
        }

    } //FIN BUCLE
    return 0;
}
