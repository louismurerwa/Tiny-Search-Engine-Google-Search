/*
 * pagedir.h - functions for TSE work with directories
 *
 * Louis Murerwa - 2019
 */

#ifndef __PAGEDIR_H
#define __PAGEDIR_H

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

#include "../libcs50/webpage.h"
#include "../libcs50/file.h"

/**************** isCrawlerDirectory ****************/
/*
 * Checks if a file named ./crawler exists in the passed crawler directory.
 * If it exists then the method return true.
 */
bool isCrawlerDirectory(char *dir);


/**************** pageSaver ****************/
/*
 * Saves a file with name count to an input pageDirectory
 * Returns 1 if the process succeeds.
 */

int pageSaver(webpage_t* page, const char* pageDirectory ,int count);

/**************** pageLoader ****************/
/*
 * Loads files stored in the crawlerOutput directory
 */
int pageLoader(char *filePath,webpage_t **webpage);

#endif // __PAGEDIR_H
