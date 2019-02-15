/*
 * pagedir.c - functions for TSE work with directories
 *
 * LouisMurerwa - January 2019
 */


#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


// ---------------- Access local libraries ------------//
#include "../libcs50/webpage.h"
#include "../libcs50/file.h"
#include "pagedir.h"


/**************** isCrawlerDirectory ****************/
/*
 * See "pagedir.h" for full documentation.
 */
bool isCrawlerDirectory(char *dir){

	//Create link to the where files are stored
	char filename[1000];
	strcpy(filename,dir);
	strcat(filename,"/.crawler");

	//Try to open .crawler for reading
	FILE *fp;
   	if((fp = fopen(filename,"r"))){
        //File exists thus its a crawler directory
        fclose(fp);
        return true;	
    }
    return false;
}

/**************** pageSaver ****************/
/*
 * See "pagedir.h" for full documentation.
 */

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
   	fp = fopen(filename,"r");
    if(fp==NULL){
    	fprintf(stderr, "File %s creation failed\n",filename);
    	return 2;
    }
    //Write the URL ,DEPTH and HTML of the page into the file
    fprintf(fp,"%s",webpage_getURL(temp)); 
    fprintf(fp, "\n"); 
	fprintf(fp, "Depth: %d", webpage_getDepth(temp));
	fprintf(fp, "\n");
    fprintf(fp,"%s",webpage_getHTML(temp));      
    fclose(fp);
    return 0;
    
}
/**************** pageLoader ****************/
/*
 * See "pagedir.h" for full documentation.
 */
int pageLoader(char *filePath,webpage_t **webpage){
    //Create pointers for variables
    char *url;
    char *depth;
    char *html;
    
    //Open  the file in the filePath
    FILE *fp;
   	fp = fopen(filePath,"r");
    if(fp==NULL){
        *webpage=NULL;
    	fprintf(stderr, "File %s opening failed\n",filePath);
    	return 2;
        
    }
    else{
        //Read the input file and store variables
        url = readlinep(fp);
        // printf("url: %s\n",url);
        depth =readlinep(fp);
        // printf("depth:%d\n",depth);
        html =readfilep(fp);
        // printf("html : %s\n",html);
        fclose(fp);
        //Create a new page from file
        *webpage = webpage_new(url,atoi(depth),html);
        //free memory
        free(url);
        free(depth);
        // free(html);
    }
    
    return 0;
}

