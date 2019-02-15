# Louis Murerwa
# Winter 2019


## indexer.c


> I tested this lab with too many arguments, invalid directories(non crawler directories).

>The program returned detailed error messages when the input parameters did not meet the required standards.
I tested this program on the server @flume.cs.dartmouth.edu and it worked on all the test cases and the edge cases.

>I have detailed my testing commands below and their respective outputs.


## Testing the Indexer

### Test 1: Run with a bad/non-existent directory
./indexer ../crawler/fjvioriorio  output

Usage:../crawler/fjvioriorio is not a crawler directory.

### Test 2: Run zero arguments
./indexer

Usage: /indexer [CRAWLER_DIRECTORY] [RESULTS_FILENAME]

### Test 3: Run one arguments
./indexer ../crawler/testDir

Usage: /indexer [CRAWLER_DIRECTORY] [RESULTS_FILENAME]

### Test 4: Run three arguments
./indexer ../crawler/testDir output input

Usage: /indexer [CRAWLER_DIRECTORY] [RESULTS_FILENAME]

### Test 5: Run with correct arguments
./indexer ../crawler/testDir output

Generated index data structure is printed onto the file output.

## indextest.c


### Test 1: Run with few arguments
./indextest output

Usage: /indextest [INDEX_DATASTRUCTURE_FILE] [NEW_INDEX_DATASTRUCTURE_FILE]

### Test 2: Run with incorrect file index datastructure
./indextest output1 newoutput

File output1 opening failed

### Test 3: Running with correct arguments

./indextest output  newoutput

The index datastructure in output is copied to the newoutput file

##indexertest.sh

This script runs all the tests in this testing file and outputs them to testlog.txt.The script is stored in the indexer directory.

