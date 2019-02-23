# Makefile for 'bag' module
#Louis Murerwa
# David Kotz, April 2016, 2017
# updated by Xia Zhou, July 2016, 2018, January 2019

# Our compiler and its flags
PROG = crawler
OBJS = crawler.o 
LIBS = ../libcs50/libcs50.a

CFLAGS =-Wall -I../libcs50 -I../common
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../common
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

crawler.o:crawler.c ../libcs50/libcs50.a

.PHONY: test clean

test: 
	mkdir testDir
	./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/ ../crawler/testDir  1
	
valgrind:
	valgrind --leak-check=full -v ./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/ ../crawler/testDir  1


clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
	rm -f core
	rm -rf search
	rm -rf testDir

 