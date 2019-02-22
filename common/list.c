/* 
 * list.h - header file for CS50 list module
 *
 * A list holds a collection of sorted nodes
 *
 * 
 * Louis Murerwa January 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"


/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct listnode {
  char *key;      //pointer to the address of the string key
  void *item ;		      // pointer to data for this item
  struct listnode *next;	      // link to next node
} listnode_t;

/**************** global types ****************/
typedef struct list {
  struct listnode *head;	      // head of the list of items in the list
} list_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see list.c for comments about exported functions */

/**************** local functions ****************/
/* not visible outside this file */
static listnode_t *listnode_new(const char *key ,void *item);

/**************** list_new() ****************/
/* Create a new (empty) list; return NULL if error. */
list_t *list_new(void)
{
  list_t *list = malloc(sizeof(list_t));//Create a free to free memory

  if (list == NULL) {
    return NULL; // error allocating list
  } else {
    // initialize contents of list structure
    list->head = NULL;
    return list;
  }
}

/**************** list_insert() ****************/
/* Insert item, identified by a key (string), into the given list.
 * The key string is copied for use by the list.
 * Return false if key exists, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */


bool list_insert(list_t *list, const char *key, void *item){
  
  //Check that the list is not null
  if(list==NULL || key==NULL){
    return false;
  }

//Create a list node representing dat to be inserted
  listnode_t *currentNode = listnode_new(key,item);
  listnode_t *temp ;
  //If list is empty add at the head
  if (list->head == NULL) {   
    list->head=currentNode;
    list->head->next= NULL;
  } 
  else{ 
    int *currCount = item;
    int *headCount = (list->head)->item ;
    //if item to be inserted is greater than current head.Inert before the head
    if (*headCount<*currCount){
      temp=list->head;
      list->head = currentNode;
      list->head->next = temp;
      return true;
    }
    else if(list->head->next==NULL){
      list->head->next = currentNode;
      return true;
    }
    /* Locate the node before the point of insertion */
    listnode_t *current = list->head;
    // Loop through and find the place to insert
    while (current->next!=NULL) {   
      int *nextCount = current->next->item;
      int *currCount = currentNode->item;
      if(*currCount>*nextCount){    
        break;
      }
      current = current->next; 
    } 
    currentNode->next = current->next; 
    current->next = currentNode; 
    return true;
  } 
return false;
}


/**************** listnode_new ****************/
/* Allocate and initialize a listnode */
// the 'static' modifier means this function is not visible 
// outside this file
static listnode_t *listnode_new(const char *key,void *item)
{
  listnode_t *node = malloc(sizeof(listnode_t));//Create memory for new node
  
  if (node == NULL) {
    // error allocating memory for node; return error
    return NULL;
  } else {
    node->item = item;//list the velue of item
    node->key = malloc(strlen(key)+1);//create memory for the key
    strcpy(node->key,key);//copy the value of string key
    node->next = NULL;//list next to null
    return node;
  }
}


  /**************** list_iterate() ****************/
/* Iterate over all items in the list, in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If list==NULL or itemfunc==NULL, do nothing.
 */
void list_iterate(list_t *list, void *arg,void (*itemfunc)(void *arg, const char *key, void *item) )
{
  if (list!= NULL && itemfunc != NULL) {
    // call itemfunc with arg, on each item
    for (listnode_t *node = list->head; node != NULL; node = node->next) {
      (*itemfunc)(arg,node->key, node->item); //Use itemfunc on items in the list
    }
  }
}

/* Counts the number of items stored in a list*/
int list_size(list_t *list){
  if(list==NULL){
    return 0;
  }
  int count = 0;
  for (listnode_t *node = list->head; node != NULL; node = node->next) {
    count++;
  }
  return count;
}


/* Check if a list is empty and return true if it is empty*/
bool list_isEmpty(list_t *list){
    if(list->head==NULL){
        return true;
    }
    return false;
}

/**************** bag_delete() ****************/
/* Delete the whole list; ignore NULL list.
 * Provide a function that will delete each item (may be NULL).
 */
void list_delete(list_t *list, void (*itemdelete)(void *item) )
{
  if (list != NULL) {//bad list
    for (listnode_t *node = list->head; node != NULL; ) {
      if (itemdelete != NULL ) {        // if possible...//This is used if we malloc the items before insertion.
        (*itemdelete)(node->key);     // delete node's itemm
        (*itemdelete)(node->item);
        node->key=NULL;
      }
      listnode_t *next = node->next;      // remember what comes next
      free(node);          // free the node
      node=NULL;
      node = next;         // and move on to next
    }
    free(list);//free memory held by the list
    list=NULL;

  }
}
