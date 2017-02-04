/*  UDC:    Sistemas Operativos
 *  Pract:  3ª
 *  Autor:  Miguel Mosquera Perez
 *  Fecha:  20/12/2013
 *  Grupo:  4.2
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
#include <sys/resource.h>
#include <sys/wait.h>
 #include <assert.h>


#include <sys/shm.h>
#include "tmalloc.h"
#include "mmap.h"
#include "shared.h"
#include <fcntl.h>
#include <sys/mman.h>

const char * fAUTORES = "autores";
const char * fPID = "getpid";

const char * fMEM = "mem";
const char * fRKEY = "rmkey";
const char * fDIR = "direcciones";
const char * fMDUMP = "memdump";
const char * fREC = "recursiva";
const char * fUID = "uid";

//Constantes de los autores
const char * AutorNombre1 = "Miguel Mosquera Pérez";
const char * AutorNombre2 = "Manuel Figueras Gago";
const char * AutorLogin1 = "miguel.mosquera.perez@udc.es";
const char * AutorLogin2 = "manuel.figueiras@udc.es";

                            
int Global_1 = 10;
int * Global_2;
char * Global_3 = "Treinta";

// ---Funciones Anteriores---
void mylogin() {
    printf("Login de autores: \n\n");
    printf("- %s : %s\n", AutorNombre1, AutorLogin1);
    printf("\n");
}


void pid(){
    printf("PID of shell: %d\n",getpid());
    printf("PID of father: %d\n",getppid());
}
//# ---Funciones Anteriores---#

// ---Funciones Auxiliares---

void reverse(char* str, int length){
    int i = 0, j = length-1;
    char tmp;
    while (i < j) {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        i++; j--;
    }
}

int itoa(int n, char* out){

    int sign = n < 0? 1: 0;
    int i = 0;
    if (n == 0) {
        out[i++] = '0';
    } else if (n < 0) {
        out[i++] = '-';
        n = -n;
    }
    while (n > 0) {
        out[i++] = '0' + n % 10;
        n /= 10;
    }
    out[i] = '\0';
    reverse(out + sign, i - sign);
    return 0;
}

int TrocearCadena(char * cadena, char * trozos[]){
   int i=1; 
   if ((trozos[0]=strtok(cadena," \n\t"))==NULL)
      return 0;
   while ((trozos[i]=strtok(NULL," \n\t"))!=NULL)
      i++;
   return i;
}

//# ---Funciones Auxiliares--- #

// ---Op. Asignacion ---

pmmalloc* myMalloc(pmmalloc* l, int tam){

    void *bytes = malloc(tam);

    char * hora;
    time_t timeProc = time (NULL);
    hora = strdup(ctime(&timeProc));

    l = insertarListaMalloc(l, bytes, hora, tam);

   free(hora);

   return l;
}

pmmap* myMmap ( pmmap* l, char *fichero, char *tipomap, char * perm) {

   void *p;
   struct stat s;
   int df, protection=0, map=MAP_PRIVATE, modo=O_RDONLY;

   if (fichero==NULL){ 
      imprimirListaMmap(l);
      return l;
   }

   if (tipomap!=NULL){

      if (!strcmp(tipomap,"-s")){
         map=MAP_SHARED;
      } else{
        perm = tipomap;
      }

      if (perm!=NULL && strlen(perm)<4) {
         protection=0;
         if (strchr(perm,'r')!=NULL) 
            protection|=PROT_READ;
         if (strchr(perm,'w')!=NULL) 
            protection|=PROT_WRITE;
         if (strchr(perm,'x')!=NULL) 
            protection|=PROT_EXEC;
      }
   }

   if (protection&PROT_WRITE) 
      modo=O_RDWR;

   if (stat(fichero,&s)==-1 || (df=open(fichero, modo))==-1){ 
      perror ("imposible acceder al fichero"); 
      return l;
   }
   
   if ((p=mmap (NULL,s.st_size, protection,map,df,0)) == MAP_FAILED){ 
      perror ("error mmap");
      close(df); 
      return l; 
   }

   close(df);
   
   char * hora;
    time_t timeProc = time (NULL);
   hora = strdup(ctime(&timeProc));

   l = insertarListaMmap (l, p, s.st_size,fichero, hora ,df);

   free(hora);
      
   return l;
}


pshared* myShared (pshared* l, key_t clave, off_t tam) {

   void * p;
   int aux, id, flags=0777;
   struct shmid_ds s;

   if (tam)
      flags=flags | IPC_CREAT | IPC_EXCL;

   if (clave==IPC_PRIVATE){
      printf("IPC_PRIVATE: error\n");
      return l;
   }

   if ((id=shmget(clave, tam, flags))==-1){
      perror("shmget");
      return l;
   }

   if ((p=shmat(id,NULL,0))==(void*) -1){
      aux=errno;

      if (tam)
         shmctl(id,IPC_RMID,NULL);

      errno=aux;
      perror("shmat");
      return l;
   }

   shmctl (id,IPC_STAT,&s);

   char * hora;
    time_t timeProc = time (NULL);
   hora = strdup(ctime(&timeProc));   

   l = insertarListaShared(l, p, s.shm_segsz, hora, clave);

   free(hora);
   return l;
}

//# ---Op. Asignacion ---#



/* Las operaciones para desasignar memoría 
se encuentran en el código de las listas */


