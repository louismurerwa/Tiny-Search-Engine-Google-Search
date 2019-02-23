# Makefile for CS50 Tiny Search Engine
#
# CS50

MAKE = make
.PHONY: all valgrind test clean

############## default: make all libs and programs ##########
all: 
	$(MAKE) -C libcs50
	$(MAKE) -C common
	$(MAKE) -C crawler
	$(MAKE) -C indexer
	$(MAKE) -C querier

############## valgrind all programs ##########
valgrind: all
	$(MAKE) -C crawler valgrind
	$(MAKE) -C indexer valgrind
	$(MAKE) -C querier valgrind


############## test all programs ##########
test: all
	$(MAKE) -C crawler test
	$(MAKE) -C indexer test
	$(MAKE) -C querier test

############## clean  ##########
clean:
	rm -f *~
	$(MAKE) -C libcs50 clean
	$(MAKE) -C common clean
	$(MAKE) -C crawler clean
	$(MAKE) -C indexer clean
	$(MAKE) -C querier clean