# Louis Murerwa ,January 2019

# Professor Xia Zhou

## CS50 Software Development and Design.
### Tiny Search Engine – Indexer Implemantation.
 
 


## Indexer data flow

![alt text](https://www.cs.dartmouth.edu/~cs50/Lectures/indexer/data-model.png)

> Pseudocode and Implementation.

- main( )
  * The main method parses the two arguments.
     - First it checks if the user has passed in two arguments.
     - Second it calls the isCrawlerDirectory method implemented in pagedir.c which is common module inorder to validate the directory.
     - Third it checks if the passed file exists .If not it creates the file and returns an error on file creation failure.
     - Fourth the program calls the indexer( ) method to index the files in the crawler directory.

- indexer( )
  - The indexer method a new index of size 300 by calling index_new( ) which is defined in index.c in the common module.
      - The method return a new hash-table.
   - The indexer method then calls a countFiles( ) method which is in the same file inorder to count the number of pages in the crawler directory.
   - The indexer then loops over each file in the crawlerDirectory and keeps track of count.
      - Creates a path name to a file of id count passes the file to the pageloader() method defined in pagedir.c.
          - This methods creates a new webpage and stores the url ,depth and html on the webpage structure and then returns the webpage.
       - The program then checks if the page is not null and parses the webpage to the webppage_getNextWord( ) which returns the words in the content of the webpage.
       -After using the page the indexer calls webpage_delete( ) which deletes the webpages and frees the valuable memory.
    - The indexer then saves the index data-structure to a file by calling the index_save method( ).
    - Finally the indexer delete the index and frees some valuable memory.
 
>Simplified Version.

Indexer

Process and validate command-line parameters
* Initialize data structure index
* index_build(directory, index)
* index_save(file, index);
* clean up data structures
* indextest:

Indextest

Process and validate command-line parameters
* Initialize data structure index
* index_load(file1, index)
* index_save(file2, index)
* clean up data structures


>TESTING

* The program can be tested through the provided test system, which can be found
within the indextest.sh. The script tests the program in both successful and
failed test cases to ensure that the program runs smoothly. It provides system information and the
results of each test case.


