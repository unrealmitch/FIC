//      Fibonacci.c
//      
//      Copyright 2012 UnrealMitch <unrealmitch@UnrealPC-Ubuntu>
//      


#include <stdio.h>

int fib1(int n) {
	
	if (n<2) {
		return n;
	} else {
		return (fib1(n-1)+fib1(n-2));
	}
}

int fib2(int n) {
	int i,j,k;
	i=1;j=0;
	for (k=1;k<=n;k++) {
		j=i+j;
		i=j-i;
	}
	return j;
}

int fib3(int n) {
	int i,j,k,h,t;
	i=1;j=0;k=0;h=1;t=0;
	while (n>0){
		if ((n%2)!= 0) {
		t=j*h;
		j=i*h+j*k+t;
		i=i*k+t;
		}
		
		t=h*h;
		h=2*k*h+t;
		k=k*k+t;
		n=(n/2);
	}
	return j;
}

void test(int n){
   
	printf(" fib1: ");
	printf("%d",fib1(n));
    printf("\n fib2: ");
    printf("%d",fib2(n));
    printf("\n fib3 -> ");
	printf("%d",fib3(n));

}

int main(int argc, char **argv)
{
	int i;
	printf("Numero prueba:");
	scanf("%d",&i);
	test(i);
	return 0;
}



