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

wrdmttns: main.o Dictionary.o
	$(CC) $(CFLAGS) -o wrdmttns main.o Dictionary.o

main.o: main.c Dictionary.h
	$(CC) -c $(CFLAGS) main.c

Dictionary.o: Dictionary.c Dictionary.h
	$(CC) -c $(CFLAGS) Dictionary.c

clean:
	rm -f *.o core a.out *.stats core a.stats wrdmttns *~