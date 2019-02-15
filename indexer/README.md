#Louis Murerwa
## CS50-Lab5

[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://travis-ci.org/joemccann/dillinger)

To build, run `make`.

To clean up, run `make clean`.

To run testscript  `make test`.

> The TSE indexer is a standalone program that reads the document files produced by the **TSE crawler**, builds an index, and writes that index to a file. Its companion, the index tester, loads an index file produced by the indexer and saves it to another file.The Indexer is part of the three components of the Tiny Search Engine program. It is responsible for "indexing" the webpages downloaded by the crawler. It gets all the words in all of the downloaded documents and counts the frequency of their occurence. It then prints this information into a file for reading.

```sh 
Usage: /indexer [CRAWLER_DIRECTORY] [RESULTS_FILENAME] 
Usage: /indextest [INDEX_DATASTRUCTURE_FILE] [NEW_INDEX_DATASTRUCTURE_FILE]
```
>The indexer takes in two parameters:
```sh  
 1. [CRAWLER_DIRECTORY]: A crawler produced directory containing the files to index.
 2. [RESULTS_FILENAME]: A filename where the index datastructure is printed to.
```

>The indexertest takes in two parameters:

```sh   
1. [INDEX_DATASTRUCTURE_FILE]:A file containing an index datastructure to be loaded.
2. [NEW_INDEX_DATASTRUCTURE_FILE]: A filename where the the index data struture is copied to.
```


 **make test**: 
- Runs a testing script called indexertest.sh.
 - The testing script tests extensively tests both the indextest and indexer programs.
- An in-depth description of the script is contained in indexertest.sh.
 