// ---Otras Funciones ---

void myDir(){

    int local_1 = 40;
    int * local_2 = (int *) malloc( sizeof(int) * 1024);
    char * local_3 = "Sesenta";

    Global_2 = (int *) malloc( sizeof(int) * 1024);
    printf("Variables Globales: \n");
    printf("1: %p\n", &Global_1);
    printf("2: %p\n", Global_2);
    printf("3: %p\n", Global_3);

    printf("Variables Locales: \n");
    printf("1: %p\n", &local_1);
    printf("2: %p\n", local_2);
    printf("3: %p\n", local_3);

    printf("Funciones: \n");                            
    printf("myMmap: %p \n", myMmap);
    printf("myDir: %p \n", myDir);
    printf("pid: %p \n", pid);


}
void cmd_rmkey (char * key) {

   key_t clave;
   int id;

   if (key==NULL || (clave=(key_t) strtoul(key,NULL,10))==IPC_PRIVATE){
      printf ("rmkey clave_valida\n");
      return;
   }
   if ((id=shmget(clave,0,0666))==-1){
      perror ("shmget: imposible obtener memoria compartida");
      return;
   }
   if (shmctl(id,IPC_RMID,NULL)==-1)
      perror ("shmctl: imposible eliminar memoria compartida\n");
}

void myDump(char * dir, char * cont){


    int num = 25;
    int dirmem = atoi(dir);
    char dirstring[64];

    if(cont!=NULL){
        num = atoi(cont);
    }

    int i;

    /*He tenido varios problemas al pasar el char* a un int en formato hexadecimal,
    así que finalmente he utilizado un scanf para obtener dicha dirección incumpliendo
    algo el formato designado en la practica.*/
    
    printf("Escriba la direccíon de memoria, sin 0x:");
    //scanf("%x",&dirmem);
	sprintf(dirstring,"%p",dir);
	

    printf("\nDireccion: \t Carácter \t Hex\n");
    for(i=0;i<num;i++)
    {
        char * address;
        address = (char*) (dirstring++);
        printf("%p \t\t", address);   
        printf("%c \t", *address);
        printf("%x \n", *address);                                        
    }
}


void recursiva (int n) {
   char automatico[512];
   static char estatico[512];
   printf ("-------------------------------\n");
   printf ("parametro n:%d en %p\n",n,&n);
   printf ("array estatico en:%p \n",estatico);
   printf ("array automatico en %p\n",automatico);
   printf ("-------------------------------\n");
   
   if (n>0)
      recursiva(n-1);
}

void myuid (char * lng, char * login) {

   struct passwd *pwd;
   int log;

   if(login == NULL){
      if(lng == NULL){
         pwd = getpwuid(geteuid());
         printf("%s %d %s\n", pwd->pw_name, pwd->pw_uid, pwd->pw_gecos );
      }
      else{
         log = atoi(lng);
         if ( setuid(log) == -1){
            perror("setuid");
         }
      }
   }
   else{
      if(strcmp(lng,"-l")==0){
          log = getpwnam(login)->pw_uid;

         if ( setuid(log) == -1) {
            perror("setuid");
         }
      }
   }
}

//# ---Otras Funciones ---#


