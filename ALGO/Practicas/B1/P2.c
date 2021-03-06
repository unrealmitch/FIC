#ifndef max
  #define max(a,b) (( (a) > (b)) ? (a) : (b))
#endif

#include <stdio.h>
#include <sys/time.h>

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

int sumaSubMax(int v [],int n){
  return sumSubMaxAux(v,0,n-1);
}

main(){
  int array[8];
  array[0]=-9;
  array[1]=2;
  array[2]=-5;
  array[3]=-4;
  array[4]=6;
  array[5]=-8;
  array[6]=6;
  array[7]=-9;
  printf("El Max es: %d /n",sumaSubMax(array,5));
}