/* 
 * counter.c - CS50 'counter' module
 * counter.c is inspired by the design of bag.c by Profesor Xia and Proffesor Campbell
 *
 * see counter.h for more information.
 * 
 *Louis Murerwa, January 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"
#include "memory.h"


/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct counternode {
  int key;      //pointer to the address of the string key
  int count;		      // pointer to count for this key
  struct counternode *next;	      // link to next node
} counternode_t;

/**************** global types ****************/
typedef struct counters {
  struct counternode *head;	      // head of the list of items in the set
} counters_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see set.c for comments about exported functions */

/**************** local functions ****************/
/* not visible outside this file */
static counternode_t *counternode_new(const int key ,int count);
static counternode_t *counter_find(counters_t *ctrs, const int key);


/**************** counter_new() ****************/
/* Create a new (empty) counter structure; return NULL if error. */
counters_t *counters_new(void)
{
  counters_t *counter = malloc(sizeof(counters_t));//Create the memory for the counter
  if (counter == NULL) {
    return NULL; // error allocating set
  } else {
    // initialize contents of set structure
    counter->head = NULL;
    return counter;
  }
}

/**************** counter_add() ****************/
/* Increment the counter indicated by key; key must be >= 0.
 * If the key does not yet exist, create a counter for it and initialize to 1.
 * Ignore if ctrs is NULL or key is negative.
 * Return the new value of the counter related to the inserted key
 */
int counters_add(counters_t *ctrs, const int key)
{
 counternode_t* found = counter_find(ctrs,key);
 if(ctrs != NULL &&  key > 0 && found ==  NULL ){
     counternode_t *new = counternode_new(key,1);//create new counter node
     if (new != NULL) {
      // add it to the head of the list
      new->next = ctrs->head;
      ctrs->head = new;
      return new->count;
    }
  }
else if(ctrs != NULL && key >= 0 ){
    // allocate a new node to be added to the list
    counternode_t *current = counter_find(ctrs,key);
    if (current != NULL) {
      // add it to the head of the list
      current->count++;//increment count of current counter
      return current->count;
    }
  }
  return 0;
}

// /**************** counter_find() ****************/
//This method is visible only in this file
static counternode_t* counter_find(counters_t *ctrs, const int key)
{
  if (ctrs == NULL) {
    return NULL; // bad ctrset
  } 
  else if (ctrs->head == NULL) {
    return NULL; // ctrs is empty
  } 
  else  {
    for (counternode_t *node = ctrs->head; node != NULL; node = node->next) {
      // look for the key
      if (node->key==key) {  
        return node;//return if key is found
      }
    }
    return NULL;
  }
}

/**************** counter_new() ****************/
/* Allocate and initialize a counternode */
// the 'static' modifier means this function is not visible 
// outside this file
static counternode_t* counternode_new(const int key , int count)
{
  
  const int newkey = key;
  int newcount = count;
  //create memory of the node
  counternode_t* node = malloc(sizeof(counternode_t));

  if (node == NULL) {
    // error allocating memory for node; return error
    return NULL;
  } else {
    node->key=newkey;
    node->count=newcount;
    return node;
  }
}

// /**************** counter_get() ****************/
/* Return current value of counter associated with the given key;
 * return 0 if ctrs is NULL or if key is not found.
 */
int counters_get(counters_t *ctrs, const int key)
{
  if (ctrs == NULL) {
    return 0; // bad ctrset
  } 
  else if (ctrs->head == NULL) {
    return 0; // ctrs is empty
  } 
  else  {
    for (counternode_t *node = ctrs->head; node != NULL; node = node->next) {
      // look for the key
      if (node->key==key) {   
        return node->count;//return count of the key if found
      }
    }
    return 0;//if not found
  }
}
// /**************** counter_set() ****************/
/* Set the current value of counter associated with the given key;
 * If the key does not yet exist, create a counter for it and initialize to
 * the given value. Ignore if ctrs is NULL, if key < 0, or count < 0.
 */
void counters_set(counters_t *ctrs, const int key, int count)
{
  if(ctrs != NULL || key >= 0 || count >= 0){
    counternode_t *current = counter_find(ctrs,key);//find the count of key
    if (current == NULL) {
      counternode_new(key,count);//create count of key if it doesnt exist
    }
    else {

      current->count = count;//set the count to a new value

    }
  }
}
// *************** counter_print() ****************
//  Print all counters; provide the output file.
//  * Ignore if NULL fp. Print (null) if NULL ctrs.

void counters_print(counters_t *ctrs, FILE *fp)
{
  if (ctrs == NULL) {
    fputs("null", fp);//bad ctrs
  }
  else if (ctrs->head == NULL) {
    fputs("Empty\n ",fp);//empty ctrs
  }
  else {
    fputc('{', fp);
    for (counternode_t *node = ctrs->head; node != NULL; node = node->next){//loop over every counternode
          fputc(' ', fp);
          fprintf(fp, "\"%d : %d\"", node->key ,node->count); //print the key and count
    }
  }
    fputs(" }\n", fp);
}

// *************** counter_print() ****************/
 //   Iterate over all counters in the set (in undefined order):
 // * call itemfunc for each item, with (arg, key, count).
 // * If ctrs==NULL or itemfunc==NULL, do nothing.
 
void counters_iterate(counters_t *ctrs, void *arg,
                      void (*itemfunc)(void *arg, const int key, int count)){

  if (ctrs!= NULL && itemfunc != NULL) {
    // call itemfunc with arg, on each item
    for (counternode_t *node = ctrs->head; node != NULL; node = node->next) {
      (*itemfunc)(arg,node->key, node->count); 
    }
  }
}

// /* Delete the whole counters. ignore NULL ctrs. 
void counters_delete(counters_t *ctrs){
  if (ctrs != NULL) {
    for (counternode_t *node = ctrs->head; node != NULL;){
      counternode_t *next = node->next;      // remember what comes next
      free(node);          // free the node
      node=NULL;
      node = next;         // and move on to next
    }
    free(ctrs);//free ctrs
    ctrs=NULL;
}
}







