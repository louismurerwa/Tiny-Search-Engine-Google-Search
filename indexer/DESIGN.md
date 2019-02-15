# Louis Murerwa January 2019

# Proffesor Xia Zhou

## CS50 Software Development and Design
### Tiny Search Engine – Indexer Design


>DESCRIPTION 

>The TSE indexer is a standalone program that reads the document files produced by the TSE crawler, builds an "index" of words and their frequencies, and writes that index to a file.This index file can be later used by the query engine to create a list of results. Its companion, the index tester, loads an index file produced by the indexer and saves it to another file.


INPUT:
```c
Usage: /indexer [CRAWLER_DIRECTORY] [RESULTS_FILENAME]

```

>The indexer takes two arguments a crawler directory which it reads from and a filename to which it writes the resulting index data structure.

>Arguments:

1. [TARGET_DIRECTORY] – the directory with the crawled webpages you would like to index.
2. [RESULTS_FILENAME] – the desired name of the index file
 
>Requirements:
1. The target directory must contain .crawler file to indicate that its a crawler produced directory.
2. The output file must exist or be possible to be opened.

> OUTPUT

The indexer outputs an output file which is written in the form:

* one line per word, one word per line
* each line provides the word and one or more (docID, count) pairs, in the format
  - word docID count [docID count]…
  - where word is a string of lower-case letters,
  - where docID is a positive non-zero integer,
  - where count is a positive non-zero integer,
  -  where the word and integers are separated by spaces

* Example outputs:
  - make 3 7 5 1
  - swim 9 1 12 4


  > DATA STRUCTURES AND FLOW
 
* The indexer uses an index data-structure as its main data structure.The index struct has a pointer to a hash table and this is where data is stored.

* The hash-table hold holds counters objects where the key is a word and the id of the counters object is a page id and the count the frequency of that word in a page.


* The pages are stored in the pageDir produced by the crawler and the indexer just references the ids of those pages .

* The hash-table handles collision by using chaining as counters nodes have pointers to the next object in case a collision happens.

* The program first populates the main “index” hashtable data structure by parsing the pages and
grabbing the valid words, then adding these words to the hashtable and incrementing
frequency/documents as necessary. 


* Then, with the completed index, this information is written to the
results file in the format specified above.