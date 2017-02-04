CC = gcc
LDFLAGS = -L/usr/lib -lglut -lGLU -lGL -lm
IFLAGS  = -I/usr/include 
CCFLAGS = -g -Wall -O2

EXENAME = noria

TARGETS = noria2.c

default:
	$(CC) $(TARGETS) $(CCFLAGS) $(IFLAGS) $(LDFLAGS) -o $(EXENAME)

run:
	$(CC) $(TARGETS) $(CCFLAGS) $(IFLAGS) $(LDFLAGS) -o $(EXENAME)
	./$(EXENAME)
