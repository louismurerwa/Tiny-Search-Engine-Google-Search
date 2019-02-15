/* ========================================================================== */
/* File: crawler.c - Tiny Search Engine web crawler
 *
 * Author:Louis Murerwa
 *
 * Input: [seed-url] [target directory] [maxDepth]
 * * Command line options: N/A
 *
 * Output: For each webpage visited, creates a file in the webPageDirectory. The 
 * first two lines of this file are the URL of the webpage and the current depth 
 * of search respectively. The HTML of the webpage will start on the third line. 
 * This file is named based on the number of webpages the crawler has so far 
 * crawled, meaning the first webpage would be called "1.html" and the second 
 * "2.html" and so on.
  * Special Considerations: Only webpages under the following domain will be 
 * crawled: http://old-www.cs.dartmouth.edu/~cs50/tse
 *
 * Description: Crawler for a search enginer that crawls the seed-url unitl max depth is reached, adding pages crawled to the target directory to be used by the indexer.
 *
 * Data structures used: A hashtable to track visited urls .A bag to store pages to be visited.
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
#include "../libcs50/bag.h"
#include "../libcs50/hashtable.h"

//Function definitions
int fetchPage(webpage_t *webpage);
int pageSaver(webpage_t* page, const char* pageDirectory ,int count);
int crawl(char *url , char *pageDirectory , int maxDepth);
int pageScanner(webpage_t *current ,bag_t **bagm);
void namedelete(void* item);
void itemdelete(void *item);


/* ========================================================================== */

//This function crawlws the page of the input URL to get further URL links
int crawl(char *url , char *pageDirectory , int maxDepth){
	//Keep counter of pages saved so far
	int count = 1;

	//Create datastructures to hold our webpage and url
	bag_t *bag = bag_new();
	hashtable_t *hashtable = hashtable_new(150);

	//Create  the seed webpage with a depth of zero
	webpage_t *firstPage;
	firstPage = webpage_new(url,0,NULL);

	//Insert the seed webpage into the bag
	bag_insert(bag,firstPage);

	//Loop through the bag while it is not empty
	webpage_t *current ;
	while((current=(bag_extract(bag)))!=NULL){
		
		//Check if url of the hashtable has been visited before and if it is internal.
		if(hashtable_find(hashtable,webpage_getURL(current))==NULL && IsInternalURL(webpage_getURL(current))==true){
			//Insert the URl into the hashtable of visited.
			hashtable_insert(hashtable,webpage_getURL(current),webpage_getURL(current));
			//Fetch the webpage
			fetchPage(current);
			//Save the current content of the page
			pageSaver(current,pageDirectory,count);
			count=count+1;
			if (webpage_getDepth(current) < maxDepth){
				//Scan the current page for more URLS
				pageScanner(current,&bag);
			}
			
		}
		//the the crawled page
		webpage_delete(current);
	}
	//Free memory stored by the datastructures
	hashtable_delete(hashtable,itemdelete);
	bag_delete(bag,namedelete);
	
	
	return 0;
}

//Fetch the html content of the current of the current page .
int fetchPage(webpage_t *webpage){
	if(!webpage_fetch(webpage)){
		//Print out error
		fprintf(stderr, "%s : Failed to fetch the page \n",webpage_getURL(webpage));
	}
	return 0;
}

//This function saves an in put page into a directory and filename inputed as parameters
int pageSaver(webpage_t* page, const char* pageDirectory ,int count)
{	
	printf("Count %d Depth %d Saving %s\n",count,webpage_getDepth(page),webpage_getURL(page));
	//Create link to the where files are stored
	char filename[10000];
	char num[5];
	strcpy(filename,pageDirectory);
	strcat(filename,"/");
	sprintf(num, "%d", count);
	strcat(filename,num);


	//Save and pageDirectory in current variables
	webpage_t *temp = page;

	//Create file
	FILE *fp;
   	fp = fopen(filename,"w");
    if(fp==NULL){
    	fprintf(stderr, "File %s creation failed\n",filename);
    	return 8;
    }
    //Write the URL ,DEPTH and HTML of the page into the file
    fprintf(fp,"%s",webpage_getURL(temp)); 
    fprintf(fp, "\n"); 
	fprintf(fp, "%d", webpage_getDepth(temp));
	fprintf(fp, "\n");
    fprintf(fp,"%s",webpage_getHTML(temp));      
    fclose(fp);
    return 0;
    
}
//This functions scans an input webpage for URLS and stores them in a datasstructure called bag
int pageScanner(webpage_t *current ,bag_t **bag){
	//Get the html on the input page
	int pos = 0;
  	char *result;
  	//loop through current page to get URLs
	while ((pos = webpage_getNextURL(current, pos, &result)) > 0) {
		
		if(NormalizeURL(result)){
			//found links to the bag
			bag_insert(*bag,webpage_new(result,webpage_getDepth(current)+1,NULL));
 	 	}

		free(result);
 	 
	}
	return 0;
}

//Delte items in bag
void namedelete(void* item)
{
  if (item != NULL) {
    free(item);   
  }
}
//Delete items in hashtable
void itemdelete(void *item)
{}

//main function

int main(int argc, char *argv[]){

	//Check command line arguments
	//Check if user has entered the required number of parameters
	if(argc!=4){
		fprintf(stderr,"Usage:Enter three parameters\n");
		return 1;
	}

	//check input arguments: 
	//URL validity 
	char *url = argv[1];
	if (IsInternalURL(url)==false) {
		fprintf(stderr, "Usage:Seed URL not valid\n");
		return 2;
	}

	if (NormalizeURL(url) == 0) {
		fprintf(stderr,"Usage:Seed URL cannot be normalised.\n");
		return 3;
	}

             
	//Checking if the input directory exists

	char *pageDirectory = argv[2];
	DIR *dir  = opendir(pageDirectory);
	if (dir != NULL) {
		printf("Saving /.crawler file to pageDirectory");
		//Create link to the where files are stored
		char filename[10000];
		strcpy(filename,pageDirectory);
		strcat(filename,"/.crawler");
		
		//Create file
		FILE *fp;
   		fp = fopen(filename,"w");
    	if(fp==NULL){
    		fprintf(stderr, "File %s creation failed\n",filename);
    		return 8;
    	}
		closedir(dir);
	}
	else{
		fprintf(stderr, "Usage:%s directory doesn't exist.\n",pageDirectory);
		return 4;
	}
	
	//Checking if the input maxDepth is an integer

	for (int i = 0; i < strlen(argv[3]); i++) {
		if (!isdigit(argv[3][i])) {
			fprintf(stderr,"Usage:Depth must be an a positive integer.\n");
			return 5;
		}
	}
	//Check if the maxDepth is greater than zero	
	if (atoi(argv[3]) < 0) {
		fprintf(stderr, "Max depth should be greater than 0\n");
		return 6;
	}
	
	int maxDepth = atoi(argv[3]);
	//Crawl the page of the URL to get more links
	crawl(url ,pageDirectory,maxDepth);

	return 0;
}


