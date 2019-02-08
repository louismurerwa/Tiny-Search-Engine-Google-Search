# Louis Murerwa
# CS 50 
# Crawler.c


## Usage: 
crawler seedURL pageDirectory maxDepth.

Example: crawler http://old-www.cs.dartmouth.edu/index.html ./data/ 2.

### Sample Command Line Output
Count 1 Depth 2 Saving http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Eleazar_Wheelock.html.

## Structure
1. main which parses arguments and calls the crawler function.
2. crawler, which loops over pages to explore, until the list is exhausted
3. fetchPage, which fetches a page from a URL
4. pageScanner, which extracts URLs from a page and processes each one
5. pageSaver, which outputs a page to the the appropriate file

### Error Messages

Code:Error
0:Success.
1:Usage:Enter three parameters.
2:Usage:Seed URL not valid.
3:Usage:Seed URL cannot be normalised.
4:Usage:%s directory doesn't exist.
5:Usage:Depth must be an a positive integer.
6:Max depth should be greater than 0.
8:File %s creation failed.


## Assumptions
Current directory input as argument must exist, or the program will return an error and quit.
All URLs to be crawled must begin with "http://old-www.cs.dartmouth.edu/~cs50/tse/". 
When server does not exist or url is not valid they are both treat as non-internal URL'S.
