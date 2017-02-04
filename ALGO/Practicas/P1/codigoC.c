#include <stdio.h>
#include <sys/time.h>
#include <math.h>

void testfib2();

/******************* Algoritmo 1 ********************/
int fib1(int n){
	if (n < 2) {return n;} else {return (fib1(n-1)+fib1(n-2));}
}
/****************************************************/




/******************* Algoritmo 2 ********************/
long long fib2(int n){

	int i = 1;
	int j = 0;
	int k = 1;
	
	for (k=1; k !=(n+1); k++){
		j+=i;
		i=j-i;}
	return j;
	}
/****************************************************/


/******************* Algoritmo 3 ********************/
long long fib3(int n){

long long i=1;
long long j=0;
long long k=0;
long long h=1;
long long t=0;

	while (n>0) {
		if ((n%2) == 1){
		t = j*h;
		j = i*h + j*k +t;
		i = i*k + t;
		}
		t = h*h;
		h = 2*k*h +t;
		k = k*k +t;
		n = n / 2;	
	}
	return j;
}
/****************************************************/


/**** Obtención hora actual en microsegundos ********/
double microsegundos() {
struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
	return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}
/****************************************************/


/***************** Test algoritmo 1 ******************/
void testfib1(){
register long double aux,aux2,aux3,sobre,sub,norm;
int n,i, test=10000;

	printf("\tn	\t|T(n)(us)      |t(n)/1.1^n  |t(n)/((1+sqrt(5))/2)^n |t(n)/2^n \n");	//Los valores de las cotas	
	for (n=2;n<=32;n*=2){

		aux2=microsegundos();
		fib1(n);
		aux3=microsegundos();
		aux=aux3-aux2;
		
		if (aux < 500) /* Tiempo es menor de 500 us*/
			{
				aux2=microsegundos();
				for(i=0;i<test;i++) 
				fib1(n);
				aux3=microsegundos();
				aux=(aux3-aux2)/test;
				printf("*");/* Indicacion de que hemos hecho este bucle*/
			}
		
		sub=aux/pow(1.1,n);
		sobre=aux/pow(2,n);
		norm=aux/pow((1+sqrt(5))/2,n);
		
		printf("|\t%8d\t%12.6Lf\t%12.6Lf\t%12.6Lf\t%12.6Lf	 \n",n,aux,sub,norm,sobre); // Imprimir las cotas
	}
	printf("\n");		
}

/****************************************************/


/***************** Test algoritmo 2 ******************/
void testfib2(){
register long double aux,aux2,aux3,sobre,sub,norm;
int n,i, test=10000;

	printf("\tn	\t|T(n)(us)	  |t(n)/n^0.8	    |t(n)/n	  |t(n)/n*log(n)\n");	//Los valores de las cotas	
	for (n=1000;n<=10000000;n*=10){

		aux2=microsegundos();
		fib2(n);
		aux3=microsegundos();
		aux=aux3-aux2;
		
		if (aux < 500) /* Tiempo es menor de 500 us*/
			{
				aux2=microsegundos();
				for(i=0;i<test;i++) 
				fib2(n);
				aux3=microsegundos();
				aux=(aux3-aux2)/test;
				printf("*");/* Indicacion de que hemos hecho este bucle*/
			}
		
		sub=aux/pow(n,0.8);
		sobre=aux/(n * log(n));
		norm=aux/n;
		
		printf("|\t%8d\t%12.6Lf\t%12.6Lf\t%12.6Lf\t%12.6Lf	 \n",n,aux,sub,norm,sobre); // Imprimir las cotas
	}
	printf("\n");		
}

/****************************************************/


/***************** Test algoritmo 3 ******************/
void testfib3(){
register long double aux,aux2,aux3,sobre,sub,norm;
int n,i, test=10000;

	printf("\tn	\t  |T(n)(us) |t(n)/sqrt(log(n))    |t(n)/log(n)   |t(n)/n^0.5 \n");	//Los valores de las cotas	
	for (n=1000;n<=10000000;n*=10){

		aux2=microsegundos();
		fib3(n);
		aux3=microsegundos();
		aux=aux3-aux2;
		
		if (aux < 500) /* Tiempo es menor de 500 us*/
			{
				aux2=microsegundos();
				for(i=0;i<test;i++) 
				fib3(n);
				aux3=microsegundos();
				aux=(aux3-aux2)/test;
				printf("*");/* Indicacion de que hemos hecho este bucle*/
			}
		
		sub=aux/(sqrt(log(n)));
		sobre=aux/(pow(n,0.5));
		norm=aux/(log(n));
		
		printf("|\t%8d\t%12.6Lf\t%12.6Lf\t%12.6Lf\t%12.6Lf	 \n",n,aux,sub,norm,sobre); // Imprimir las cotas
	}
	printf("\n");		
}
/****************************************************/


main(){

	testfib1();
	testfib2();
	testfib3();

}
