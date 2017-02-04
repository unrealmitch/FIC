#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listaprocesos.h"
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>

proceso *crearLista2p() {
	return NULL;
}

proceso *addLista2p(proceso *p, int pro_pid,char *nombre,char * tiempo,int prioridad,int estado) {

   proceso *aux;
   proceso *pro;

   aux = (proceso *) malloc(sizeof (proceso));
   aux->nombre = (char *) malloc (sizeof (char)*(strlen(nombre)+1));
   aux->tiempo = (char *) malloc (sizeof (char)*(strlen(tiempo)+1));	

	aux->pid = pro_pid;
   strcpy(aux->nombre,nombre);
   strcpy(aux->tiempo,tiempo);
   aux->prioridad = prioridad;
   aux->estado = estado;
   aux->sig = NULL;
	
   if (p == NULL) {
      p = aux;
   }
   else {
      pro = p;
      while (pro->sig != NULL) {
         pro = pro->sig;
      }
      pro -> sig = aux;
   }
   return p;
}

proceso *delLista2p(proceso *lista,proceso *borrar){

   proceso *newlista;
   proceso *temp = NULL;
   proceso *pactual;

   pactual = lista;
   newlista = lista;

   if( pactual != NULL){
      if (pactual != borrar){

         while ( (pactual->sig != NULL) && (pactual->sig != borrar) ){
            temp=pactual;
            pactual = pactual->sig;
         }

         if(pactual->sig != NULL){ //Caso elemento intermedio
            temp = pactual->sig;
            pactual->sig = temp->sig;
         } else if (pactual == borrar){ //Caso elemento final
            temp->sig = NULL;
            temp = pactual;
         } else {
            temp=NULL; //No se ha encontrado el elemento
         }
      } else { //Caso elemento primero
         temp = pactual;
         newlista = temp->sig;
      }
   
      if(temp!=NULL){
         free(temp->nombre);
         free(temp->tiempo);
         free(temp);
      }
   }
   return newlista;
}  


void clearLista2p(proceso **l){ 

   proceso *aux;

   if (*l == NULL) {
   }
   else {
      while (*l != NULL){
         aux = (*l);
         (*l) = (*l)->sig;
         free(aux->nombre);
         free(aux->tiempo);
         free(aux);
      }
   }
}  

void printprocess(proceso* p){

   printf("%5d %4d %s ",p->pid, p->prioridad, p->nombre);
   if(p->estado==ACTIVO){ printf("ACTIVO");}
   else if(p->estado==PARADO){ printf("PARADO");}
   else if(p->estado==TSENAL){ printf("SIGNAL");}
   else if(p->estado==TNORMAL){ printf("TERMINADO");}
   printf(" %s", p->tiempo);
}

proceso* refreshLista2p(proceso* l){
   
   proceso * aux;
   int estado;
   aux = l;
   int new_prio;

   while (aux != NULL){  
   // WNOHANG :No esperar por un hijo que esta en ejecución.
   //WUNTRACED :No esperar si el hijo está parado a no ser que este siendo trazado.
   //WCONTINUED :Volver si un hijo ha continuado ejecutándose tras mandarle la señal
      new_prio = getpriority(PRIO_PROCESS, aux->pid);
      if(aux->prioridad != new_prio ){
         aux->prioridad = new_prio;
      }
      int valor = waitpid (aux->pid, &estado, WNOHANG | WUNTRACED | WCONTINUED);
      if (valor == 0) { /*Non se produciu ningún cambio*/ }
      else{ 
         if (valor == -1){ 
         }
         else{
            if (aux->pid == valor) {
               //Valor = pid del proceso que cambio de estado.
               if (WIFEXITED (estado)) {
                  //terminado normalmente
                  aux->estado = TNORMAL;
               }
               else{
                  if (WIFSIGNALED(estado)) {
                   //terminado por señal
                     aux->estado = TSENAL;
                  }
                  else{
                     if (WIFSTOPPED(estado)) {
                        //parado
                        aux->estado = PARADO;
                     }
                     else{
                        aux->estado = ACTIVO;
                     }
                  }    
               }            
            }
         }
      }
      aux = aux -> sig;
   }
   return l;
}
