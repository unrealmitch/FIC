#include "ListaAristas.h"
#include <math.h>

#define MAX_N 901
#define UMBRAL 500
#define TEST 15

    double microsegundos(){
    struct timeval t;
        if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
        return (t.tv_usec + t.tv_sec * 1000000.0);
    }
    
    
    /*********************** PRIM ********************************/
    lista Prim(matriz M, int n){
        lista T;
        arista auxarista;
        int * MasProximo = (int *) malloc(n*sizeof(int));
        int * DistanciaMinima = (int *) malloc(n*sizeof(int));
        int i,j,k;
        long min;
    
             crear_lista(&T);
             DistanciaMinima[0]= -1;

             for(i=1;i < n;i++){
                 MasProximo[i]=0;
                 DistanciaMinima[i]=M[i][0];
             }

             for(i=0;i<(n-1);i++){
                 min=1000000;
                 for(j=1;j<n;j++){
                     if ( (0<=DistanciaMinima[j]) && (DistanciaMinima[j] <min) ) {
                         min=DistanciaMinima[j];
                         k=j;
                     }
                 }
                 auxarista.x=MasProximo[k];
                 auxarista.y=k;
                 auxarista.peso=M[auxarista.x][auxarista.y];
                 DistanciaMinima[k] = -1;
                 insertar(auxarista,&T);
                 for(j=1;j<n;j++){
                     if (M[j][k] < DistanciaMinima[j]) {
                         DistanciaMinima[j]=M[j][k];
                         MasProximo[j]=k;
                     }
                 }
             }
             free(MasProximo);
             free(DistanciaMinima);
             return T;
    }
     
     /*********************** FUNCIONES AUXILIARES MATRICES ********************************/
     matriz crearMatriz(int n) {
        int i;
        matriz aux;
     
             if ((aux = (int **) malloc(n*sizeof(int *))) == NULL)
                  return NULL;
             
             for (i=0; i<n; i++)
                  if ((aux[i] = (int *) malloc(n*sizeof(int))) == NULL)
                  return NULL;
             
             return aux;
     }
     
     void inicializarMatriz(matriz m, int n) {
     /* Crea un grafo completo no dirigido con pesos aleatorios entre 1 y n */
          int i, j;
               for (i=0; i<n; i++)
                    for (j=i+1; j<n; j++)
                         m[i][j] = rand() % n + 1;
               
               for (i=0; i<n; i++)
                    for (j=0; j<=i; j++)
                         if (i==j)
                              m[i][j] = 0;
                         else
                              m[i][j] = m[j][i];
     
     }
     
     void liberarMatriz(matriz m, int n) {
          int i;
               for (i=0; i<n; i++)
                    free(m[i]);
               free(m);
     }


     /*********************** VALIDACIONES ********************************/
     void ValidacionAlgoritmo1(){
          matriz M = NULL;
          lista l;
               M = crearMatriz(5);
               M[0][0] = 0; M[0][1] = 1; M[0][2] = 8; M[0][3] = 4; M[0][4] = 7;
               M[1][0] = 1; M[1][1] = 0; M[1][2] = 2; M[1][3] = 6; M[1][4] = 5;
               M[2][0] = 8; M[2][1] = 2; M[2][2] = 0; M[2][3] = 9; M[2][4] = 5;
               M[3][0] = 4; M[3][1] = 6; M[3][2] = 9; M[3][3] = 0; M[3][4] = 3;
               M[4][0] = 7; M[4][1] = 5; M[4][2] = 5; M[4][3] = 3; M[4][4] = 0; 
               
               l=Prim(M,5);
               printf("Validacion con matriz n = 5\n");
               mostrar(l);
               printf("\n");
               liberarMatriz(M,5);
          }
     
      void ValidacionAlgoritmo2(){
          matriz M = NULL;
          lista l;
               M = crearMatriz(4);
               M[0][0] = 0; M[0][1] = 1; M[0][2] = 4; M[0][3] = 7;
               M[1][0] = 1; M[1][1] = 0; M[1][2] = 2; M[1][3] = 8; 
               M[2][0] = 4; M[2][1] = 2; M[2][2] = 0; M[2][3] = 3; 
               M[3][0] = 7; M[3][1] = 8; M[3][2] = 3; M[3][3] = 0;
              
               l=Prim(M,4);
               printf("Validacion con matriz n = 4\n");
               mostrar(l);
               printf("\n");
               liberarMatriz(M,4);
          }
     
          void ValidacionAlgoritmo3(){
          matriz M = NULL;
          lista l;
               M = crearMatriz(7);
               M[0][0] = 0; M[0][1] = 7; M[0][2] = 99; M[0][3] = 5; M[0][4] = 99; M[0][5] = 99; M[0][6] = 99;
               M[1][0] = 7; M[1][1] = 0; M[1][2] = 8; M[1][3] = 9; M[1][4] = 7; M[1][5] = 99; M[1][6] = 99;
               M[2][0] = 99; M[2][1] = 8; M[2][2] = 0; M[2][3] = 99; M[2][4] = 5; M[2][5] = 99; M[2][6] = 99;
               M[3][0] = 5; M[3][1] = 9; M[3][2] = 99; M[3][3] = 0; M[3][4] = 15; M[3][5] = 6; M[3][6] = 99;
               M[4][0] = 99; M[4][1] = 7; M[4][2] = 5; M[4][3] = 15; M[4][4] = 0; M[4][5] = 8; M[4][6] = 9;
               M[5][0] = 99; M[5][1] = 99; M[5][2] = 99; M[5][3] = 6; M[5][4] = 8; M[5][5] = 0; M[5][6] = 11;
               M[6][0] = 99; M[6][1] = 99; M[6][2] = 99; M[6][3] = 99; M[6][4] = 9; M[6][5] = 11; M[6][6] = 0;
      
               l=Prim(M,7);
               printf("Validacion con matriz n = 7\n");
               mostrar(l);
               printf("\n");
               liberarMatriz(M,7);
     }
          
     
     
          /*********************** MEDICION EMPIRICA ***************************/
     void medicion(){
         int i,x,j;
         long double tiempo,aux,aux2,aux3,sobre,sub,norm;
         matriz M = NULL;
         lista l;
        
        
          printf("\n       n         |T(n)(us)     |t(n)/n^1.9   |t(n)n^2      |t(n)n^2.1  \n"); 
          for (i=50;i<MAX_N;i+=100){
             M = crearMatriz(i);
             inicializarMatriz(M,i);
             aux = microsegundos();
             l=Prim(M,i);
             aux2=microsegundos()-aux;
             tiempo=aux2;
             if (tiempo<UMBRAL) {
                 aux = microsegundos();
                 for (j=1;j<=TEST;j++){
                     inicializarMatriz(M,i);
                     l=Prim(M,i);
                     VaciarLista(&l);
                 }
                 aux2 = microsegundos()-aux;
                 aux3 = microsegundos();
                 for (j=1;j<=TEST;j++){
                     inicializarMatriz(M,i);
                 }
                 aux3= microsegundos()-aux3;
                 tiempo = (aux2-aux3)/TEST;
                 printf("*");
             }else{
                 printf(" ");
                 VaciarLista(&l);
             }
             sub = tiempo/pow(i,1.9);
             norm = tiempo/pow(i,2);
             sobre = tiempo/pow(i,2.1);
             if(i==650){printf("       -----------------------------------------------------------\n ");}
             printf("%10d %15.2Lf %13.6Lf %12.6Lf %12.6Lf \n"
                        ,i,  tiempo, sub,    norm,  sobre);
              liberarMatriz(M,i);
           }
     }
     

void main(){
    ValidacionAlgoritmo1();
    ValidacionAlgoritmo2();
    ValidacionAlgoritmo3();
    medicion();
    medicion();
    medicion();
    medicion();
}




