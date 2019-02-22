# Makefile for CS50 library
# Builds and compiles all these utility functions into a library.
#
# CS50 

# object files, and the target library
OBJS = index.o pagedir.o word.o list.o

LIB = common.a

# add -DNOSLEEP to disable the automatic sleep after web-page fetches
#               (students, please do not use -DNOSLEEP!)
# add -DMEMTEST for memory tracking report in indexer
# (and run `make clean; make` whenever you change this)
FLAGS = #-DNOSLEEP # -DMEMTEST 

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc
MAKE = make

# Build the library by archiving object files
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# Dependencies: object files depend on header files
index.o: index.h 
pagedir.o: pagedir.h
word.o: word.h
list.o:list.h 

.PHONY: clean 

# clean up after our compilation
clean:
	rm -f $(LIB) *~ *.o 