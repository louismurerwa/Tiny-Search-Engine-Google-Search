# Louis Murerwa
# CS50 - Lab6

## CS50 Software Development and Design.
### Tiny Search Engine.

#### ***Download all files and run the command 'make test' to test this program.***

DEMO:

To run the whole process, cd into QUERY and run:

To build, run `make`.

To clean up, run `make clean`.

To test run testscript  `make test`.

To check memory run valgrind `make valgrind`


-----------------------------------------------------------
## To Run By Parts 

## Part 1: Crawler

## Usage: 
./crawler seedURL pageDirectory maxDepth.

```sh 
Usage: /crawler [SEED_URL] [CRAWLER_DIRECTORY] [MAX_DEPTH] 

```
>The crawler takes in three parameters:

```sh  
 1. [SEED_URL] :A url that the crawler starts crawling at.
 2. [CRAWLER_DIRECTORY]: A crawler produced directory containing the files to index.
 3. [MAX_DEPTH]: The depth that the crawler crawls to.
```

Example: crawler http://old-www.cs.dartmouth.edu/index.html ./data/ 2.

### Sample Command Line Output
Count 1 Depth 2 Saving http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Eleazar_Wheelock.html.

## Assumptions
Current directory input as argument must exist, or the program will return an error and quit.
All URLs to be crawled must begin with "http://old-www.cs.dartmouth.edu/~cs50/tse/". 
When server does not exist or url is not valid they are both treat as non-internal URL'S.


## Part 2: Indexer


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



## Part 3: Query Engine


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


## Example Output

Queries: Dartmouth , College ,Dartmouth College, Dartmouth or College

<img width="1434" alt="screen shot 2019-02-03 at 3 03 45 pm" src="https://github.com/LUXATHEMASTER/Tiny-Search-Engine-Google-Search/blob/master/img/Screenshot%202019-03-08%2015.04.12.png">
