# AED Projeto
#
# Francisco Apolinário
# Inês Mesquita
#
# To compile prog:
#    make
#----------------------------------------------------------------------

CC=gcc
CFLAGS= -Wall -std=c99 -O3

wrdmttns: main.o Dictionary.o Graph.o heap.o
	$(CC) $(CFLAGS) -o wrdmttns main.o Dictionary.o Graph.o heap.o

main.o: Dictionary.o
	$(CC) -c $(CFLAGS) main.c

Dictionary.o: Dictionary.c Dictionary.h heap.o Graph.o 
	$(CC) -c $(CFLAGS) Dictionary.c

Graph.o: heap.o Graph.c Graph.h
	$(CC) -c $(CFLAGS) Graph.c

heap.o: heap.h
	$(CC) -c $(CFLAGS) heap.c

clean:
	rm -f *.o core a.out *.paths core a.paths wrdmttns *~
