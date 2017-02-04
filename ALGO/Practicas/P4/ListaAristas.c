#include "ListaAristas.h"

	/*************************************************************/
	void crear_lista(lista *l){
		 
		 nodo* tmp; 
		 tmp = (nodo*) malloc(sizeof(struct nodo1));
		 if ((tmp == NULL)) {
			  printf("memoria agotada\n");
			  exit(EXIT_FAILURE);
		 }
		 tmp->siguiente = NULL;
		 (*l).cabeza = tmp;
	}


	/*************************************************************/
	int lista_vacia(lista l){
		 return (l.cabeza->siguiente == NULL);
	}


	/*************************************************************/
	void mostrar(lista l){
	  nodo * aux;
	  
		  aux = l.cabeza->siguiente;
		  while(aux!=NULL){
		  	printf("(%d , %d , %d)\n",aux->elemento.x,aux->elemento.y,aux->elemento.peso);
		  	aux = aux->siguiente;
		}
	}
	
	/*************************************************************/
	int insertar(arista x, lista *l){
	  nodo * tmp = (nodo *) malloc(sizeof(struct nodo1));
	  if (tmp == NULL) {
		return 0;
	  }
	  tmp->elemento = x;
	  tmp->siguiente = (*l).cabeza->siguiente;
	  if((*l).cabeza->siguiente==NULL) (*l).ultimo = tmp;
	  (*l).cabeza->siguiente = tmp;
	  
	  return 1;
	}


	/*************************************************************/
	void BorrarLista(lista *l){
		free((*l).cabeza);
		free((*l).ultimo);
		free(l);

	}
	
	/*************************************************************/
	void VaciarLista(lista *l){ 
	   nodo * aux;
	   nodo *aux2;
	   aux = (*l).cabeza->siguiente;
		
	   if (aux == NULL) {
	      perror("Lista vacia");
	   }
	   else {
	      while (aux != NULL){
		 aux2=aux;
		 aux = aux->siguiente; 
		 free(aux2);
	      }
		  (*l).cabeza = NULL;
		  (*l).ultimo = NULL;
	   }
	} 

