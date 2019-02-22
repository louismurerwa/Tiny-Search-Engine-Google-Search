/* ========================================================================== */
/* File: indexer.c - Tiny Search Engine web crawler
 *
 * Author:Louis Murerwa
 *
 * Input: [crawlerDirectory] [indexFilename]
 * * Command line options: N/A
 * 
 * 
 * Data structures used: A hashtable to track the page and count that a word appears in.
 */
/* ========================================================================== */
// ---------------- System libs e.g., <stdio.h>----------//
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <unistd.h>
#include <dirent.h>
 

// ---------------- Access local libraries ------------//
#include "../libcs50/set.h"
#include "../libcs50/memory.h"
#include "../libcs50/counters.h"
#include "../libcs50/bag.h"
#include "../common/pagedir.h"
#include "../common/word.h"
#include "../common/index.h"
#include "../common/list.h"
 
//Function definitions
int processQuery(index_t *index , char *pageDir);
int extractWords(char *sentence ,char *words[]);
int runQuery(index_t *index , char *words[] ,char *pageDir,int count);
int countFiles(char *filePath );
bool isAlpha(char *string);
int checkQuery(char *words[],int size);
bool isOperator(char *word);
static void set_intersect(set_t *setA, set_t *setB);
static void set_intersect_helper(void *arg, const char *key, void *item);
static void convertToSet(set_t *set , counters_t *counters);
static void convertHelper(void *set, const int key, int count);
static void set_merge(set_t *setA, set_t *setB);
static void set_merge_helper(void *arg, const char *key, void *item);
static void printQuery(void *pageDir, const char *key, void *item);
static void itemdelete(void *item);
static void set_sort(set_t *set,list_t *sortedList);
static void set_sortHelper(void *arg, const char *key, void *item);

/* ========================================================================== */
//This function reads queries from stdin and processes them by calling difrent functions
int processQuery(index_t *index , char *pageDir){
	//Read queries from stdin line by line
	int BUFFERSIZE =2000;
	char buffer[BUFFERSIZE];
    while(fgets(buffer, BUFFERSIZE , stdin) != NULL)
    {	
		//Extract words from a line and normalize the words
		char *words[1000];
		//Extract words from the line and normalizing them
		int count = extractWords(buffer,words);

		//Checking the validity of the query
		//This method checks the validity of words as described in the TSE querier design
		//It only checks if the count of words in the array is greater than zero
		//Returns 0 if query is valid
		//runQuery is called if the query is valid
       if(count>0&&checkQuery(words,count)==0){
			//Printing query for user to see
			//Search for the documents with words in the index
			//This method takes in a query and prints out the results
			runQuery(index,words,pageDir,count);
	   }
		//Reset the counter of words in the array
		count=0;
	}
	return 0; 
}  


//This functions processes the words in a query and normalizes the words
int extractWords(char *sentence ,char *words[]){
//Takes a string of words and builds an array of words
//White space in the delimeter
//Check for illegal characters before adding words to an array
//This methods are useful isalpha() and isspace()
//Normalize the words in the query
	char *temp = strtok (sentence," \n");
	int count = 0;
	//Tokenize the line and return words
	while(temp!=NULL){
		if(isAlpha(temp) && NormalizeWord(temp)){
			words[count]=temp;
    		temp = strtok (NULL, " \n");
			count=count+1;
		}
		else{
			fprintf(stderr,"Error:'%s' conatains a non-Alpahanumeric character\n",temp);
			return -1;
		}

	}
	//This is the number of words added to the array
	return count;
}

//This function is called by extract words to check if the word contains alpha numeric characters
bool isAlpha(char *string){
	char *ptr = string;
	
 	while(*ptr!='\0'){ 
    	// check for alphabets 
    	if (isalpha(*ptr)==0 && *ptr!='\n'){
        return false;
    	} 
		ptr++;
	}
	return true;
}

