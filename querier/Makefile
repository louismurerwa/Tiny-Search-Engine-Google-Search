# Makefile for 'querier' module
# Louis Murerwa February 2019

# Our compiler and its flags
PROG = querier 
OBJS = querier.o
LIBS = ../common/common.a ../libcs50/libcs50.a

CFLAGS =-Wall -I../libcs50 -I../common
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../common
CC = gcc
MAKE = make


$(PROG):$(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

querier.o:querier.c ../common/*.h ../libcs50/*.h 


.PHONY: test clean valgrind valgrindtest


test: 
	./querier ../crawler/testDir ../indexer/output

valgrind:
	valgrind --leak-check=full -v ./querier ../crawler/testDir ../indexer/output

 
valgrindtest:
	valgrind --leak-check=full -v ./queriertestsh
	
clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
	rm -f core
	rm -rf search