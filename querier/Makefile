# Makefile for 'querier' module
# Louis Murerwa February 2019

# Our compiler and its flags
PROG1= querier 
PROG2= fuzzquery
OBJS1 = querier.o
OBJS2 = fuzzquery.o
LIBS = ../common/common.a ../libcs50/libcs50.a

CFLAGS =-Wall -I../libcs50 -I../common
CFLAGS = -Wall -pedantic -std=gnu11 -ggdb $(TESTING) -I../common
CC = gcc
MAKE = make


$(PROG1):$(OBJS1)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

$(PROG2):$(OBJS2)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

querier.o:querier.c ../common/*.h ../libcs50/*.h
fuzzquery.o:fuzzquery.c

all: querier fuzzquery


.PHONY: test clean valgrind valgrindtest


test: 
	./querier ../crawler/testDir ../indexer/output

valgrind:
	valgrind --leak-check=full -v ./querier ../crawler/testDir ../indexer/output

 
valgrindtest:
	valgrind --leak-check=full -v ./queriertestsh
	
clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG1)
	rm -f $(PROG2)
	rm -f core
	rm -rf search