//This function processes the query .Checks the validity of the query
int checkQuery(char *words[],int size){
	//Valiate query
	//neither the first or last word may be an operator
	//operators may not be adjacent
	//If valid moe on to next part.
	
	//Check if that the first word of a query is not an operator
	if(isOperator(words[0])==true){
		fprintf(stderr,"Error:First word in query is an '%s' operator\n",words[0]);
		return 2;
	}
	//Check that the last word of a query is not an operator
	if(isOperator(words[size-1])==true){
		fprintf(stderr,"Error:Last word word in query is an '%s' operator\n",words[size-1]);
		return 3;
	}
	//Check that there are no concequetive operators
	for (int i = 0; i < size; i++ ) {
		if(size>1 && i < size-1 && isOperator(words[i])&&isOperator(words[i+1])){
			fprintf(stderr,"Usage:Two concecutive operators in query.'%s' and '%s' are consequtive.\n",words[i],words[i+1]);
			return 4;
		}
	}
	return 0;
}
//This method checks if an input string is an operator
bool isOperator(char *word){
	if(strcmp(word,"and")==0){ 
		return true;
	}
	if(strcmp(word,"or")==0){ 
		return true;
	}
	return false;
}



//This method runs the query and looks for the documents containg the words in the query
int runQuery(index_t *index ,char *words[],char *pageDir,int count){
	//if no documents satisfy the query, print No documents match.
	// rank the resulting set of documents according to its score,
	//print the set of documents in decreasing rank order
	//for each, list the score, document ID and URL
	//Obtain the URL by reading the first line of the relevant document file from the pageDirectory
	//One function to return set of documents that satisfy an andsequence, looping over words in the andsequence; accumulate an answer (like a running product) as you go.
	//Another function to return set of documents that satisfy a query, looping over calls to the above function for each andsequence; accumulate an answer (like a running total) as you go.
	
	//Stores URLs in each andsection of the query
	set_t *andURLS = NULL;
	//Stores urls in each word found by the query
	set_t *currentSet;
	//Stores the resulting URLs of the query
	set_t *Urlfinal = set_new();
	//Stores the counters object retrived from index datasrtucture for each object
	counters_t *countersSet;
	//Loop through the words in the query
	for(int i=0;i<count;i++){
		//If word is not an operator
		if(!isOperator(words[i])){
			//Extract the words counter set object from index structure
			countersSet=index_find(index,words[i]);
			currentSet = set_new();
			//Counters object of a word is not NULL
			if(countersSet!=NULL){
				//Convert counters object to a set
				convertToSet(currentSet,countersSet);
				//if andURLS is empty set it to currentSet
				if(andURLS==NULL){
					andURLS = set_new();
					set_merge(andURLS,currentSet);
					set_delete(currentSet,itemdelete);
				}
				else{
					//Intersect the and URLs set with the currentSet 
					set_intersect(andURLS,currentSet);
					set_delete(currentSet,itemdelete);
				}
				 
			} 
			else{
				//Create a new empty and section if counters set doesnt exist
	 			set_delete(currentSet,itemdelete);
				set_delete(andURLS,itemdelete);
				andURLS=set_new();
			}	 
		} 
		//if word is an and operator
		else if(strcmp(words[i],"and")==0){
			continue;
		} 
		//If word is an or operator merge and sections
		else if(strcmp(words[i],"or")==0){
			set_merge(Urlfinal,andURLS);
			set_delete(andURLS,itemdelete);
			
			andURLS=NULL;
		}
	}   
	//Merge the last andsection into the whole query
	set_merge(Urlfinal,andURLS);
	set_delete(andURLS,itemdelete);

	//Rank the pages in descending order
	
	void *dir = pageDir;
	list_t *sortedList = list_new();
	set_sort(Urlfinal,sortedList);
	set_delete(Urlfinal,itemdelete);

	//If list is empty
	if(list_isEmpty(sortedList)){
		printf("No documents match\n");
	}
	else{
		int count = list_size(sortedList);
		printf("Matches %d ranked (ranked) :\n",count);
		list_iterate(sortedList,dir,printQuery);
	}
 //Do list cont to find number of mathced pages
	list_delete(sortedList,itemdelete);
	
	return 0; 
}
/* Convert a counters object into a set object
 */
static void set_sort(set_t *set , list_t *sortedList){
	
	set_iterate(set,sortedList,set_sortHelper); 
}    

static void set_sortHelper(void *arg, const char *key, void *item){
	int *itemBcopy = malloc(sizeof(int));
	int *temp = item;
	int count = *temp; 
	*itemBcopy = count;
	
	list_insert(arg,key,itemBcopy);
} 
 
  
/* Convert a counters object into a set object
 */

static void convertToSet(set_t *set,counters_t *counters){
	counters_iterate(counters,set,convertHelper); 
}

static void convertHelper(void *set, const  int key, int count){
	char keys[1000];
	sprintf(keys, "%d", key);
	int *item = malloc(sizeof(int));
  *item = count;
	set_insert(set,keys,item);
}

/* print the output of the query
 */

