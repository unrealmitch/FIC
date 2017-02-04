#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mmap.h"
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/mman.h>


pmmap* crearListaMmap() { // Inicializa a NULL
	return NULL;
}

pmmap *insertarListaMmap(pmmap *l, void *dir, int tam, char * fichero, char *tiempo, int descr) {

   pmmap *aux;
   pmmap *p;

   aux = (pmmap *) malloc(sizeof (pmmap));
   aux->dir = (void *) dir;		
   aux->tam = tam;
   aux-> tiempo = strdup(tiempo);
   aux->descr = descr;
   aux->fichero = strdup(fichero);
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

void imprimirMmap(pmmap* l){

   printf("%p %d %d %s",l->dir, l->tam,l->descr, l->fichero);
   printf(" %s", l->tiempo);
}

void imprimirListaMmap(pmmap *l){
   pmmap *aux;
   aux = l;

   printf(" LISTA MMAP \n");
   if (aux == NULL) {
      printf("La lista esta vacia\n");
   }
   else{
      while ( aux != NULL ) {
         imprimirMmap(aux);
         aux= aux->sig;
      }		
   }
}

pmmap* borrarListaMmap(pmmap *l, char * fich){

	pmmap * anterior, * aux;
	anterior = l;
	aux = l;
	if (aux->sig == NULL) { 
		if (strcmp(aux->fichero, fich)==0) { //Eliminamos el unico nodo que hay
			l = NULL;
			anterior = NULL;
			if (munmap(aux->dir,aux->tam) == -1) {
				perror("munmap");
            return l;
         }
         free (aux->fichero);
 			free (aux->tiempo);
			free(aux);
			aux = NULL;
		}
	}
	else {
		while (aux != NULL) {
			if (strcmp(aux->fichero,fich)==0) {
				if (aux==anterior) {
					//es el primero de la lista
					l = aux->sig;
					anterior = l;
			      if (munmap(aux->dir,aux->tam) == -1) {
				      perror("munmap");
                  return l;
               }
		 			free (aux->tiempo);
               free (aux->fichero);
					free (aux);
					aux = l;
				}
				else {
					//No es el primero de la lista
					anterior -> sig = aux -> sig;
			      if (munmap(aux->dir,aux->tam) == -1) {
				      perror("munmap");
                  return l;
               }
		 			free (aux->tiempo);
               free (aux->fichero);
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

pmmap* borrarListaMmapDir(pmmap *l, char * dirdelete){

   pmmap * anterior, * aux;
   anterior = l;
   aux = l;
   char dirstring[64];


   if (aux != NULL){
      if (aux->sig == NULL) {
      sprintf(dirstring,"%p",aux->dir);
         if (strcmp(dirstring, dirdelete) == 0) { //Eliminamos el unico nodo que hay
            l = NULL;
            anterior = NULL;
            if (munmap(aux->dir,aux->tam) == -1) {
               perror("munmap");
               return l;
            }
            free (aux->fichero);
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
                  if (munmap(aux->dir,aux->tam) == -1) {
                     perror("munmap");
                     return l;
                  }
                  free (aux->tiempo);
                  free (aux->fichero);
                  free (aux);
                  aux = l;
               }
               else {
                  //No es el primero de la lista
                  anterior -> sig = aux -> sig;
                  if (munmap(aux->dir,aux->tam) == -1) {
                     perror("munmap");
                     return l;
                  }
                  free (aux->tiempo);
                  free (aux->fichero);
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

void vaciarListaMmap(pmmap **l){

   pmmap *aux;

   if(*l != NULL){
      while(*l != NULL){
         aux = (*l);
         (*l) = (*l)->sig;
			if (munmap(aux->dir,aux->tam) == -1) {
				perror("munmap");
         }
         free(aux->fichero);
         free(aux->tiempo);
         free(aux);
      }
   }
}
