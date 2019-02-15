/* 
 * index.h - header file for CS50 index module
 *
 * A *index* is a set of (key,item) pairs.  It acts just like a 
 * set, but is far more efficient for large collections.
 *
 * David Kotz, April 2016, 2017
 * updated by Xia Zhou, July 2016, January 2019
 */

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <stdbool.h>

/**************** global types ****************/

typedef struct index index_t;  // opaque to users of the module

/**************** functions ****************/

/* Create a new (empty) index; return NULL if error. */
index_t *index_new(const int num_slots);

/* Insert item, identified by key (string), into the given index.
 * The key string is copied for use by the index; that is, the module
 * is responsible for allocating memory for a copy of the key string, and
 * later deallocating that memory; thus, the caller is free to re-use or 
 * deallocate its key string after this call.  
 * Return false if key exists in ht, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool index_insert(index_t *ht, const char *key,int documentID);



/* Return the item associated with the given key;
 * return NULL if index is NULL, key is NULL, key is not found.
 */
void *index_find(index_t *ht, const char *key);

/* Print the whole table; provide the output file and func to print each item.
 * Ignore if NULL fp. Print (null) if NULL ht. 
 * Print a table with no items if NULL itemprint.
 */
void index_print(index_t *ht, FILE *fp, 
		     void (*itemprint)(FILE *fp, const char *key, void *item));

/* Iterate over all items in the table; in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If ht==NULL or itemfunc==NULL, do nothing.
 */
void index_iterate(index_t *ht, void *arg,
	       void (*itemfunc)(void *arg, const char *key, void *item) );

/* Load an index stored in a file into an index data structure*/
int index_load(index_t *index,char *filePath );

/* Print out an index datastructure to a file*/
int index_save(index_t *index,char* filePath);

/* Delete the whole index; ignore NULL ht.
 * Provide a function that will delete each item (may be NULL).
 */
void index_delete(index_t *ht);

#endif // __index_H
