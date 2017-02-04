#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shared.h"
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/shm.h>


pshared *crearListaShared() { // Inicializa a NULL
	return NULL;
}

pshared *insertarListaShared(pshared *l, void *dir, int tam, char *tiempo, key_t key) {

   pshared *aux;
   pshared *p;

   aux = (pshared *) malloc(sizeof (pshared));
   aux->dir = (void *) dir;		
   aux->tam = tam;
   aux->key = key;
   aux->tiempo = strdup(tiempo);
   aux->sig = NULL;
	
   if (l == NULL) {
      l = aux;
   }
   else {
      p = l;
      while (p->sig != NULL) {
         p = p->sig;
      }
      p -> sig = aux;
   }
   return l;
}

void imprimirShared(pshared* l){

   printf("%p %d %d",l->dir, l->tam, l->key);
   printf(" %s", l->tiempo);
}

void imprimirListaShared(pshared *l){
   pshared *aux;
   aux = l;

   printf(" LISTA SHARED \n");
   if (aux == NULL) {
      printf("La lista esta vacia\n");
   }
   else{
      while ( aux != NULL ) {
         imprimirShared(aux);
         aux= aux->sig;
      }		
   }
}

pshared* borrarListaShared(pshared *l, int tam){

	pshared * anterior, * aux;
	anterior = l;
	aux = l;
	if (aux->sig == NULL) { 
		if (aux->tam==tam) { //Eliminamos el unico nodo que hay
			l = NULL;
			anterior = NULL;
			if (shmdt(aux->dir) == -1){
				perror("shmdt");
            return l;
         }
 			free (aux->tiempo);
			free(aux);
			aux = NULL;
		}
	}
	else {
		while (aux != NULL) {
			if (aux->tam==tam) {
				if (aux==anterior) {
					//es el primero de la lista
					l = aux->sig;
					anterior = l;
			      if (shmdt(aux->dir) == -1){
				      perror("shmdt");
                  return l;
               }
		 			free (aux->tiempo);
					free (aux);
					aux = l;
				}
				else {
					//No es el primero de la lista
					anterior -> sig = aux -> sig;
			      if (shmdt(aux->dir) == -1){
				      perror("shmdt");
                  return l;
               }
		 			free (aux->tiempo);
					free (aux);
					aux = anterior -> sig;
				}
			}
			else {
				//Este nodo no se elimina. se sigue recorriendo la lista
				anterior = aux;
				aux = aux->sig;
			}
		}
	}
	return l;
}

pshared* borrarListaSharedDir(pshared *l, char * dirdelete){

   pshared * anterior, * aux;
   anterior = l;
   aux = l;
   char dirstring[64];


   if (aux != NULL){
      if (aux->sig == NULL) { 
         sprintf(dirstring,"%p",aux->dir);
         if (strcmp(dirstring, dirdelete) == 0) { //Eliminamos el unico nodo que hay
            l = NULL;
            anterior = NULL;
            if (shmdt(aux->dir) == -1){
               perror("shmdt");
               return l;
            }
            free (aux->tiempo);
            free(aux);
            aux = NULL;
         }
      }
      else {
         while (aux != NULL) {
            if (strcmp(dirstring, dirdelete) == 0) {
			sprintf(dirstring,"%p",aux->dir);
               if (aux==anterior) {
                  //es el primero de la lista
                  l = aux->sig;
                  anterior = l;
                  if (shmdt(aux->dir) == -1){
                     perror("shmdt");
                     return l;
                  }
                  free (aux->tiempo);
                  free (aux);
                  aux = l;
               }
               else {
                  //No es el primero de la lista
                  anterior -> sig = aux -> sig;
                  if (shmdt(aux->dir) == -1){
                     perror("shmdt");
                     return l;
                  }
                  free (aux->tiempo);
                  free (aux);
                  aux = anterior -> sig;
               }
            }
            else {
               //Este nodo no se elimina. se sigue recorriendo la lista
               anterior = aux;
               aux = aux->sig;
            }
         }
      }
   }
   return l;
}

void vaciarListaShared(pshared **l){

   pshared *aux;

   if(*l != NULL){
      while(*l != NULL){
         aux = (*l);
         (*l) = (*l)->sig;
			if (shmdt(aux->dir) == -1){
				perror("shmdt");
         }
         free(aux->tiempo);
         free(aux);
      }
   }
}
