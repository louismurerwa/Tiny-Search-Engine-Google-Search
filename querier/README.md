# Louis Murerwa
# CS50 - Lab6

## CS50 Software Development and Design.
### Tiny Search Engine – Querier Implemantation.


![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://travis-ci.org/joemccann/dillinger)

To build, run `make`.

To clean up, run `make clean`.

To test run testscript  `make test`.

To check memory run valgrind `make valgrind` 



querier.c uses a directory containing output from crawler.c and an associated index file created by indexer.c to parse queries from the user. The querier returns a list of documents / webpages that satisfy the given query.

> The TSE querier is a standalone program that takes a query and reads the index input file produced by **TSE Indexer** and the crawler directory produced by the **TSE crawler**.The querier builds an index from the input file and looks for queries in that index.The querier returns a list of files that the represent the query and the list of files representing the query.

```sh 
Usage: /querier [CRAWLER_DIRECTORY] [INDEX_FILE] 
Usage: /queriertest.sh
```
>The querier takes in two parameters:
```sh  
 1. [CRAWLER_DIRECTORY]: A crawler produced directory containing the files to index.
 2. [RESULTS_FILENAME]: A filename where containing an index printed to a file.
```

```
for instance:

[Query]  Dartmouth College

Evaluating query: dartmouth college
Matches 3 documents (ranked):
Score: 242 docID:   4 | http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Dartmouth_College.html

Score:   1 docID:   1 | http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/

Score:   1 docID:   7 | http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html


Assumptions
pageDirectory was created by crawler.c
indexFilename was created by indexer.c from pageDirectory
Return Values.

0.  Success
1. Incorrect number of arguments
2.  Invalid crawler output directory or invalid index file
3. Error opening file for I/O

pageDirectory has files named 1, 2, 3, …, without gaps.
The content of files in pageDirectory follow the format as defined in the specs; thus your code (to read the files) need not have extensive error checking.
