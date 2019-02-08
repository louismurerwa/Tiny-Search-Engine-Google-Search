
#Louis Murerwa
#Winter 2019
##Crawler.c
##IMPLEMANTATION

These are the steps I took inorder to implement this crawler

1.execute from a command line as shown in the User Interface
2.parse the command line, validate parameters, initialize other modules
3.call crawler with the parameters passed from command line
	-Initialize bag and hash table data structures.
	-make a webpage for the seedURL, marked with depth=0
	-bag holds pages to be explored and url holds urls already visited
	-Loop through the bag and while there are more pages in the bag
		-extract a webpage (URL,depth) item from the bag of webpages to be crawled
		-add the URL of the cerrent page to the hashtable of URLs seen
		-use pagefetcher to retrieve a webpage for that URL
		-use pagesaver to write the webpage to the pageDirectory with a unique document ID, as described in the Requirements
		-increase the count of pages saved
		-if the webpage depth is < maxDepth, explore the webpage to find links:
		-use pagescanner to parse the webpage to extract all its embedded URLs;
		-stored the extracted URLs in a bag
	-delete the webpage
	-delete the datastructures
	-return



4.pagefetcher
	-fetch the webpage of the page and stored in the variable in page itself
5.pageSaver
	-create the path of the file to be created
	-create the file
	-save page url,depth,and html to the file
	-close the file
6.pageScanner
	-scan page for URLs
	-for each url scanned
		-normalise the scaned Url
		-create a webpage of the url and insert it into the bag
