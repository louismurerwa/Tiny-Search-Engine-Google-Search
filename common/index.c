/* 
 * index.c - CS50 'index' module
 * index.c is inspired by the design of index.c by Profesor Xia and Proffesor Campbell
 *
 * see index.h for more information.
 * 
 *Louis Murerwa, January 2019
 */
 
 // ---------------- System libs e.g., <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------- Access local libraries ------------//
#include"../common/index.h"
#include"../libcs50/counters.h"
#include"../libcs50/jhash.h"
#include"../libcs50/hashtable.h"
#include"../libcs50/file.h"
#include"../libcs50/memory.h"

/**************** global functions ****************/
/* that is, visible outside this file */
/* see index.h for comments about exported functions */

typedef struct index 
{
  hashtable_t *hashtable; //pointer to the array of pointers to sets which contain countrers
} index_t;
// /**************** local functions ****************/
//  not visible outside this file 


/******** delete counters item ********/
static void ct_delete(void *item)
{
	counters_t* ct = item;
	if (ct != NULL) {
		counters_delete(ct);
	}
}

/******** helper to save items in counters ********/
static void save_counts (void *arg, const int key, int count)
{
	FILE *fp = arg; 
	fprintf(fp, "%d %d ", key, count);
} 

/******** helper to save item in hashtable ********/
static void save_item (void *arg, const char *key, void *item)
{
	FILE *fp = arg; 
	counters_t *c = item;
  //Write key to file
	fprintf(fp, "%s ", key);
  //Iterate over the counters set
	counters_iterate(c, fp, save_counts);
	fprintf(fp, "\n");
}

/**************** index_new() ****************/
/* Create a new (empty) index; return NULL if error. 
 * Allocate memory to the new index
*/

index_t *index_new(const int num_slots){
  //Allocate memory to index struct
  index_t *index = malloc(sizeof(index_t));

  if (index == NULL) {
    return NULL; // error allocating index
  } else {
    // initialize contents of hashtable structure
    index->hashtable = hashtable_new(num_slots);
    return index;
  }
}

/**************** index_insert() ****************/
/* Insert item, identified by key (string), into the given index.
 * The key string is copied for use by the index.
 * Return false if key exists in ht, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool index_insert(index_t *index, const char *key,int documentID)
{ 
  //Find is a key already exists in the index data structure
  counters_t *count = hashtable_find(index->hashtable,key);
  //If count doesnt exist
  if(count==NULL){
    //Create new counters and insert into the hashtable
    count=counters_new();
    assertp(count,"Failed to create a counters object in index_insert");
    counters_add(count,documentID);
    return hashtable_insert(index->hashtable,key,count);
  }
  else{
    //If counters already exist in the index datastructure
    counters_add(count,documentID);
    return hashtable_insert(index->hashtable,key,count);
  }
}

 /**************** index_find() ****************/
/* Return the item associated with the given key;
 * return NULL if index is NULL, key is NULL, key is not found.
 */
 void *index_find(index_t *ht, const char *key)
{
  return hashtable_find(ht->hashtable,key);
} 

 /**************** index_print() ****************/
/* Print the whole table; provide the output file and func to print each item.
 * Ignore if NULL fp. Print (null) if NULL ht.
 * Print a table with no items if NULL itemprint.*/

void index_print(index_t *ht, FILE *fp,
                     void (*itemprint)(FILE *fp, const char *key, void *item))
{
  hashtable_print(ht->hashtable,fp,itemprint);
}

//   /**************** index_iterate() ****************/
/* Iterate over all items in the table; in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If ht==NULL or itemfunc==NULL, do nothing.
 */
void index_iterate(index_t *ht, void *arg,
               void (*itemfunc)(void *arg, const char *key, void *item) )
{
  hashtable_iterate(ht->hashtable,arg,itemfunc);
}

//  /**************** index_load() ****************/
/* Load an index stored in a file into an index data structure
 */
int index_load(index_t *index ,char *filePath){
//Open input file 
  FILE *fp;
  fp = fopen(filePath,"r");
  if(fp==NULL){
    fprintf(stderr, "File %s opening failed\n",filePath);
    return 2;
  }
  else{
    //Create a link to the fiel to be loaded
    char word[1000];
    //Read file and load data into index
    while(fscanf(fp,"%s",word)==1){
        int id ;
        int count;
        //Create new counters object
        counters_t *current = counters_new();
        while(fscanf(fp,"%d%d",&id,&count)==2){
          //Add ID and frequencey into a counters set
          counters_set(current,id,count);
        }
        //Add counters set to the index with key as word
        hashtable_insert(index->hashtable,word,current);
      }
    fclose(fp);
  }
  return 0;
}

//**************** index_save() ****************/
/* 
* Print out an index datastructure to a file
*/

int index_save(index_t *index,char *filePath){
  //Open file for writing
  FILE *fp = fopen(filePath, "w");
	if (fp == NULL) {
		fprintf(stderr, "index_save : failed to open file%s\n",filePath);
		return 2;
	}
  //Iterate through the index and save each item to an out put file
	index_iterate(index, fp, save_item);
	fclose(fp); 
	return 0;

}


//   /**************** index_delete() ****************/
/* Delete the whole index; ignore NULL ht.
 * Provide a function that will delete each item (may be NULL).
 */
void index_delete(index_t *ht)
{
  hashtable_delete(ht->hashtable,ct_delete);
  free(ht);
}

