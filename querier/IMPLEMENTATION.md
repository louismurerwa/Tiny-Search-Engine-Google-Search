## Louis Murerwa ,January 2019

## Professor Xia Zhou

## CS50 Software Development and Design.
#### Tiny Search Engine – Crawler Implemantation.
 


* **List**

>The list data structure holds objects ordered in descending order.The objects are ordered upon insertion. So this is more efficient than sorting and also takes a O(n) running time.The list was data-structure is contained in common because in the future I want to expand this project and all the parts of the project will use this data-structure. 


### Program Structure

>All the logic is contained in one program querier.c. 


querier.c

``` c
int main(int argc, char *argv[])
```
-  The main method parses the two arguments.
     - First it checks if the user has passed in two arguments.
     - Second it calls the isCrawlerDirectory method implemented in pagedir.c which is common module inorder to validate the directory.
     - Third it checks if the passed file exists .If not it creates the file and returns an error on file creation failure.
     - Fourth the program calls the processQuery( ) method to take and process the query form the stdin.



``` c
int processQuery(index_t *index , char *pageDir)
```
- While reading queries from stdin into a line	
   - Calls the extract words method to extract words from line ,tokenize the line and normalize the words
   - Calls check query to check validity of the query.
   - Calls the run-query method that takes in a array of words in the query and prints out the results of the query.

``` c
int extractWords(char *sentence ,char *words[])
```

- Takes a string of words and builds an array of words
- White space in the delimeter when tokenizing
- Check for illegal characters before adding words to an array
- The methods methods uses these predefined methods isalpha( ) and isspace( )
- Normalize the words in the query


``` c
int checkQuery(char *words[],int size)
````
- Validate the query according to the following rules.
    - neither the first or last word may be an operator
    - operators may not be adjacent.
    - If valid move on to next part.


``` c
bool isOperator(char *word)
```
-This method checks if an input string is an operator


``` c
int runQuery(index_t *index ,char *words[],char 
*pageDir,int count)
```

- The method initializes the data structures needed for running the query.
- While the array of queries is not empty.
   - Take each word and check if it is an operator.
   - If it not an operator find the corresponding counters set object from the index structure.
   - Call the covert to set method which converts the countersset to a set.
   - Put the contents of this the andURLS set if it is empty
   - If the andURLS is not empty call intersect to merge this to currentSet.

- If word is and and operator continue.
- if word if and or operator loop through merge the set holding andsequence with the URLfinal which holds the results of all the queries.

- Call the setsort to rank the the final output URLS and this method returns a sorted list.
- Call list _iterate to print out the ranked urls.

```c
static void set_sort(set_t *set , list_t *sortedList)
```
- This method takes in a set contain all the URLs from the resulting query and ranks them according to frequency.

```c
static void printQuery(void *pageDir, const char *key, void *item)
````
- This method is a helper method the is called with set or list iterate to print infomation held in those structures.

```c
static void  
set_intersect(set_t *setA, set_t *setB)
````
- Takes two sets and intersects the two sets into the first set.

```c
static void 
set_merge(set_t *setA, set_t *setB)
````

- Takes two sets and combines them and returns the output.

```c
int countFiles(char *filePath )
```
-Counts the number of lines in a file .

```c
static void rank(set_t *Urlfinal,char *pageDir)
```
-Ranks the pages in descending order of frequency.
-Uses a list DataStructure which stores items in order.
list.c

````c

/**************** global types ****************/
typedef struct list list_t;  // opaque to users of the module

/**************** functions ****************/

/* Create a new (empty) list; return NULL if error. */
list_t *list_new(void);

/* Insert item, identified by a key (string), into the given list.
 * The key string is copied for use by the list; that is, the module
 * is responsible for allocating memory for a copy of the key string, and
 * later deallocating that memory; thus, the caller is free to re-use or 
 * deallocate its key string after this call.  
 * Return false if key exists, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool list_insert(list_t *list, const char *key, void *item);


/* Iterate over all items in the list, in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If list==NULL or itemfunc==NULL, do nothing.
 */
void list_iterate(list_t *list, void *arg,
		 void (*itemfunc)(void *arg, const char *key, void *item) );


/* Counts the number of items stored in a list*/
int list_size(list_t *list);


/* Check if a list is empty and return true if it is empty*/
bool list_isEmpty(list_t *list);

/* Delete the whole list; ignore NULL list.
 * Provide a function that will delete each item (may be NULL).
 */
void list_delete(list_t *list, void (*itemdelete)(void *item) );


````



#### Enjoy

![Minion](https://octodex.github.com/images/minion.png)

 