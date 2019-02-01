/* 
 * hashtable.c - CS50 'hashtable' module
 * hashtable.c is inspired by the design of hashtable.c by Profesor Xia and Proffesor Campbell
 *
 * see hashtable.h for more information.
 * 
 *Louis Murerwa, January 2019
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"hashtable.h"
#include"memory.h"
#include"../libcs50/set.h"
#include"jhash.h"


/**************** file-local global variables ****************/
/* none */

/**************** global types ****************/
typedef struct hashtable 
{
  set_t **hashtable; //pointer to the array of pointers to sets
  int num;      // size of the hashtable .Used to compute hash key
  
} hashtable_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see hashtable.h for comments about exported functions */

// /**************** local functions ****************/
//  not visible outside this file 

/**************** hashtable_new() ****************/

/* Create a new (empty) hashtable; return NULL if error. */
hashtable_t *hashtable_new(const int num_slots)
{ 
  hashtable_t *hashtable = malloc(sizeof(hashtable_t));
  if (hashtable == NULL) {
    return NULL; // error allocating hashtable
  } else {
    // initialize contents of hashtable structure
    hashtable->hashtable = calloc(num_slots,sizeof(set_t*));
    hashtable->num= num_slots;
    return hashtable;
  }
}


/**************** hashtable_insert() ****************/
/* Insert item, identified by key (string), into the given hashtable.
 * The key string is copied for use by the hashtable.
 * Return false if key exists in ht, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool hashtable_insert(hashtable_t *ht, const char *key, void *item)
{
  unsigned long hashkey =JenkinsHash(key,ht->num);//compute hashkey
  if(ht == NULL || key == NULL || item == NULL )
  {
    return  false;
  }
  else{
    if (ht->hashtable[hashkey] == NULL){
      // create a new set that is pointed to by the hashkey
      ht->hashtable[hashkey]=set_new();
    }
    bool inserted = set_insert(ht->hashtable[hashkey],key,item);//return true if insert has succesfully worked
    return inserted;
    }
    return false; 
}
 /**************** hashtable_find() ****************/
/* Return the item associated with the given key;
 * return NULL if hashtable is NULL, key is NULL, key is not found.
 */
 void *hashtable_find(hashtable_t *ht, const char *key)
{
  unsigned long hashkey =JenkinsHash(key,ht->num);//compute hashkey
  void *founditem;
  if (ht == NULL) {
    return NULL; // bad hashtable
  } 
  else  {
    if (ht->hashtable[hashkey]!=NULL) {  // check if set exists
        set_t *curset = ht->hashtable[hashkey];
        founditem = set_find(curset ,key);// the item to return
        return founditem;//return item
      }
    return NULL;
  }
}

 /**************** hashtable_print() ****************/
/* Print the whole table; provide the output file and func to print each item.
 * Ignore if NULL fp. Print (null) if NULL ht.
 * Print a table with no items if NULL itemprint.*/

void hashtable_print(hashtable_t *ht, FILE *fp,
                     void (*itemprint)(FILE *fp, const char *key, void *item))
{
  if(fp!=NULL) {//bad file
    if (ht == NULL) {
      printf("NULL hashtable\n");
      fputs("null", fp);
    }
    else {
    fputc('{', fp);
      for (int i = 0; i < ht->num; ++i)
      {
        if(itemprint==NULL){//bad print function
          printf("Itemprint\n");
            fputc('{', fp);
            fputc(' ', fp);
            fputc('}', fp); 
        }
        else{//print the hashtable into output file
          fputc(' ', fp);
          if(ht->hashtable[i]!=NULL){
            set_t *current = ht->hashtable[i];//access set to be printed
            set_print(current,fp,itemprint);//print set 
          }
        }
      }
    }
    fputs(" }\n", fp);
  }
}

//   /**************** hashtable_iterate() ****************/
/* Iterate over all items in the table; in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If ht==NULL or itemfunc==NULL, do nothing.
 */
void hashtable_iterate(hashtable_t *ht, void *arg,
               void (*itemfunc)(void *arg, const char *key, void *item) )
{
  if (ht!= NULL && itemfunc != NULL) {
    // call itemfunc with arg, on each item
    for (int i = 0;i <ht->num;i++) {
      set_iterate(ht->hashtable[i],arg,itemfunc);//iterate over items in each set
    }
  }
}

//   /**************** hashtable_delete() ****************/
/* Delete the whole hashtable; ignore NULL ht.
 * Provide a function that will delete each item (may be NULL).
 */
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item) )
{
  if (ht != NULL) {//check if table is good
    for (int i = 0; i < ht -> num; i++) {//iterate over slots of pointers to sets
      if (itemdelete != NULL ) {        // if possible...
        set_delete(ht->hashtable[i],itemdelete);//delete each set
      }
    }
    free(ht->hashtable);//free memory of array of pointers
    ht->hashtable=NULL;
    free(ht);//free memory of hashtable
    //ht=NULL;
  } 
}



