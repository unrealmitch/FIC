/*	UDC:	Sistemas Operativos
 * 	Pract:  2ª
 * 	Autor:	Miguel Mosquera Perez
 * 	Fecha: 	03/10/2013
 * 	Grupo: 	4.2
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
#include "listaprocesos.h"

const char * fAUTORES = "autores";
const char * fPID = "getpid";
const char * fDIR = "cdir";
const char * fLS = "list";
const char * fDEL = "delete";
const char * fDELD = "rdir";

const char * fPriority= "priority";
//priority [pid [valor]]

const char * fFork = "fork";
//fork[]d
const char * fExec = "exec";
//exec [@prio] prog arg1
const char * fSPlano = "splano";
//splano [@prio] prog arg1
const char * fPPlano = "pplano";
//pplano [@prio] prog arg1
const char * fExecpri = "execpri"; 
//execpri prio prog arg1
const char * fSPlanopri = "splanopri";
//splanopri prio prog arg1
const char * fPPlanopri = "pplanopri";
//pplanopri prio prog arg1
const char * fexec2 = "prog";
//[@prio] prog arg1
const char * fjobs = "jobs";
//jobs [all|term|sig|stop|act]
//jobs pid
const char * fDelJob = "deljobs";
//deljobs [all|term|sig|stop|act]
const char * fFG = "fg";

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

void myprio(int pid, int prio, int set){
	int newprio = 0;

	if(set){
		if((setpriority(PRIO_PROCESS,pid,prio))==-1){
			perror(fPriority);
		}
	}

	if ((newprio = getpriority(PRIO_PROCESS,pid))==-1){
		perror(fPriority);
	}else{
		printf("Priority of process %d : %d\n", pid, newprio);
	}
}


void pid(){
	printf("PID of shell: %d\n",getpid());
    printf("PID of father: %d\n",getppid());
}

int myfork(){
	pid_t sonpid;
	
	sonpid=fork();

   if(sonpid == -1){
      perror("FORK");
      return -1;
   }else {
		if (sonpid==0){
			printf("Son Process\n");
			return 1;
		}else {
			waitpid(sonpid,NULL,0);
			return sonpid;
		}
	}
}

int myfork2p(){
	pid_t sonpid = fork();
 	int num;

	if(sonpid == -1){
    	perror(fFork);
    	return -1;
   } else {
	   	if (sonpid == 0){
			return 1;
		}
	   	else{
	    	waitpid(sonpid,&num,WNOHANG|WUNTRACED|WCONTINUED);
	    	return sonpid;
	    }
	}
}

void exec(char** elementos_cadena, int num_elementos, int prio){
	if (num_elementos > 1){
	   //Establecemos la prioridad en caso de que esta
	   //se pase por parametro (@x)
	   if(prio > -1){
	      setpriority(PRIO_PROCESS,getpid(),prio);
	   }
	   
	   if(execvp(elementos_cadena[1],elementos_cadena+1) == -1){
	      perror(fExec);
	   }
	} else {
		perror(fExec);
	}
}

void splano(char** elementos_cadena, int num_elementos, proceso** lista2p, int prio){
	if(num_elementos > 1){

	   	time_t timeP;   
	   	int sonpid = myfork2p();
	   	char *name = (char *) malloc(sizeof(char)*1024);
	   	char *hour = (char *) malloc(sizeof(char)*1024);

	   	if(sonpid==-1){
	    	  perror(fFork);
	   	} else if(sonpid == 1){
	        exec(elementos_cadena, num_elementos,prio);
	      	}else{
	        	if (prio < 0) {
	        		prio = getpriority(PRIO_PROCESS, sonpid);
	        	}

	        	//La hora de inicio del proceso
	   			timeP = time(NULL);;
	   			strcpy(hour,ctime(&timeP));
	         	name = strcpy(name,elementos_cadena[1]);

	         	//Añadimos argumentos
	         	int i;
	         	for(i = 2; i < num_elementos; i++){
	            	name = strcat(name, " ");
	            	name = strcat(name, elementos_cadena[i]);
	         	}
	         //Añadimos a la lista el proceso y su informacion	
	         *lista2p = addLista2p(*lista2p, sonpid, name, hour, prio, 3);

	         free(name);
	         free(hour);
	     }
	}else{
		perror(fSPlano);
	}
}

int getPrioParam(char** elementos_cadena, int* num_elementos, int filtro){
	//Filtro: 0-> Prioridad pasada sin @ para "func"prio
	//Filtro: 1-> Prioridad pasada con @ para "func" @prio
	//Filtro: 2-> Prioridad con @ para @prio prog

	int i,prio = 0;
	if(filtro < 2){
		
		if( (filtro==0) || (elementos_cadena[1][0] == '@') ) {

			prio = atoi (&elementos_cadena[1][filtro]);

			for(i = 1;i<((*num_elementos)-1);i++){
				elementos_cadena[i] = elementos_cadena[i+1];
			}
			
			*num_elementos = (*num_elementos) - 1;
			elementos_cadena[*num_elementos] = NULL;
			
		   	return prio;
		}else{
			return -1;
		}
	} else if (elementos_cadena[0][0] == '@'){
		prio = atoi (&elementos_cadena[0][1]);

		for(i = 0;i<((*num_elementos)-1);i++){
			elementos_cadena[i] = elementos_cadena[i+1];
		}
			
		*num_elementos = (*num_elementos) - 1;
		elementos_cadena[*num_elementos] = NULL;

		return prio;
	} else{
		return -1;
	}
}

void pplano(char** elementos_cadena, int num_elementos, int prio, int tipo){
	//Tipo 0-> [@prio] programa arg1 arg2... 
	//Tipo 1-> pplano [@prio] programa arg1 arg2...

	int pid = fork();
	if (tipo>1){
		perror("Tipo para pplano no definido");
		return;
	}

	if (pid == -1){
		perror(fexec2);
	}else{
		if(pid==0){

		   //Establecemos la prioridad en caso de que esta
		   //se pase por parametro (@x)
		   if(prio > -1){
		      setpriority(PRIO_PROCESS,getpid(),prio);
		   }

		   	if(execvp(elementos_cadena[tipo],elementos_cadena+tipo) == -1){
		      	perror(elementos_cadena[tipo]);
		      	exit(0);
		   	} 
		}else{
			waitpid(pid,NULL,0);
		}
	} 
}

int StateToInt(char* elemento_cadena){
	int ebuscado = -1;
			
	if(strcmp(elemento_cadena,"all")==0){
		ebuscado = -1;
	}
		else if(strcmp(elemento_cadena,"term")==0){
		ebuscado = 0;
	}
		else if(strcmp(elemento_cadena,"sig")==0){
		ebuscado = 1;
	}
		else if(strcmp(elemento_cadena,"stop")==0){
		ebuscado = 2;
	}
	else if(strcmp(elemento_cadena,"act")==0){
		ebuscado = 3;
	}
	else{
		ebuscado = -2;
	}

	return ebuscado;
}

void procesos(char** elementos_cadena, int num_elementos, proceso* lista2p){
	proceso *temp;
	temp = lista2p;
	int ebuscado = -1;

	if (num_elementos > 1) {ebuscado = StateToInt(elementos_cadena[1]);}

	printf("Lista de procesos en 2do plano:\n");
	printf("PID\t PRIO \t Comando \t Inicio \t Estado\n");
	
	while(temp != NULL){
		if( (temp->estado == ebuscado) || (ebuscado == -1) ){
			printf("%i \t %i \t %-15s %-15s %i\n", temp->pid, temp->prioridad, temp->nombre, temp->tiempo, temp->estado);
		}
		temp = temp->sig;
	}
}

void procesospid(char** elementos_cadena, int num_elementos, proceso* lista2p){
	proceso *temp;
	temp = lista2p;

	char *search_pid = elementos_cadena[1];
	int notfound = 1;
	char *pid = (char *) malloc(sizeof(char)*1024);

	while(temp != NULL){
		itoa(temp->pid,pid);
		if( strcmp(search_pid, pid) ==0 ) {
			printf("PID\t PRIO \t Comando \t Inicio \t\t Estado\n");
			printf("%i \t %i \t %-15s %-10s %i\n", temp->pid, temp->prioridad, temp->nombre, temp->tiempo, temp->estado);
			notfound = 0;
			break;
		}
		temp = temp->sig;
	}

	if (notfound){
		printf("Proceso con pid %s no encontrado. \n",search_pid);
	}
	free(pid);
}

proceso *borraprocesos(char** elementos_cadena, int num_elementos, proceso* lista2p){
	proceso *temp;

	proceso *newlista;

	newlista=lista2p;
	temp = lista2p;
	int ebuscado = -1;

	if (num_elementos > 1) {ebuscado = StateToInt(elementos_cadena[1]);}
	
	while(temp != NULL){
		if( (temp->estado == ebuscado) || (ebuscado == -1) ){
			newlista=delLista2p(newlista,temp);
			temp=temp->sig;
		}
	}

	return newlista;
}

void FG(int pid, proceso* l){

   proceso* aux;

   if(pid != 0){
      struct rusage usage;
      int status;   

      int wpid = wait4(pid,&status,WCONTINUED|WUNTRACED,&usage);

      if(wpid == -1){
         perror("wait4");
      }
      else{
         aux=refreshLista2p(l);
         while ( (aux != NULL) && (aux->pid != wpid) ){
            aux=aux->sig;
         }

         if(aux!=NULL){
            printprocess(aux);
            if (WIFEXITED(status)) {
               printf("TERMINADO, ESTADO=%d\n", WEXITSTATUS(status));
               printf("CONSUMO: Tiempo CPU (USER): %lu microsegundos\n", usage.ru_utime.tv_usec);
               printf("Tiempo CPU(KERNEL): %lu microsegundos\n",usage.ru_stime.tv_usec);
               printf("Memoria (Max): %lu KB \n", usage.ru_maxrss);
            }
            else{
               if (WIFSTOPPED(status)) {
//                  printf("PARADO, ESTADO=%d\n", WSTOPSIG(status));
               }  
               else{
                  if (WIFSIGNALED(status)) {
                     printf("TERMINADO POR SEÑAL, ESTADO=%d\n", WTERMSIG(status));
                     printf("CONSUMO: Tiempo CPU (USER): %lu microsegundos\n", usage.ru_utime.tv_usec);
                     printf("Tiempo CPU(KERNEL): %lu microsegundos\n",usage.ru_stime.tv_usec);
                     printf("Memoria (Max): %lu KB \n", usage.ru_maxrss);
                  }
                  else{
//                     printf("ACTIVO\n");
                  }
               }            
            }

         }
         else{
            printf("Proceso no encontrado\n");
         }
      }
   }
   else 
      perror(fFG);
}

int main(){

   int salir=0;
   int num_elementos=0;

	char cadena_origen[256];
	char* elementos_cadena[256];

	proceso *lista2p;
	lista2p = crearLista2p();

	int prio;
	int ebuscado;
   
	while(salir==0){

	prio=0;
	ebuscado=-1;
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
			
			//Function priority
		   	else if(strcmp(elementos_cadena[0],fPriority)==0){
				if (num_elementos == 1){
					myprio(getpid(),0,0);
				} else if (num_elementos == 2){
					myprio(atoi(elementos_cadena[1]),0,0);
				} else {
					myprio(atoi(elementos_cadena[1]),atoi(elementos_cadena[2]),1);
				}
			}
		
			//Function fork
			else if(strcmp(elementos_cadena[0],fFork)==0){
				myfork();
			}
			
			//Function exec
			else if(strcmp(elementos_cadena[0],fExec)==0){
				prio = getPrioParam(elementos_cadena,&num_elementos,1);
				exec(elementos_cadena,num_elementos,prio);
			}

			//Funcion splano
			else if(strcmp(elementos_cadena[0],fSPlano)==0){
				prio = getPrioParam(elementos_cadena,&num_elementos,1);
				splano(elementos_cadena,num_elementos,&lista2p,prio);
			}

			//Funcion pplano
			else if(strcmp(elementos_cadena[0],fPPlano)==0){
				prio = getPrioParam(elementos_cadena,&num_elementos,1);
				pplano(elementos_cadena,num_elementos,prio,1);
			}

			//Funcion jobs
			else if(strcmp(elementos_cadena[0],fjobs)==0){
				lista2p=refreshLista2p(lista2p);
				if (  (num_elementos > 1) ){
					ebuscado = StateToInt(elementos_cadena[1]);
				}
				if (ebuscado == -2) {
					procesospid(elementos_cadena,num_elementos,lista2p);
				}else{
					procesos(elementos_cadena,num_elementos,lista2p);
				}
			}		

			//Funcion deljobs
			else if(strcmp(elementos_cadena[0],fDelJob)==0){
				lista2p = borraprocesos(elementos_cadena,num_elementos,lista2p);
			}		
			//Funcion fg
			else if(strcmp(elementos_cadena[0],fFG)==0){
				lista2p=refreshLista2p(lista2p);
            	if(elementos_cadena[1]!= NULL){
               		int pid = atoi (elementos_cadena[1]);
               		FG(pid, lista2p);
            	}else{
               		perror(fFG);
            	}
         	}

         	//Funciones con pri

         	//Function exec
			else if(strcmp(elementos_cadena[0],fExecpri)==0){
				prio = getPrioParam(elementos_cadena,&num_elementos,0);
				exec(elementos_cadena,num_elementos,prio);
			}

			//Funcion splano
			else if(strcmp(elementos_cadena[0],fSPlanopri)==0){
				prio = getPrioParam(elementos_cadena,&num_elementos,0);
				splano(elementos_cadena,num_elementos,&lista2p,prio);
			}

         	//Funcion pplanopri
			else if(strcmp(elementos_cadena[0],fPPlanopri)==0){
				prio = getPrioParam(elementos_cadena,&num_elementos,0);
				pplano(elementos_cadena,num_elementos,prio,1);
			}
			//Funcion prog
			else {
				prio = getPrioParam(elementos_cadena,&num_elementos,2);
				pplano(elementos_cadena,num_elementos,prio,0);
			}


		}

   }
   clearLista2p(&lista2p);
   return 0;
}
