all: main.out

main.out: main.c listaprocesos.o
	gcc -g -O0 -Wall -o main.out main.c listaprocesos.o

listaprocesos.o: listaprocesos.h listaprocesos.c
		gcc -g -O0 -Wall -c listaprocesos.c

clean:
	rm -f *.out *.o
