/* 
 * set.c - CS50 'set' module
 * set.c is inspired by the design of bag.c by Profesor Xia and Proffesor Campbell
 *
 * see set.h for more information.
 * 
 *Louis Murerwa, January 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "memory.h"


/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct setnode {
  char *key;      //pointer to the address of the string key
  void *item;		      // pointer to data for this item
  struct setnode *next;	      // link to next node
} setnode_t;

/**************** global types ****************/
typedef struct set {
  struct setnode *head;	      // head of the list of items in the set
} set_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see set.c for comments about exported functions */

/**************** local functions ****************/
/* not visible outside this file */
static setnode_t *setnode_new(const char *key ,void *item);

/**************** set_new() ****************/
/* Create a new (empty) set; return NULL if error. */
set_t *set_new(void)
{
  set_t *set = count_malloc(sizeof(set_t));//Create a free to free memory

  if (set == NULL) {
    return NULL; // error allocating set
  } else {
    // initialize contents of set structure
    set->head = NULL;
    return set;
  }
}

/**************** set_insert() ****************/
/* Insert item, identified by a key (string), into the given set.
 * The key string is copied for use by the set.
 * Return false if key exists, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */

bool set_insert(set_t *set, const char *key, void *item)
{
  if(set == NULL || item == NULL || key == NULL ){//check for NULL inputs
    return  false;

  }
  else{
    // allocate a new node to be added to the list
    setnode_t *new = setnode_new(key,item);
    if (new != NULL) {
      // add it to the head of the list
      new->next = set->head;
      set->head = new;
      return true;
    }
    return false; 
  }
}

/**************** setnode_new ****************/
/* Allocate and initialize a setnode */
// the 'static' modifier means this function is not visible 
// outside this file
static setnode_t *setnode_new(const char *key,void *item)
{
  setnode_t *node = count_malloc(sizeof(setnode_t));//Create memory for new node
  
  if (node == NULL) {
    // error allocating memory for node; return error
    return NULL;
  } else {
    node->item = item;//set the velue of item
    node->key = count_malloc(strlen(key)+1);//create memory for the key
    strcpy(node->key,key);//copy the value of string key
    node->next = NULL;//set next to null
    return node;
  }
}

// /**************** set_find() ****************/
/* Return the item associated with the given key;
 * return NULL if set is NULL, key is NULL, or key is not found.
 */
void *set_find(set_t *set, const char *key)
{
  if (set == NULL) {
    return NULL; // bad set
  } 
  else if (set->head == NULL) {
    return NULL; // set is empty
  } 
  else  {
    for (setnode_t *node = set->head; node != NULL; node = node->next) {// look for the key
      
      if (strcmp(node->key,key)==0) {  // check if the string values are equal
        void *item = node->item; // the item to return
        return item;
      }
    }
    return NULL;
  }
}

// /**************** set_print() ****************/
/* Print the whole set; provide the output file and func to print each item.
 * Ignore if NULL fp. Print (null) if NULL set.
 * Print a set with no items if NULL itemprint.
 */
void set_print(set_t *set, FILE *fp,void (*itemprint)(FILE *fp, const char *key, void *item))
{
  if (set == NULL) {//bad set
    fputs("null", fp);
  }
   else if (set->head == NULL) {//empty set
    printf("Empty\n ");
   
  } 
  else if (itemprint == NULL){//null itemprint
    fputc('{', fp);
    fputc(' ', fp);
    fputc('}', fp);    
  }
  else {//print the contents of the set
    fputc('{', fp);
    for (setnode_t *node = set->head; node != NULL; node = node->next){//iterate over the contents of the set
          fputc(' ', fp);
          (*itemprint)(fp,node->key, node->item);//print the items in the set
    }
  }
    fputs(" }\n", fp);
}

  /**************** set_iterate() ****************/
/* Iterate over all items in the set, in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If set==NULL or itemfunc==NULL, do nothing.
 */
void set_iterate(set_t *set, void *arg,void (*itemfunc)(void *arg, const char *key, void *item) )
{
  if (set!= NULL && itemfunc != NULL) {
    // call itemfunc with arg, on each item
    for (setnode_t *node = set->head; node != NULL; node = node->next) {
      (*itemfunc)(arg,node->key, node->item); //Use itemfunc on items in the set
    }
  }
}

/**************** bag_delete() ****************/
/* Delete the whole set; ignore NULL set.
 * Provide a function that will delete each item (may be NULL).
 */
void set_delete(set_t *set, void (*itemdelete)(void *item) )
{
  if (set != NULL) {//bad set
    for (setnode_t *node = set->head; node != NULL; ) {
      if (itemdelete != NULL ) {        // if possible...//This is used if we malloc the items before insertion.
        (*itemdelete)(node->item);     // delete node's itemm
        node->item=NULL;
      }
      free(node->key);//free node key
      node->key=NULL;
      setnode_t *next = node->next;      // remember what comes next
      count_free(node);          // free the node
      node=NULL;
      node = next;         // and move on to next
    }
    count_free(set);//free memory held by the set
    set=NULL;

  }
}
