///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* PROGRAMA PRINCIPAL 
   Author: JOSE PINO - SANTIAGO TORTORA
 Dado un vector de N numeros reales y un numero entero k, determinar el k-esimo mayo elemento.
	Se generan dos tipos de algoritmos diferentes para comparar sus tiempos de ejecución en un tabla.
	
	El algoritmo1 (selección_mayor1) se basa en ordenar por el metodo burbuja los valores de mayor a menor, 
    de este modo los valores mayores quedaran al inicio del arreglo. Luego se ajusta el puntero para que
    k coincida con la posicion del valor en el arreglo.
    
    El algoritmo2 (selección_mayor2) se basa en ajustando el tope al maximo valor asignado. Por ejemplo, si k=1
    entonces el mayor de todos es el resultado, si es k es otro valor, se ajusta el tope con el resultado maximo obtenido
    en el recorrido anterior del arreglo.
	
	
	
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//////////////Prototipos////////////////////////////
void cargarArreglo (int *A, int tam);
void imprimirKesimos (int *A, int tam, int k);
int seleccion_mayor1 (int *A, int k, int n);
int seleccion_mayor2 (int *A, int k, int n);
////////////////////////////////////////////////////






//////////////////////////////////////////FUNCION PRINCIPAL///////////////////////////////////////////////////////////////////////////
int main () {

  system ("cls");	
	int N;
    int k; 	
	int maxValorK = 10;												//Cantidad maxima de K para el ejemplo, muestra los top 10 del mayor al menor

	
	for  (N = 1000; N<=10000; N+=1000) {					//Cantidad de elementos del arreglo
      printf (" N = %d", N);                                //Imprime en pantalla la cantidad N
	  printf ("\tAlgoritmo 1 \tAlgoritmo 2");
	  printf("\n----------------------------------------------\n");
      int b[N];                                                    //Dimensiona el arreglo para N valores
        
   
		for (k = 1; k<=maxValorK; k++) {						//El valor kesimo varia desde 1 a [N] o para el ejemplo hasta [maxValorK]
			cargarArreglo(b,N);									//Funcion que carga el arreglo de tamaño N con valores random
			printf ("K = %d", k);                               //Imprime en pantalla la cantidad K actual
			imprimirKesimos (b, N, k);							//Funcion que imprime los kesimos de acuerdo a k y los tiempos respectivos
			   //printf ("Resultado: %d", seleccion_mayor2 (b,k,N)); Muestra los resultados de acuerdo al kesimo mayor elemento
            printf("\n");
			
		}
		printf("\n\n");
	}
 
 system ("PAUSE");
 
 return 0;


}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////









////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Funciona primero ordenando el arreglo por el metodo burbuja de mayor a menor y luego con un puntero 
se ubica en  la posición k-esima */

int seleccion_mayor1 (int *A, int k, int n) {


  

    int i;
    int j;
    int resultado;
	int aux;






	//ORDENACION DEL VECTOR POR BURBUJA de mayor a menor
	for (i = 0; i<n; i++) {
      
		for (j = 0; j<n-1; j++) {
            
			if (A[j+1] > A[j]) {
			    aux = A[j+1];
				A[j+1]=A[j];
                A[j]=aux;
                   
			}
		}
	}


resultado = (A[k-1]);       //El arreglo ya esta ordenado y los mayores se encuentran al inicio, se ajusta el puntero para que k=1 coincida con la posicion 0 del arreglo y asi sucesivamente

 return (resultado);


}
////////////////////////////////////////////////////////////////////////////////////////////////////////





















////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Funciona haciendo ejecutando k veces un bucle que ajusta el tope de acuerdo al mayor 
encontrado en el recorrido previo*/

int seleccion_mayor2 (int *A, int k, int n) {



    int tope;
    int mayor;
    int i;
    int j;
    int max;
    int valorkesimo;       
    mayor = -999999999;	                                          
	tope = 99999999;



	for (i = 1; i<=k; i++) {												//El proceso se hara k veces hasta llegar al k-esimo termino
 		for  (j = 0; j< n; j++) {											//Recorrido del vector
			if ( ((A[j]) > mayor)  &&  ((A[j])<tope) ) {		//Si el valor en la posicion [i] es mayor al "mayor" y menor al tope, se asigna
				
                valorkesimo = A[j];										
				mayor = A[j];				
			}
			
		}
		tope = valorkesimo;												//Se ajusta el tope al mayor para que el tope de la siguiente pasada sea el valor mayor de la anterior
		mayor = -9999;
		
	}




//printf ("\tPrueba respuesta A2: %d", valorkesimo);
 return (valorkesimo);

}
////////////////////////////////////////////////////////////////////////////////////////////////////////






////////////////////////////////////////////////////////////////////////////////////////////////////
/*Funcion que carga el arreglo con valores aleatorios*/
void cargarArreglo (int *A, int tam) {

	int i;

	for (i = 0; i< tam; i++) {
		A[i] = rand()%11;         //Carga el arreglo con valores aleatorios, para la prueba mod11 carga valores desde 0 a 10
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////








////////////////////////////////////////////////////////////////////////////////////////////////////
/*Funcion que llama a cada funcion de resolucion, mide el tiempo e imprime los valores medidos*/
void imprimirKesimos (int *A, int tam, int k) {



    ///// Inicio de medicion de la primera funcion
    float total1,inicio1, final1;
    inicio1=clock();
       		seleccion_mayor1 (A, k, tam);           //Llamada a la primera funcion
    final1=clock();
    total1=(final1-inicio1)/(double) CLOCKS_PER_SEC;
    ///// Fin de medicion de la primera funcion



	printf ("           %f",(total1));



    ///// Inicio de medicion de la segunda funcion
    float total2,inicio2, final2;
    inicio2=clock();
		   seleccion_mayor2 (A, k, tam);           //Llamada a la segunda funcion
    final2=clock();
    total2=(final2-inicio2)/(double) CLOCKS_PER_SEC;
    ///// Fin de medicion de la primera funcion

	printf ("           %f", (total2));
	printf ("     ");
	

}
////////////////////////////////////////////////////////////////////////////////////////////////////