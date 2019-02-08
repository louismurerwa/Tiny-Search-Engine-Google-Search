/*
 * crawler.c - an example of calling the webpage module to fetch a 
 *              webpage of a given URL and save it to a file.
 * 
 * usage: ./crawler URL pageDirectory maxDepth
 * 
 * see libcs50/webpage.md for APIs of the webpage module 
 *
 * Louis Murerwa, January 2019
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

#include "../libcs50/webpage.h"
#include "../libcs50/bag.h"
#include "../libcs50/hashtable.h"

//Function definitions

int save_page(webpage_t* page, const char* pageDirectory ,int count);
int crawl(char *url , char *pageDirectory , int maxDepth);
int pageScanner(webpage_t *current ,bag_t **bagm);
void namedelete(void* item);
void itemdelete(void *item);


//main function

int main(int argc, char *argv[]){

	//Check if user has entered the required number of arguments
	if(argc!=4){
		fprintf(stderr,"Usage:Enter three arguments\n");
		return 1;
	}

	// check input arguments: 
	//URL validity 
	char *url = argv[1];
	if (IsInternalURL(url)==false) {
		fprintf(stderr, "Usage:Seed URL is not an internal URL\n");
		return 2;
	}

	if (NormalizeURL(argv[1]) == 0) {
		fprintf(stderr,"Usage:Invalid seed URL given.\n");
		return 3;
	}

             
	//Checking if the input directory exists

	char *pageDirectory = argv[2];
	DIR *dir  = opendir(pageDirectory);
	if (dir != NULL) {
		closedir(dir);
	}
	else{
		fprintf(stderr, "Usage:%s directory doesn't exist.\n",pageDirectory);
		return 4;
	}
	
	//Checking if the input maxDepth is an integer

		for (int i = 0; i < strlen(argv[3]); i++) {
		if (!isdigit(argv[3][i])) {
			printf("Usage:Depth must be an integer.\n");
			return 1;
		}
	}
	//Check if the maxDepth is greater than zero
	
	int maxDepth = atoi(argv[3]);
	//Crawl the page of the URL to get more links
	crawl(url ,pageDirectory,maxDepth);

	return 0;
}

//This function crawlws the page of the input URL to get further URL links
int crawl(char *url , char *pageDirectory , int maxDepth){
	//Keep counter of pages saved so far
	int count = 0;

	//Create datastructures to hold our webpage and url
	bag_t *bag = bag_new();
	hashtable_t *hashtable = hashtable_new(15);

	//Create  the seed webpage to be the seed webpage

	webpage_t *firstPage;
	firstPage = webpage_new(url,0,NULL);

	//Insert the seed webpage into the data structures
	
	bag_insert(bag,firstPage);

	//Loop through the bag while it is not empty
	webpage_t *current ;

	while((current=(bag_extract(bag)))!=NULL){
		
		

		//Check if url of the hashtable has been visited before and if it is internal.
		if(hashtable_find(hashtable,webpage_getURL(current))==NULL && IsInternalURL(webpage_getURL(current))==true){
			printf("Current Url%s\n",webpage_getURL(current) );
			printf("Depth%d\n",webpage_getDepth(current));
			//Insert the URl into the hashtable.
			hashtable_insert(hashtable,webpage_getURL(current),webpage_getURL(current));
			
			//Fetch the html content of the current of the current page .
			if(webpage_fetch(current)){
				//Save the current content of the page
				save_page(current,pageDirectory,count);
				count=count+1;
				if (webpage_getDepth(current) < maxDepth){
					//Scan the current page for more URLS
					pageScanner(current,&bag);
				}
			}
			else{
				//Print out error
				fprintf(stderr, "%s : Failed to fetch the page \n",webpage_getURL(current));
			}
			
		}
		webpage_delete(current);
	}
	//Free memory stored by the datastructures
	hashtable_delete(hashtable,itemdelete);
	bag_delete(bag,namedelete);
	
	
	return 0;
}

//This function saves an in put page into a directory and filename inputed as parameters
int save_page(webpage_t* page, const char* pageDirectory ,int count)
{
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
	FILE *pageinfo;
    pageinfo = fopen(filename,"w");
    if(pageinfo==NULL){
    	fprintf(stderr, "File %s creation failed\n",filename);
    	return 5;
    }
    //Write the URL and HTML of the page into the file
    fprintf(pageinfo,webpage_getURL(temp)); 
    fprintf(pageinfo,webpage_getHTML(temp));      
    fclose(pageinfo);
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


