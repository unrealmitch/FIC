void Prim(matriz M, int n){
	lista T = crearLista(&T);
	arista auxarista;
	int[n] DistanciaMinima, MasProximo; 
	int i,j,k;
	long min;
	
	DistanciaMinima[0]= -1;

	for(i=1;i < n;i++){
		MasProximo[i]=1;
		DistanciaMinima[i]=M[i,1];
	}

	for(i=0;i<n;i++){
		min=LONG_MAX;
			for(j=1;j<n;j++){
				if ( (0<=DistanciaMinima[j]) && (DistanciaMinima[j] <min) ) {
					min=DistanciaMinima[j];
					k=j;
				}
			}
		aux.x=MasProximo[k];
		aux.y=k
		aux.peso=M[aux.x,aux.y];
		DistanciaMinima[k] = -1;
		T=Insertar()
	} 



}
/*************************  QUICKSORT *******************************/
