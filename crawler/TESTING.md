# Louis Murerwa
# Winter 2019


## Crawler.c
## Testing.md



I tested this lab with too many arguments, invalid directories, URLs not in our domain, and depths out of reach.The program returned detailed error messages when the input parameters did not meet the required standards.

If the URL had been crawled already since it would be present in the hashtable, the program is silent and skips it.

I tested this program on the server @flume.cs.dartmouth.edu and it worked on all the test cases and the edge cases.

I have detailed my testing commands below and their respective outputs.


## Testing the Crawler

### Test 1: Run with bad url
./crawler http://www.cs.dartm.edu/~cs50/tse/ ./testDir/ 1

Usage:Seed URL is not an internal URL.


### Test 2: Run with bad directory
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/ ./notExist 1

Usage:./notExist directory doesn't exist.

### Test 3: Run with invalid depth
./crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ../testDir/ -4 

Usage:Depth must be an a positive integer.

### Test 4: Run with few than required parameters or more than required

./crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ../testDir/

Usage:Enter three parameters
 
### Test 5: Test the crawler with a seedURL that points to a non-existent server.

./crawler http://old-www.cs.dart.edu/~cs50/tse/ ../testDir/ 1

Usage:Seed URL not valid


### Test 5: Test the crawler with a seedURL that points to a non-internal server.

./crawler http://www.cs.dartmouth.edu/home ../testDir/ 1

Usage:Seed URL not valid

### Test 6 :the crawler with a seedURL that points to a valid server but non-existent page.

./crawler http://old-www.cs.dart.edu/djjdkd ../testDir/ 1

Usage:Seed URL not valid

### Test 7 :Crawling a closed list of pages which link back to each other 

#### Depth 1
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/ ./testDir 3

Depth 0 Saving http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/
Depth 1 Saving http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html

Move into the directory
cd testDir
Files in testDir
0  1 

#### Depth 2

./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/ ./testDir 2

Depth 0 Saving http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/
Depth 1 Saving http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
Depth 2 Saving http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
Depth 2 Saving http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html

Move into the directory
cd testDir
Files in testDir
0  1  2  3  

#### Depth 3

./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/ ./testDir 2

Depth 0 Saving http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/
Depth 1 Saving http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
Depth 2 Saving http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
Depth 2 Saving http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
Depth 3 Saving http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
Depth 3 Saving http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
Depth 3 Saving http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html

Move into the directory
cd testDir
Files in testDir
0  1  2  3  4  5  6  7 
