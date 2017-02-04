CFLAGS= -g -O0
all:ListaAristas.o
	gcc $(CFLAGS) -c Jonatan-Miguel-Practica4AlgoCodigo.c 
	gcc $(CFLAGS) -o  prim Jonatan-Miguel-Practica4AlgoCodigo.o ListaAristas.o -lm


ListaAristas.o:
	gcc $(CFLAGS) -c ListaAristas.c
	
clean:
	rm -f *.o
	rm -f *.out
