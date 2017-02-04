#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tmalloc.h"
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>


pmmalloc* crearListaMalloc() { // Inicializa a NULL
	return NULL;
}

pmmalloc *insertarListaMalloc(pmmalloc *l, void *dir, char *tiempo, int tam) {

   pmmalloc *aux;
   pmmalloc *p;

   aux = (pmmalloc *) malloc(sizeof (pmmalloc));
   aux->dir = dir;		
   aux->tiempo = (char *) malloc (sizeof (char)*(strlen(tiempo)+1));
	
   aux->tam = tam;
   strcpy(aux->tiempo,tiempo);
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

void imprimirMalloc(pmmalloc* l){

   printf("%p %d",l->dir, l->tam);
   printf(" %s", l->tiempo);
}

void imprimirListaMalloc(pmmalloc *l){
   pmmalloc *aux;
   aux = l;

   printf(" LISTA MALLOC \n");
   if (aux == NULL) {
      printf("La lista esta vacia\n");
   }
   else{
      while ( aux != NULL ) {
         imprimirMalloc(aux);
         aux= aux->sig;
      }		
   }
}

pmmalloc* borrarListaMalloc(pmmalloc *l, int tam){

	pmmalloc * anterior, * aux;
	anterior = l;
	aux = l;

	if (aux != NULL){
		if (aux->sig == NULL) { 

			if (aux->tam == tam) { //Eliminamos el unico nodo que hay
				l = NULL;
				anterior = NULL;
				free (aux->dir);
	 			free (aux->tiempo);
				free(aux);
				aux = NULL;
			}
		}
		else {
			while (aux != NULL) {
				if (aux->tam== tam) {
					if (aux==anterior) {
						//es el primero de la lista
						l = aux->sig;
						anterior = l;
						free (aux->dir);
			 			free (aux->tiempo);
						free (aux);
						aux = l;
					}
					else {
						//No es el primero de la lista
						anterior -> sig = aux -> sig;
						free (aux->dir);
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

pmmalloc* borrarListaMallocDir(pmmalloc *l, char * dirdelete){

	pmmalloc * anterior, * aux;
	anterior = l;
	aux = l;

	char dirstring[64];


	if (aux != NULL){
		if (aux->sig == NULL) { 
			sprintf(dirstring,"%p",aux->dir);
			if (strcmp(dirstring, dirdelete) == 0) { //Eliminamos el unico nodo que hay
				l = NULL;
				anterior = NULL;
				free (aux->dir);
	 			free (aux->tiempo);
				free(aux);
				aux = NULL;
			}
		}
		else {
			while (aux != NULL) {
				sprintf(dirstring,"%p",aux->dir);
				if (strcmp(dirstring, dirdelete) == 0) {
					if (aux==anterior) {
						//es el primero de la lista
						l = aux->sig;
						anterior = l;
						free (aux->dir);
			 			free (aux->tiempo);
						free (aux);
						aux = l;
					}
					else {
						//No es el primero de la lista
						anterior -> sig = aux -> sig;
						free (aux->dir);
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

void vaciarListaMalloc(pmmalloc **l){

   pmmalloc *aux;

   if(*l != NULL){
      while(*l != NULL){
         aux = (*l);
         (*l) = (*l)->sig;
         free(aux->dir);
         free(aux->tiempo);
         free(aux);
      }
   }
}


