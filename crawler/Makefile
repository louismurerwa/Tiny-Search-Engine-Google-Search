# Makefile for 'bag' module
#
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

test: $(PROG) datafile
	./$(PROG) < datafile


clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
	rm -f core
	rm -rf search
	