void options_mem(char** elementos_cadena, int num_elementos,
                 pmmalloc** lmall, pmmap** lmmap, pshared** lsha){

    if (num_elementos < 2){
        printf("Lista Direcciones Asignadas:\n");
        imprimirListaMalloc(*lmall);
        imprimirListaMmap(*lmmap);
        imprimirListaShared(*lsha);
    } else {
        // Asignamos Memoria
        if (strcmp(elementos_cadena[1], "-malloc") == 0){
            if (num_elementos > 2){
                *lmall = myMalloc(*lmall, atoi(elementos_cadena[2]));
            } else {
                imprimirListaMalloc(*lmall);
            }
        }

        else if (strcmp(elementos_cadena[1], "-mmap") == 0){
            if (num_elementos == 2) {
                imprimirListaMmap(*lmmap);
            }
            else if (num_elementos == 3){
                *lmmap = myMmap(*lmmap,elementos_cadena[2],NULL,NULL);
            }
            else if (num_elementos == 4){
                *lmmap =  myMmap(*lmmap,elementos_cadena[2],elementos_cadena[3],NULL);
            }
            else if (num_elementos == 5){
                *lmmap =  myMmap(*lmmap,elementos_cadena[2],elementos_cadena[3],elementos_cadena[4]);
            }
            else{
                perror("Demasiados elementos\n");
            }
        } 
        else if (strcmp(elementos_cadena[1], "-shared") == 0){
            if (num_elementos == 2){
                imprimirListaShared(*lsha);
            }
            else if(num_elementos == 3){
                *lsha = myShared(*lsha, atoi(elementos_cadena[2]), (off_t) NULL);
            }else{
                *lsha = myShared(*lsha, atoi(elementos_cadena[2]), atoi(elementos_cadena[3]));
            }
        }

        // Desasignamos Memoria
        else if (strcmp(elementos_cadena[1], "-deassign") == 0){
            if (num_elementos < 3){
                perror("Argumentos Insuficientes\n");
            }
            else if (strcmp(elementos_cadena[2], "malloc") == 0){
                if (num_elementos == 3){
                    imprimirListaMalloc(*lmall);
                } else{
                    *lmall = borrarListaMalloc(*lmall, atoi(elementos_cadena[3]));
                }
            }
            else if (strcmp(elementos_cadena[2], "mmap") == 0){
                if (num_elementos == 3){
                    imprimirListaMmap(*lmmap);
                } else{
                    *lmmap = borrarListaMmap(*lmmap, elementos_cadena[3]);
                }
            }
            else if (strcmp(elementos_cadena[2], "shared") == 0){
                if (num_elementos == 3){
                    imprimirListaShared(*lsha);
                } else{
                    *lsha = borrarListaShared(*lsha, atoi(elementos_cadena[3]));
                }
            }
            else{
                *lmall = borrarListaMallocDir(*lmall, elementos_cadena[2]);
                *lmmap = borrarListaMmapDir(*lmmap, elementos_cadena[2]);
                *lsha = borrarListaSharedDir(*lsha, elementos_cadena[2]);
            }
        } 
        else{
            printf("Argumento inválido: %s \n",elementos_cadena[1]);
        }
    }
}


int main(){

    int salir=0;
    int num_elementos=0;

    char cadena_origen[256];
    char* elementos_cadena[256];

    pmmalloc *lmalloc;
    pmmap *lmmap;
    pshared *lshared;

    lmalloc=crearListaMalloc();
    lmmap = crearListaMmap();
    lshared = crearListaShared();


    while(salir==0){

    printf("#");

        fgets(cadena_origen,256,stdin);
        num_elementos=TrocearCadena(cadena_origen, elementos_cadena);
        
        if(strcmp(strtok(cadena_origen," "),"\n") != 0){
            
            //Exit shell
            if( (strcmp(elementos_cadena[0],"quit")==0) || (strcmp(elementos_cadena[0],"fin")==0) || (strcmp(elementos_cadena[0],"exit")==0)){
                salir=1;
            }

            //Function pid
            else if(strcmp(elementos_cadena[0],fPID)==0){
                pid();
            }
            
            //Mostrar Autores
            else if (strcmp(elementos_cadena[0], fAUTORES) == 0) {
            mylogin();
            }

            //Funcion MEM
            else if (strcmp(elementos_cadena[0], fMEM) == 0) {
                options_mem(elementos_cadena,num_elementos,&lmalloc,&lmmap,&lshared);
            }

            //Funcion rmkey
            else if (strcmp(elementos_cadena[0], fRKEY) == 0) {
                cmd_rmkey(elementos_cadena[1]);
            }

            else if (strcmp(elementos_cadena[0], fDIR) == 0){
                myDir();
            }
            //Funcion memdump
            else if (strcmp(elementos_cadena[0], fMDUMP) == 0) {
                if (num_elementos > 2) {
                    myDump(elementos_cadena[1],elementos_cadena[2]);
                }else{
                    myDump(elementos_cadena[1],NULL);
                }

            }

            //Funcion recursiva
            else if (strcmp(elementos_cadena[0], fREC) == 0) {
                recursiva(atoi(elementos_cadena[1]));
            }

            //Funcion UID
            else if (strcmp(elementos_cadena[0], fUID) == 0) {
                if(num_elementos != 1){
                    myuid(elementos_cadena[1], elementos_cadena[2]);
                }else{
                    myuid(NULL, NULL);         
                }
            }

            //No Encontrada
            else{
                printf("No se reconoce: %s \n", elementos_cadena[0]);
            }
        }
   }

   vaciarListaMalloc(&lmalloc);
   vaciarListaMmap(&lmmap);
   vaciarListaShared(&lshared);

   return 0;
}