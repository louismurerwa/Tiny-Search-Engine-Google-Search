# Makefile for 'index' module
#Louis Murerwa
# David Kotz, April 2016, 2017
# updated by Xia Zhou, July 2016, 2018, January 2019

# Our compiler and its flags
PROG = indexer indextest
OBJS = indexer.o 
OBJS2 = indextest.o
LIBS = ../common/common.a ../libcs50/libcs50.a

CFLAGS =-Wall -I../libcs50 -I../common
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../common
CC = gcc
MAKE = make


all:$(PROG)

indexer:$(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

indextest: $(OBJS2)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@


indexer.o:indexer.c  ../common/*.h ../libcs50/*.h
indextest.o:indextest.c ../common/*.h ../libcs50/*.h

.PHONY: test clean


test: 
	./indexer ../crawler/testDir output
	./indexertest.sh

valgrind:
	valgrind --leak-check=full -v ./indexer ../crawler/testDir output

 
valgrindtest:
	valgrind --leak-check=full -v ./indextest
	
clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
	rm -f core
	rm -rf search
	rm -rf testDir
	rm -f input
	rm -f newoutput  
	rm -f newoutput_sorted  
	rm -f output_sorted 
	rm -f output
	rm -f testoutput.txt
