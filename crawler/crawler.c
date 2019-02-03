/*
 * fetchweb.c - an example of calling the webpage module to fetch a 
 *              webpage of a given URL and save it to a file.
 * 
 * usage: ./fetchweb URL FileName
 * 
 * see libcs50/webpage.md for APIs of the webpage module 
 *
 * Xia Zhou, January 2019
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "libcs50/bag.h"
#include "libcs50/hashset.h"
#include "libcs50/webpage.h"


void save_page(webpage_t* page, const char* fname)
{
	webpage_t *temp = page;
	FILE *pageinfo;
    pageinfo = fopen(fname,"w");
    if(pageinfo==NULL){
    	fprintf(stderr, "File %s creation failed\n",fname);
    }

    fprintf(pageinfo,temp->url); 
    fprintf(pageinfo,temp->html);      
    fclose(pageinfo);
    printf("Writing to the file was successful. Closing the program\n");
    
}


crawl(char *url , char *pageDirectory , int maxDepth){
	int depth = 0;
	int count = 0;
	webpage_t *firstPage = webpage_new(url,depth,NULL);
	bag_t bag = bag_new();
	hashtable_t hashtable = hashtable_new(5);
	hashtable_insert(hashtable,url,webpage);
	bag_insert(bag,webpage);

	while(!bag.isEmpty()){
		webpage *current = bag_extract(bag);
		if(IsInternalUrl(current->url)&& hashtable_find(hashtable,current->url)==NULL){
			if(!webpage_fetch(current)){
				fprintf(stderr, "Error fetching page cannot be normalized\n");
				return 3;
			}
		save_page(current,count);
		if (current->depth < maxdepth){

		 }
		 
	return 0;

		}
	}


}


int main(int argc, char *argv[]){

	if(argc!=4){
		printf("Usage:./crawler seedURL pageDirectory maxDepth\n");
		return 1 ;
	}

	// check input arguments: URL validity
	char* url = argv[1];
	if (!NormalizeURL(url)) {
		fprintf(stderr, "%s cannot be normalized\n", url);
		return 2;
	}
	//Checking if the input directory exists
	char *pageDirectory = argv[2];
	struct stat statbuf;
	stat(argv[2], &statbuf);
	if(!S_ISDIR(statbuf.st_mode)){
    	printf("Usage:pageDirectory should be valid directory\n");
    	return 3 ;
    }
	//Check if input depth is a valid integer

	if (!isdigit(atoi(argv[3]))){
        printf ("Usage:maxDepth should be an integer", argv[1]);
       	return 4;
	}
	int maxDepth = argv[3];
  	
	crawl(url ,pageDirectory,maxDepth);

	return 0;
}

