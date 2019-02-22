## Louis Murerwa ,January 2019

## Professor Xia Zhou

## CS50 Software Development and Design.
#### Tiny Search Engine – Crawler Implemantation.
 
 
>DataStructures

* **Hash-table.**

>I used an index data-structure that uses a set for its implementation. The index data-structure stores the words, which are found in the documents created by crawler. The documents are named by ID, starting at 1 and increasing by one. The index takes an item, in this case counters. Counters for their key takes the document ID that the word was found in. The counter also keeps track of the frequencies of the word in each document. After the user inputs a query the program searches for the counts in each document.

* **Set**

>I used a set to hold my page id and word frequency.The current-set held objects that corresponded to one word.The currentSet was intersected with with andURLS set to produce the andURLS set which held objects in an and sequence.The andURLs sets were merged together after an and operator to produce the Url final set which held all objects for the query.

1. **currentSet** - Held objects corresponding to one word.
2. **andURLS** - held objects corresponding to an and sequence.
3. **Urlfinal** - held objects corresponding to the whole query.



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







#### Enjoy

![Minion](https://octodex.github.com/images/minion.png)
![Stormtroopocat](https://octodex.github.com/images/stormtroopocat.jpg "The Stormtroopocat")

![Alt text][id]

[id]: https://octodex.github.com/images/dojocat.jpg  "The Dojocat"
 