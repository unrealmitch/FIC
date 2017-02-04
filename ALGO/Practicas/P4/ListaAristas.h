#include <stdlib.h>
#include <stdio.h>
#include <string.h>


     typedef struct {
          int x, y, peso;
     } arista;

     typedef int ** matriz;
     
     typedef arista tipoElemento;
     
     typedef struct nodo1{
          tipoElemento elemento;
          struct nodo1* siguiente;
     } nodo;
      
     typedef struct {
          nodo *cabeza;
          nodo *ultimo;
     } lista;
     
      
void crear_lista(lista*);
void BorrarLista(lista *);
int lista_vacia(lista);
int insertar(arista, lista*);
void mostrar(lista);
void VaciarLista(lista *);

