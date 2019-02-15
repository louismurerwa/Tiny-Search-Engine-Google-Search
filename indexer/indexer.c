/* ========================================================================== */
/* File: indexer.c - Tiny Search Engine web crawler
 *
 * Author:Louis Murerwa
 *
 * Input: [crawlerDirectory] [outputfile]
 * * Command line options: N/A
 * 
 * 
 * Data structures used: A hashtable to track the page and count that a word appears in.
 */
/* ========================================================================== */
// ---------------- System libs e.g., <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <unistd.h>
#include <dirent.h>

// ---------------- Access local libraries ------------//
#include "../libcs50/webpage.h"
#include "../libcs50/memory.h"
#include "../common/pagedir.h"
#include "../common/word.h"
#include "../common/index.h"
 
//Function definitions
int indexer(char *pageDirectory , char *indexFilename);
int countFiles(char *dir );
   
/* ========================================================================== */
//This function indexes the pages stored in the crawler pageDirectory
int indexer(char *pageDirectory , char *indexFilename){
 
	//Create datastructures that holds:words->(documentID,count)
	index_t *indexer = index_new(300);
	assertp(indexer,"Indexer creation failed in indexer.c.");

	//Loop through the pages in the pageDirectory
	int numFiles = countFiles(pageDirectory);
	for(int i = 1 ;i<numFiles;i++){
	 
		//Create path to files in crawler directory
		char filename[1000];
		char num[10];
		strcpy(filename,pageDirectory);
		strcat(filename,"/"); 
		sprintf(num, "%d", i);
  		strcat(filename,num);
		
		//Read each file and grab the the filename(ID),depth,html.
		webpage_t *currentPage;
		pageLoader(filename,&currentPage);
		assertp(currentPage,"Webpage creation failed in indexer.c");

		//Read words from the webpage
 		int pos = 0;
 		char *result;
		if(webpage_getURL(currentPage)!=NULL){
 			while ((pos = webpage_getNextWord(currentPage, pos, &result)) > 0) {
				//Normalize word
				if(NormalizeWord(result)&&strlen(result)>2){
				//found links to the bag
					index_insert(indexer,result,i); 
 	 			}
 				free(result);
 			}
		}  
		webpage_delete(currentPage);
	}
	//Save the indexer to an output file
	index_save(indexer,indexFilename);
 
	//Delete the index datastructure
	index_delete(indexer);

	return 0; 
}  


//This function counts the total number of files stored in a directory
int countFiles(char *dir ){

	int count = -2;
	struct dirent *de;  // Pointer for directory entry 
    // opendir() returns a pointer of DIR type.  
    DIR *dr = opendir(dir); 
    
    if (dr == NULL)  // opendir returns NULL if couldn't open directory 
    { 
        //Directory opening failes 
        return 0; 
    } 

    while ((de = readdir(dr)) != NULL){
            count =count + 1;
	}

    closedir(dr);     
    return count;
}

//main function 
int main(int argc, char *argv[]){
	//Check command line arguments
	//Check if user has entered the required number of parameters
	if(argc!=3){
		fprintf(stderr,"Usage: /indexer [CRAWLER_DIRECTORY] [RESULTS_FILENAME] \n");
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
    char *indexFilename = argv[2];
    if((fp = fopen(indexFilename,"w"))!=NULL){
        // file exists
        fclose(fp);
    }
    else{
    	fprintf(stderr, "File %s creation failed\n",indexFilename);
    	return 3;
    }

	//Call the indexer method
	indexer(pageDirectory,indexFilename);

	return 0;
}


