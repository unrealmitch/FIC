all: p3.out

p3.out: p3.c tmalloc.o mmap.o shared.o
	gcc -g -O0 -Wall -o p3 p3.c tmalloc.o mmap.o shared.o

tmalloc.o: tmalloc.h tmalloc.c
		gcc -g -O0 -Wall -c tmalloc.c
		
mmap.o: mmap.h mmap.c
		gcc -g -O0 -Wall -c mmap.c		
		
shared.o: shared.h shared.c
		gcc -g -O0 -Wall -c shared.c			

clean:
	rm -f p3 *.o
