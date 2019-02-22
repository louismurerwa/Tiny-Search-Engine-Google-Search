/* 
 * list.h - header file for CS50 list module
 *
 * A list holds a collection of sorted nodes
 *
 * 
 * Louis Murerwa January 2019
 */


#ifndef __LIST_H
#define __LIST_H

#include <stdio.h>
#include <stdbool.h>
#include <stdbool.h>

/**************** global types ****************/
typedef struct list list_t;  // opaque to users of the module

/**************** functions ****************/

/* Create a new (empty) list; return NULL if error. */
list_t *list_new(void);

/* Insert item, identified by a key (string), into the given list.
 * The key string is copied for use by the list; that is, the module
 * is responsible for allocating memory for a copy of the key string, and
 * later deallocating that memory; thus, the caller is free to re-use or 
 * deallocate its key string after this call.  
 * Return false if key exists, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool list_insert(list_t *list, const char *key, void *item);


/* Iterate over all items in the list, in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If list==NULL or itemfunc==NULL, do nothing.
 */
void list_iterate(list_t *list, void *arg,
		 void (*itemfunc)(void *arg, const char *key, void *item) );


/* Counts the number of items stored in a list*/
int list_size(list_t *list);


/* Check if a list is empty and return true if it is empty*/
bool list_isEmpty(list_t *list);

/* Delete the whole list; ignore NULL list.
 * Provide a function that will delete each item (may be NULL).
 */
void list_delete(list_t *list, void (*itemdelete)(void *item) );

#endif // __list_H