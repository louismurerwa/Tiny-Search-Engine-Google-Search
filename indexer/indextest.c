/* ========================================================================== */
/* File: indextest.c - Tiny Search Engine web crawler
 *
 * Author:Louis Murerwa
 *
 * Input: [indexdatastructurefile] [new file] [maxDepth]
 * * Command line options: N/A
 *
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
#include "../common/pagedir.h"
#include "../common/word.h" 
#include "../common/index.h"
   

//Test function
void test(char *oldfileIndex,char *newfileindex){
	//Create new index 
    index_t *current=index_new(100);
	//Load index datastructure from file
	index_load(current,oldfileIndex);
	//Save index datastructure to file
	index_save(current,newfileindex);
	//Delete the index datastructure
	index_delete(current);
}
//main function
   
int main(int argc, char *argv[]){
 

	//Check command line arguments
	//Check if user has entered the required number of parameters
	if(argc!=3){
		fprintf(stderr,"Usage: /indextest [INDEX_DATASTRUCTURE_FILE] [NEW_INDEX_DATASTRUCTURE_FILE]\n");
		return 1;
	}
	//Testing index_load and save
 	char *oldfileIndex = argv[1];
    char *newfileindex = argv[2];
	test(oldfileIndex,newfileindex);
	return 0;
}