static void printQuery(void *pageDir, const char *key, void *item){
	int *countp = item;
  	int count = *countp;

	//Create pointers for variables
    char *url;
    char filePath[1000];
		strcpy(filePath,pageDir); 
		strcat(filePath,"/"); 
   	strcat(filePath,key);
    //Open  the file in the filePath
    FILE *fp;
   	fp = fopen(filePath,"r");
    if(fp==NULL){
    	fprintf(stderr, "File %s opening failed\n",filePath);
        
    }  
    else{
        //Read the input file and store variables
        url = readlinep(fp);
        fclose(fp);
    }
	
	if(count!=0){
		printf("score %d doc %s: %s\n",count,key,url);
	}
	free(url); 
}  
      
    
   
/* Take the intersection of two sets and store it in the first set.
 * the second set is unchanged.
 */
static void  
set_intersect(set_t *setA, set_t *setB)
{
  set_iterate(setA, setB, set_intersect_helper); 
}

static void 
set_intersect_helper(void *arg, const char *key, void *item)
{
  set_t *setB = arg; 
  int *itemA = item;   

  int *itemB = set_find(setB, key); 
  if (itemB == NULL) {
    *itemA = 0;  // not found this key in set B, set the int to zero
  } else {
	int *itemBcopy = malloc(sizeof(int));
	int *temp = itemB;
	int count = *temp;
	*itemBcopy = count;
    *itemA = *itemA < *itemBcopy ? *itemA : *itemBcopy; // found the key, take the minimum
  }
}




/* Merge the second set into the first set;
 * the second set is unchanged.
 */
static void 
set_merge(set_t *setA, set_t *setB)
{  
  set_iterate(setB, setA, set_merge_helper);
}
 
/* Consider one item for insertion into the other set.
 * If the other set does not contain the item, insert it;
 * otherwise, update the other set's item with sum of item values.
 */
static void 
set_merge_helper(void *arg, const char *key, void *item)
{
  set_t *setA = arg;
  int *itemB = item;

	

  
  // find the same key in setA
  int *itemA = set_find(setA, key);
  if (itemA == NULL) {
    // not found: insert it
	int *itemBcopy = malloc(sizeof(int));
	int *temp = itemB;
	int count = *temp;
	*itemBcopy = count;
    set_insert(setA, key, itemBcopy);
  } else {
    // add to the existing value
    *itemA += *itemB;
  }
}

//Counts the number of words in the index file
int countFiles(char *filePath ){

	FILE *fp; 
    int count = 0;  // Line counter (result) 
    char c;  // To store a character read from file 
    // Open the file 
    fp = fopen(filePath, "r"); 

    // Check if file exists 
    if (fp == NULL) 
    { 
        printf("Could not open file %s\n", filePath); 
        return 0; 
    } 
  
    // Extract characters from file and store in character c 
    for (c = getc(fp); c != EOF; c = getc(fp)) 
        if (c == '\n') // Increment count if this character is newline 
            count = count + 1; 
    // Close the file 
    fclose(fp); 
    printf("Enter your query: ");    
    return count;
}
//Delete items stored in set
static void 
itemdelete(void *item)
{
  if (item != NULL)
    free(item);
}




//main function 
int main(int argc, char *argv[]){
	//Check command line arguments
	//Check if user has entered the required number of parameters
	if(argc!=3){
		fprintf(stderr,"Usage: /querier [CRAWLER_DIRECTORY] [INDEX_FILENAME] \n");
		return 1;
	}  

	//Checking if the input directory exists and is a crawler directory 
	char *pageDirectory = argv[1];
	if(!isCrawlerDirectory(pageDirectory)){
		fprintf(stderr, "Usage:%s is not a crawler directory.\n",pageDirectory);
		return 2;
	}
 
    //Checking if input file exists
    FILE *fp;
	index_t *index;
    char *indexFilename = argv[2];
	fp = fopen(indexFilename,"r");
    if(!fp){
        // file doesnt exist
        fprintf(stderr, "File %s doesnot exist\n",indexFilename);
    	return 3;
    }
	else{
		fclose(fp);
	}
   //File exists
	int numLines = countFiles(indexFilename);

	//Create index to hold input from the file
	index = index_new(numLines);
	assertp(index,"Indexer creation failed in indexer.c.");

	//Load the index
    index_load(index,indexFilename);

	//Process the query 
	processQuery(index,pageDirectory);

	//Delete the index datastructure
	index_delete(index);

	return 0;
}