
## Louis Murerwa ,January 2019

## Professor Xia Zhou

## CS50 Software Development and Design.
#### Tiny Search Engine – Crawler Implemantation.

### Design

The quirer takes in a a directory containg crawler produced files numbered 0,1,2,3 .... .The crawler also takes a file containing  an index printed in a file.The indexer reads this file and builds and index which can be used to find words.

***querier.c***

Querier first continuously prompts for a query until a proper answer is typed in. The query then cleans the query out. Next the query finds the scores for the query in each document. The scores are sorted into descending order and the results are printed out.The querier also returns the URLS of the pages.

>DataStructures

* **Hash-table.**

>I used an index data-structure that uses a set for its implementation. The index data-structure stores the words, which are found in the documents created by crawler. The documents are named by ID, starting at 1 and increasing by one. The index takes an item, in this case counters. Counters for their key takes the document ID that the word was found in. The counter also keeps track of the frequencies of the word in each document. After the user inputs a query the program searches for the counts in each document.

* **Set**

>I used a set to hold my page id and word frequency.The current-set held objects that corresponded to one word.The currentSet was intersected with with andURLS set to produce the andURLS set which held objects in an and sequence.The andURLs sets were merged together after an and operator to produce the Url final set which held all objects for the query.

1. **currentSet** - Held objects corresponding to one word.
2. **andURLS** - held objects corresponding to an and sequence.
3. **Urlfinal** - held objects corresponding to the whole query.

***list.c*** in common

The data structure holds information sorted according to frequency.The orser is descending.


***High Level Pseudocode***

- Check for arguments
- Load the index from the argument into a data structure
- Read the search query from the stdin
- Clean and parse each query
- If the query is incorrect, notify the user and prompt again
- Ignore empty queries
- Identify the set of documents matching the query
- If no documents satisfy the query notify user
- Rank the results of the documents in decreasing order by match
- Exit when the query is completed or EOF is reach