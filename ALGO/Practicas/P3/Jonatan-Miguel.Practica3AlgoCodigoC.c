#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define MAX_ARRAY 2048001 
#define UMBRAL2 500
#define TEST 1000
int UMBRAL;

/********************** FUNCIONES AUXILIARES ***********************/
void inicializar_semilla() {
	srand(time(NULL));          //<- SEMILLA FIJA
	/* se establece la semilla de una nueva serie de enteros
	pseudo-aleatorios */
}

double microsegundos() {
struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
	return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

void aleatorio_mod50(int v [], int n) {
	int i;
	for (i=0; i < n; i++) v[i] = (rand() % 101) - 50;
}

void aleatorio(int v [], int n) {
  int i;
  for (i=0; i < n; i++)
    v[i] = rand();
}

void ascendente(int v [], int n) {
  int i;
  for (i=0; i < n; i++)
    v[i] = i;
}

void descendente(int v [], int n) {
  int i;
  for (i=0; i < n; i++)
    v[i] = n-i;
}

/*********************** INSERTION-SORT ******************************/


void ord_ins(int v[],int n){
int i,j,x;
	
	for(i=1;i<n;i++){
		x=v[i];
		j=i-1;
		while((j>=0)&&(v[j]>x)){
			v[j+1] = v[j];
			j--;
		}
		v[j+1]=x;
	}
}
          /** CABECERA **/
void OrdenacionInsercion(int v[],int n){
    ord_ins(v,n);
}

/*************************  QUICKSORT *******************************/

void intercambiar(int v[], int i, int j){
  int temp=v[i];
  v[i]=v[j];
  v[j]=temp;
}


void Mediana3(int v[], int i, int j){
  int k;
  
     k = (i+j) / 2;
  
  if (v[k] > v[j]) {
    intercambiar(v,k,j);
  }
  
  if (v[k] > v[i]) {
    intercambiar(v,k,i);
  }
  
  if (v[i] > v[j]) {
    intercambiar(v,i,j);
  }
}

void OrdenarAux(int v[],int izq, int der){
  int pivote=0, i=0, j=0;
  
  if ((izq+UMBRAL) <= der){
    Mediana3(v,izq,der);
    
    pivote= v[izq];
    i=izq;
    j=der;
    
    do{
      do{
          i++;
      }while(v[i]<pivote);
      do{
          j--;
      }while(v[j]>pivote);
      intercambiar(v,i,j);
    }while(j>i);
    
    intercambiar(v,i,j);
    intercambiar(v,izq,j);
    OrdenarAux(v,izq,j-1);
    OrdenarAux(v,j+1,der);
  }
}
          /** CABECERA **/
void OrdenacionRapida(int v[],int n){
  OrdenarAux(v,0,n-1);
  if(UMBRAL > 1) {
    ord_ins(v,n);
  }
}

/************************** VALIDACIONES ****************************/
void ValidacionOrdenacionInsercion(int max){
int vector[max];
int i;
     inicializar_semilla();
     
     printf("\n");
     printf("#############################\n");
     printf("Inicialización Aleatoria\n");
     aleatorio_mod50(vector,max);
     printf("Vector Sin Ordenar\n");
	for(i=0;i<max;i++){printf("%d ",vector[i]);}
	printf("\n"); 
	ord_ins(vector,max);
	printf("Vector Ordenado por Insercion\n");
	for(i=0;i<max;i++){printf("%d ",vector[i]);} 
	printf("\n");
	printf("#############################\n");
	
	
	printf("\n");
	printf("#############################\n");
	printf("Inicialización Descendente\n");
    	descendente(vector,max);
     printf("Vector Sin Ordenar\n");
	for(i=0;i<max;i++){printf("%d ",vector[i]);}
	printf("\n"); 
	ord_ins(vector,max);
	printf("Vector Ordenado por Inserción\n");
	for(i=0;i<max;i++){printf("%d ",vector[i]);} 
	printf("\n");
	printf("#############################\n");
	
    	
    	printf("\n");
    	printf("#############################\n");
	printf("Inicialización Ascendente\n");
   	ascendente(vector,max);
   	printf("Vector Sin Ordenar\n");
	for(i=0;i<max;i++){printf("%d ",vector[i]);}
	printf("\n"); 
	ord_ins(vector,max);
	printf("Vector Ordenado por Inserción\n");
	for(i=0;i<max;i++){printf("%d ",vector[i]);} 
	printf("\n");
	printf("#############################\n");
}

void ValidacionOrdenacionRapida(int max){
int vector[max];
int i;
     inicializar_semilla();
     UMBRAL=1;
     printf("\n");
     printf("#############################\n");
     printf("Inicialización Aleatoria\n");
     aleatorio_mod50(vector,max);
     printf("Vector Sin Ordenar\n");
	for(i=0;i<max;i++){printf("%d ",vector[i]);}
	printf("\n"); 
	OrdenacionRapida(vector,max);
	printf("Vector Ordenado por Quicksort\n");
	for(i=0;i<max;i++){printf("%d ",vector[i]);} 
	printf("\n");
	printf("#############################\n");
	
	
	printf("\n");
	printf("#############################\n");
	printf("Inicialización Descendente\n");
     descendente(vector,max);
     printf("Vector Sin Ordenar\n");
	for(i=0;i<max;i++){printf("%d ",vector[i]);}
	printf("\n"); 
	OrdenacionRapida(vector,max);
	printf("Vector Ordenado por Quicksort\n");
	for(i=0;i<max;i++){printf("%d ",vector[i]);} 
	printf("\n");
	printf("#############################\n");
	
	
     printf("\n");
	printf("#############################\n");
	printf("Inicialización Ascendente\n");
   	ascendente(vector,max);
     printf("Vector Sin Ordenar\n");
	for(i=0;i<max;i++){printf("%d ",vector[i]);}
	printf("\n"); 
	OrdenacionRapida(vector,max);
	printf("Vector Ordenado por Quicksort\n");
	for(i=0;i<max;i++){printf("%d ",vector[i]);} 
	printf("\n");
	printf("#############################\n");
}

/*************************** PRUEBAS EMPIRICAS **********************/
void prueba_insercion(int max){
     int *array;
	int i,x,j;
	long double tiempo=0,aux,aux2,aux3,sobre,sub,norm;

	array = malloc(max*sizeof(int));
	
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("Ordenacion por insercion con vector ALEATORIO\n");
	printf("\n       n         |T(n)(us)   |T(n)(s)    |t(n)/n^1.54 |t(n)/n^1.77 |t(n)/n^2.0   \n"); 
	for (i=500;i<max && tiempo < 1000000;i*=2){
		
		aleatorio(array,i);
		aux = microsegundos();
		OrdenacionInsercion(array,i);
		aux2=microsegundos()-aux;
		tiempo=aux2;
		if (aux2<UMBRAL2) {
		
			aux = microsegundos();
			for (j=1;j<=TEST;j++){
				aleatorio(array,i);
				OrdenacionInsercion(array,i);;
			}
			aux2 = microsegundos()-aux;
			aux3 = microsegundos();
			for (j=1;j<=TEST;j++){
				aleatorio(array,i);
			}
			aux3= microsegundos()-aux3;
			tiempo = (aux2-aux3)/TEST;
			printf("*");
		}else{printf(" ");}
		sub = tiempo/(pow(i,1.54));
		norm = tiempo/(pow(i,1.77));
		sobre = tiempo/pow(i,2);
		printf("%10d %15.6Lf %7.3Lf %13.6Lf %12.6Lf %12.6Lf \n"
                        ,i,  tiempo,tiempo/1000000, sub, norm,  sobre);
	}
	
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("Ordenacion por insercion con vector ASCENDENTE\n");
	printf("\n       n         |T(n)(us)   |T(n)(s)    |t(n)/ln(n)  |t(n)/n      |t(n)/n*ln(n) \n"); 
	tiempo=0;
	for (i=500;i<max && tiempo < 1000000;i*=2){
		
		ascendente(array,i);
		aux = microsegundos();
		OrdenacionInsercion(array,i);
		aux2=microsegundos()-aux;
		tiempo=aux2;
		if (aux2<UMBRAL2) {
		
			aux = microsegundos();
			for (j=1;j<=TEST;j++){
			     ascendente(array,i);
				OrdenacionInsercion(array,i);
			}
			aux2 = microsegundos()-aux;
			aux3 = microsegundos();
			for (j=1;j<=TEST;j++){
				ascendente(array,i);
			}
			aux3= microsegundos()-aux3;
			tiempo = (aux2-aux3)/TEST;
			printf("*");
		}else{printf(" ");}
		sub = tiempo/log(i);
		norm = tiempo/i;
		sobre = tiempo/(i*log(i));
		printf("%10d %15.6Lf %7.3Lf %13.6Lf %12.6Lf %12.6Lf \n"
                        ,i,  tiempo,tiempo/1000000, sub, norm,  sobre);
	}
	
	
	tiempo=0;
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("Ordenacion por insercion con vector DESCENDENTE\n");
	printf("\n       n         |T(n)(us)   |T(n)(s)    |t(n)/n^1.8  |t(n)/n^2    |t(n)/n^2.2   \n");
	for (i=500;i<max && tiempo < 1000000;i*=2){
		
		descendente(array,i);
		aux = microsegundos();
		OrdenacionInsercion(array,i);
		aux2=microsegundos()-aux;
		tiempo=aux2;
		if (aux2<UMBRAL2) {
		
			aux = microsegundos();
			for (j=1;j<=TEST;j++){
				descendente(array,i);
				OrdenacionInsercion(array,i);
			}
			aux2 = microsegundos()-aux;
			aux3 = microsegundos();
			for (j=1;j<=TEST;j++){
				descendente(array,i);
			}
			aux3= microsegundos()-aux3;
			tiempo = (aux2-aux3)/TEST;
			printf("*");
		}else{printf(" ");}
		sub = tiempo/pow(i,1.8);
		norm = tiempo/pow(i,2);
		sobre = tiempo/pow(i,2.2);
		printf("%10d %15.6Lf %7.3Lf %13.6Lf %12.6Lf %12.6Lf \n"
                        ,i,  tiempo,tiempo/1000000, sub, norm,  sobre);
	}


}



/* UMBRAL = 1  */

void prueba_umbral1(){

	//int array[MAX_ARRAY];
	int *array;
	int i,x,j;
	long double tiempo,aux,aux2,aux3,sobre,sub,norm;

	array = malloc(MAX_ARRAY*sizeof(int));
	UMBRAL=1;
	
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("Con UMBRAL = %d y orden ALEATORIO\n",UMBRAL);
	printf("\n       n         |T(n)(us)   |T(n)(s) |t(n)/        |t(n)/           |t(n)/  \n"); 
	printf("                                          ln(n)*n^0.7    ln(n)*n^1.25     n^1.25\n");
	printf("\n");
	
	for (i=500;i<MAX_ARRAY;i*=2){
		
		aleatorio(array,i);
		aux = microsegundos();
		OrdenacionRapida(array,i);
		aux2=microsegundos()-aux;
		tiempo=aux2;
		if (aux2<UMBRAL2) {
		
			aux = microsegundos();
			for (j=1;j<=TEST;j++){
				aleatorio(array,i);
				OrdenacionRapida(array,i);
			}
			aux2 = microsegundos()-aux;
			aux3 = microsegundos();
			for (j=1;j<=TEST;j++){
				aleatorio(array,i);
			}
			aux3= microsegundos()-aux3;
			tiempo = (aux2-aux3)/TEST;
			printf("*");
		}else{printf(" ");}
		sub = tiempo/(log(i)*pow(i,0.70));
		norm = tiempo/(log(i)*pow(i,0.98));
		sobre = tiempo/pow(i,1.25);
		printf("%10d %15.6Lf %7.3Lf %13.6Lf %12.6Lf %12.6Lf \n"
                        ,i,  tiempo,tiempo/1000000, sub, norm,  sobre);
	}
	
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("Con UMBRAL = %d y orden ASCENDENTE\n",UMBRAL);
	printf("\n       n         |T(n)(us)   |T(n)(s)  |t(n)/n^0.89  |t(n)/n^1.045 |t(n)/n^1.19  \n"); 
	for (i=500;i<MAX_ARRAY;i*=2){
		
		ascendente(array,i);
		aux = microsegundos();
		OrdenacionRapida(array,i);
		aux2=microsegundos()-aux;
		tiempo=aux2;
		if (aux2<UMBRAL2) {
		
			aux = microsegundos();
			for (j=1;j<=TEST;j++){
			     ascendente(array,i);
				OrdenacionRapida(array,i);
			}
			aux2 = microsegundos()-aux;
			aux3 = microsegundos();
			for (j=1;j<=TEST;j++){
				ascendente(array,i);
			}
			aux3= microsegundos()-aux3;
			tiempo = aux2/TEST;
			printf("*");
		}else{printf(" ");}
		sub = tiempo/pow(i,0.89);
		norm = tiempo/pow(i,1.045);
		sobre = tiempo/pow(i,1.19);
		printf("%10d %15.6Lf %7.3Lf %13.6Lf %12.6Lf %12.6Lf \n"
                        ,i,  tiempo,tiempo/1000000, sub, norm,  sobre);
	}
	
	
	
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("Con UMBRAL = %d y orden DESCENDENTE\n",UMBRAL);
	printf("\n       n         |T(n)(us)   |T(n)(s)  |t(n)/n^0.95  |t(n)/n^1.05  |t(n)/n^1.15  \n");  
	for (i=500;i<MAX_ARRAY;i*=2){
		
		descendente(array,i);
		aux = microsegundos();
		OrdenacionRapida(array,i);
		aux2=microsegundos()-aux;
		tiempo=aux2;
		if (aux2<UMBRAL2) {
		
			aux = microsegundos();
			for (j=1;j<=TEST;j++){
				descendente(array,i);
				OrdenacionRapida(array,i);
			}
			aux2 = microsegundos()-aux;
			aux3 = microsegundos();
			for (j=1;j<=TEST;j++){
				descendente(array,i);
			}
			aux3= microsegundos()-aux3;
			tiempo = (aux2-aux3)/TEST;
			printf("*");
		}else{printf(" ");}
		sub = tiempo/pow(i,0.95);
		norm = tiempo/pow(i,1.05);
		sobre = tiempo/pow(i,1.15);
		printf("%10d %15.6Lf %7.3Lf %13.6Lf %12.6Lf %12.6Lf \n"
                        ,i,  tiempo,tiempo/1000000, sub, norm,  sobre);
	}

}

/* UMBRAL = 10  */

void prueba_umbral10(){

	//int array[MAX_ARRAY];
	int * array;
	int i,x,j;
	long double tiempo,aux,aux2,aux3,sobre,sub,norm;
	
	array = malloc(MAX_ARRAY*sizeof(int));
	UMBRAL=10;
	
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("Con UMBRAL = %d y orden ALEATORIO\n",UMBRAL);
	printf("\n       n         |T(n)(us)   |T(n)(s) |t(n)/        |t(n)/           |t(n)/  \n"); 
	printf("                                          ln(n)*n^0.7    ln(n)*n^0.99     n^1.25\n");
	printf("\n");;
	for (i=500;i<MAX_ARRAY;i*=2){
		
		aleatorio(array,i);
		aux = microsegundos();
		OrdenacionRapida(array,i);
		aux2=microsegundos()-aux;
		tiempo=aux2;
		if (aux2<UMBRAL2) {
		
			aux = microsegundos();
			for (j=1;j<=TEST;j++){
				aleatorio(array,i);
				OrdenacionRapida(array,i);
			}
			aux2 = microsegundos()-aux;
			aux3 = microsegundos();
			for (j=1;j<=TEST;j++){
				aleatorio(array,i);
			}
			aux3= microsegundos()-aux3;
			tiempo = (aux2-aux3)/TEST;
			printf("*");
		}else{printf(" ");}
		sub = tiempo/(log(i)*pow(i,0.70));
		norm = tiempo/(log(i)*pow(i,0.99));
		sobre = tiempo/pow(i,1.25);
		printf("%10d %15.6Lf %7.3Lf %13.6Lf %12.6Lf %12.6Lf \n"
                        ,i,  tiempo,tiempo/1000000, sub, norm,  sobre);
	}
	
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("Con UMBRAL = %d y orden ASCENDENTE\n",UMBRAL);
	printf("\n       n         |T(n)(us)   |T(n)(s)  |t(n)/n^0.93  |t(n)/n^1.065 |t(n)/n^1.200 \n");
	for (i=500;i<MAX_ARRAY;i*=2){
		
		ascendente(array,i);
		aux = microsegundos();
		OrdenacionRapida(array,i);
		aux2=microsegundos()-aux;
		tiempo=aux2;
		if (aux2<UMBRAL2) {
		
			aux = microsegundos();
			for (j=1;j<=TEST;j++){
			     ascendente(array,i);
				OrdenacionRapida(array,i);
			}
			aux2 = microsegundos()-aux;
			aux3 = microsegundos();
			for (j=1;j<=TEST;j++){
				ascendente(array,i);
			}
			aux3= microsegundos()-aux3;
			tiempo = aux2/TEST;
			printf("*");
		}else{printf(" ");}
		sub = tiempo/pow(i,0.930);
		norm = tiempo/pow(i,1.065);
		sobre = tiempo/pow(i,1.200);
		printf("%10d %15.6Lf %7.3Lf %13.6Lf %12.6Lf %12.6Lf \n"
                        ,i,  tiempo,tiempo/1000000, sub, norm,  sobre);
	}
	
	
	
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("Con UMBRAL = %d y orden DESCENDENTE\n",UMBRAL);
	printf("\n       n         |T(n)(us)   |T(n)(s)  |t(n)/n^0.94  |t(n)/n^1.07 |t(n)/n^1.20  \n");
	for (i=500;i<MAX_ARRAY;i*=2){
		
		descendente(array,i);
		aux = microsegundos();
		OrdenacionRapida(array,i);
		aux2=microsegundos()-aux;
		tiempo=aux2;
		if (aux2<UMBRAL2) {
		
			aux = microsegundos();
			for (j=1;j<=TEST;j++){
				descendente(array,i);
				OrdenacionRapida(array,i);
			}
			aux2 = microsegundos()-aux;
			aux3 = microsegundos();
			for (j=1;j<=TEST;j++){
				descendente(array,i);
			}
			aux3= microsegundos()-aux3;
			tiempo = (aux2-aux3)/TEST;
			printf("*");
		}else{printf(" ");}
		sub = tiempo/pow(i,0.94);
		norm = tiempo/pow(i,1.07);
		sobre = tiempo/pow(i,1.20);
		printf("%10d %15.6Lf %7.3Lf %13.6Lf %12.6Lf %12.6Lf \n"
                        ,i,  tiempo,tiempo/1000000, sub, norm,  sobre);
	}
free(array);

}

/* UMBRAL = 100  */

void prueba_umbral100(){

	//int array[MAX_ARRAY];
	int *array;
	int i,x,j;
	long double tiempo,aux,aux2,aux3,sobre,sub,norm;

	array = malloc(MAX_ARRAY*sizeof(int));
	UMBRAL=100;
	
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("Con UMBRAL = %d y orden ALEATORIO\n",UMBRAL);
	printf("\n       n         |T(n)(us)   |T(n)(s) |t(n)/        |t(n)/           |t(n)/  \n"); 
	printf("                                          ln(n)*n^0.7    ln(n)*n^0.975     n^1.25\n");
	printf("\n");
	for (i=500;i<MAX_ARRAY;i*=2){
		
		aleatorio(array,i);
		aux = microsegundos();
		OrdenacionRapida(array,i);
		aux2=microsegundos()-aux;
		tiempo=aux2;
		if (aux2<UMBRAL2) {
		
			aux = microsegundos();
			for (j=1;j<=TEST;j++){
				aleatorio(array,i);
				OrdenacionRapida(array,i);
			}
			aux2 = microsegundos()-aux;
			aux3 = microsegundos();
			for (j=1;j<=TEST;j++){
				aleatorio(array,i);
			}
			aux3= microsegundos()-aux3;
			tiempo = (aux2-aux3)/TEST;
			printf("*");
		}else{printf(" ");}
		sub = tiempo/(log(i)*pow(i,0.70));
		norm = tiempo/(log(i)*pow(i,0.975));
		sobre = tiempo/pow(i,1.25);
		printf("%10d %15.6Lf %7.3Lf %13.6Lf %12.6Lf %12.6Lf \n"
                        ,i,  tiempo,tiempo/1000000, sub, norm,  sobre);
	}
	
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("Con UMBRAL = %d y orden ASCENDENTE\n",UMBRAL);
	printf("\n       n         |T(n)(us)   |T(n)(s)  |t(n)/n^0.95  |t(n)/n^1.09 |t(n)/n^1.23  \n");
	for (i=500;i<MAX_ARRAY;i*=2){
		
		ascendente(array,i);
		aux = microsegundos();
		OrdenacionRapida(array,i);
		aux2=microsegundos()-aux;
		tiempo=aux2;
		if (aux2<UMBRAL2) {
		
			aux = microsegundos();
			for (j=1;j<=TEST;j++){
			     ascendente(array,i);
				OrdenacionRapida(array,i);
			}
			aux2 = microsegundos()-aux;
			aux3 = microsegundos();
			for (j=1;j<=TEST;j++){
				ascendente(array,i);
			}
			aux3= microsegundos()-aux3;
			tiempo = aux2/TEST;
			printf("*");
		}else{printf(" ");}
		sub = tiempo/pow(i,0.95);
		norm = tiempo/pow(i,1.09);
		sobre = tiempo/pow(i,1.23);
		printf("%10d %15.6Lf %7.3Lf %13.6Lf %12.6Lf %12.6Lf \n"
                        ,i,  tiempo,tiempo/1000000, sub, norm,  sobre);
	}
	
	
	
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("Con UMBRAL = %d y orden DESCENDENTE\n",UMBRAL);
	printf("\n       n         |T(n)(us)   |T(n)(s)  |t(n)/n^0.94  |t(n)/n^1.1 |t(n)/n^1.26  \n");
	for (i=500;i<MAX_ARRAY;i*=2){
		
		descendente(array,i);
		aux = microsegundos();
		OrdenacionRapida(array,i);
		aux2=microsegundos()-aux;
		tiempo=aux2;
		if (aux2<UMBRAL2) {
		
			aux = microsegundos();
			for (j=1;j<=TEST;j++){
				descendente(array,i);
				OrdenacionRapida(array,i);
			}
			aux2 = microsegundos()-aux;
			aux3 = microsegundos();
			for (j=1;j<=TEST;j++){
				descendente(array,i);
			}
			aux3= microsegundos()-aux3;
			tiempo = (aux2-aux3)/TEST;
			printf("*");
		}else{printf(" ");}
		sub = tiempo/pow(i,0.94);
		norm = tiempo/pow(i,1.1);
		sobre = tiempo/pow(i,1.26);
		printf("%10d %15.6Lf %7.3Lf %13.6Lf %12.6Lf %12.6Lf \n"
                        ,i,  tiempo,tiempo/1000000, sub, norm,  sobre);
	}
free(array);
}
/*********************************************************************/



void main(){
     //ValidacionOrdenacionRapida(20);
     //ValidacionOrdenacionInsercion(20);
     //prueba_insercion(128001);
	prueba_umbral1();
	prueba_umbral10();
	prueba_umbral100();
	
}
	
	
	
	
	
	
	
	
	
	
	
	
