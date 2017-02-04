#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#define MAX_ARRAY 131073
#define MAX_ARRAY_2 2100000
#define TEST 50000
#define TEST_2 15000
#define UMBRAL 500
#ifndef max
  #define max(a,b) (( (a) > (b)) ? (a) : (b))
#endif

/******************** SEMILLA ***********************************/
void inicializar_semilla() {
	srand(time(NULL));          //<- SEMILLA FIJA
	/* se establece la semilla de una nueva serie de enteros
	pseudo-aleatorios */
}
/*****************************************************************/

/****************** GENERADOR NUMEROS ****************************/
void aleatorio_mod10(int v [], int n) {
	int i;
	for (i=0; i < n; i++) v[i] = (rand() % 21) - 10;
/* genera un número pseudoaleatorio entre -10 y +10 */
}
/*****************************************************************/

/************** Obtención hora actual en microsegundos ***********/
double microsegundos() {
struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
	return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}
/******************************************************************/

/********************* SUMA SUB MAX 1 *****************************/
int SumaSubMax1(int v[],int n){
	 int i,j,estaSuma,sumaMax;
	 
	 sumaMax = 0;
	 for (i=0;i<n;i++){
	 estaSuma=0;
	 	for(j=i;j<n;j++){
	 	estaSuma = estaSuma + v[j];
	 	if (estaSuma >sumaMax){sumaMax = estaSuma;}
	 	}
	 }
	return sumaMax;
}

/********************************************************************/
int SumaSubMax2(int v [],int n){
  return sumSubMaxAux(v,0,n-1);
}
/*****************************/
int sumSubMaxAux(int v [], int izq, int der){
  if (izq==der) {
    if (v[izq] > 0) {return v[izq];}
    else {return 0;}
  
  }else{
    int centro = 0, sumDer = 0, sumIzq = 0,
    sumBordeDer = 0, sumBordeIzq= 0, sumAux = 0;
    int i = 0;
    
      centro = (izq+der) / 2;
      sumDer=sumSubMaxAux(v,centro+1,der);
      sumIzq=sumSubMaxAux(v,izq,centro);
      sumBordeIzq=0;sumAux=0;
      for(i=(centro+1);i<=der;i++){
	sumAux=sumAux+v[i];
	if (sumAux > sumBordeDer){sumBordeDer = sumAux;}
      }
      sumBordeIzq=0;sumAux=0;
      for(i=centro;i>=izq;i--){
	sumAux+=v[i];
	if (sumAux>sumBordeIzq){sumBordeIzq=sumAux;}
      }
      return max(max(sumIzq,sumDer),(sumBordeDer+sumBordeIzq));
  }
}

/*********************** EJERCICIO 2 ************************************/
void testAlgoritmos(){
	int i;
	int vector1[] = {-9,2,-5,-4,6};
	int vector2[] = {4,0,9,2,5};
	int vector3[] = {-2,-1,-9,-7,-1};
	int vector4[] = {9,-2,1,-7,-8};
	int vector5[] = {15,-2,-5,-4,16}; 
	int vector6[] = {7,-5,6,7,-7};
	int vector7[15];
	
	aleatorio_mod10(vector7,15);
	printf("Algoritmo 1 \t Algoritmo 2\n");
	
	printf("%d\t\t%d {",SumaSubMax1(vector1,5),SumaSubMax2(vector1,5));
	for(i=0;i<5;i++){printf("%d,",vector1[i]);}
	printf("}\n");
	
	printf("%d\t\t%d {",SumaSubMax1(vector2,5),SumaSubMax2(vector2,5));
	for(i=0;i<5;i++){printf("%d,",vector2[i]);}
	printf("}\n");
	
	printf("%d\t\t%d {",SumaSubMax1(vector3,5),SumaSubMax2(vector3,5));
	for(i=0;i<5;i++){printf("%d,",vector3[i]);}
	printf("}\n");
	
	printf("%d\t\t%d {",SumaSubMax1(vector4,5),SumaSubMax2(vector4,5));
	for(i=0;i<5;i++){printf("%d,",vector4[i]);}
	printf("}\n");
	
	printf("%d\t\t%d {",SumaSubMax1(vector5,5),SumaSubMax2(vector5,5));
	for(i=0;i<5;i++){printf("%d,",vector5[i]);}
	printf("}\n");
	
	printf("%d\t\t%d {",SumaSubMax1(vector6,5),SumaSubMax2(vector6,5));
	for(i=0;i<5;i++){printf("%d,",vector6[i]);}
	printf("}\n");
	
	printf("%d\t\t%d {",SumaSubMax1(vector7,15),SumaSubMax2(vector7,15));
	for(i=0;i<15;i++){printf("%d,",vector7[i]);}
	printf("}\n");
}


/**************************** EJERCICIO 3**********************************/

void testAlg1(){
	int array[MAX_ARRAY];
	int i,x,j;
	long double tiempo,aux,aux2,aux3,sobre,sub,norm;
	
	printf("\nn\t|T(n)(us) \t|t(n) \t|t(n) \t|t(n) \n");
	for (i=64;i<MAX_ARRAY;i*=2){
		
		aleatorio_mod10(array,i);
		aux = microsegundos();
		x = SumaSubMax1(array,i);
		aux2=microsegundos()-aux;
		tiempo=aux2;
			if (aux2<UMBRAL) {
			aux = microsegundos();
			
			for (j=1;j<=TEST;j++)
				{aleatorio_mod10(array,i);
				SumaSubMax1(array,i);}
			aux2 = microsegundos()-aux;
			
			aux3 = microsegundos();
			for (j=1;j<=TEST;j++){
			aleatorio_mod10(array,i);}
			aux3= microsegundos()-aux3;
			
			tiempo = (aux2-aux3)/TEST;
			printf("*");
			}
		sub = tiempo/(pow(i,1.2));
		norm = tiempo/(pow(i,2));
		sobre = tiempo/(pow(i,2.5));
		printf("%d\t%12.6Lf\t%12.6Lf\t%12.6Lf\t%12.6Lf\n",i,tiempo,sub,norm,sobre);
	}
}

/********************************************************************/

void testAlg2(){
	int array[MAX_ARRAY_2];
	int i,x,j;
	long double tiempo,aux,aux2,aux3,sobre,sub,norm;
	
	printf("\nn\t|T(n)(us) \t|t(n)/ln(n)^2 \t|t(n)/(n)^1.05 \t|t(n)/(n)^1.2 \n");
	for (i=64;i<MAX_ARRAY_2;i*=2){
		aleatorio_mod10(array,i);
		aux = microsegundos();
		x = SumaSubMax2(array,i);
		aux2=microsegundos()-aux;
		tiempo=aux2;
			if (aux2<UMBRAL) {
			aux = microsegundos();
			
			for (j=1;j<=TEST_2;j++)
				{aleatorio_mod10(array,i);
				SumaSubMax2(array,i);}
			aux2 = microsegundos()-aux;
			
			aux3 = microsegundos();
			for (j=1;j<=TEST_2;j++){
			aleatorio_mod10(array,i);}
			aux3= microsegundos()-aux3;
			
			tiempo = (aux2-aux3)/TEST_2;
			printf("*");
			}
		sub = tiempo/(pow(log(i),2));
		norm = tiempo/(pow(i,1.05));
		sobre = tiempo/(pow(i,1.2));
		printf("%d\t%12.6Lf\t%12.6Lf\t%12.6Lf\t%12.6Lf\n",i,tiempo,sub,norm,sobre);
	}
}


/********************************************************************/

void main (){
inicializar_semilla();
testAlgoritmos();
testAlg1();
testAlg2();

}
