#!/bin/bash
> testoutput.txt

echo "Testing the indexer.c and indexertest.c programs" >> testoutput.txt
echo "-------------------------------------------------------------" >> testoutput.txt

echo "" >> testoutput.txt
echo "" >> testoutput.txt

echo "[" `date` "] Building the indexer..." >> testoutput.txt

echo "" >> testoutput.txt
echo "" >> testoutput.txt

echo "Testing the indexer.c  program" >> testoutput.txt

make

echo "[" `date` "] Build successful!" >> testoutput.txt

echo "Test 1: Run with a bad/non-existent directory" >> testoutput.txt
echo "Command: ../indexer ../crawler/fjvioriorio  output" >> testoutput.txt

echo "" >> testoutput.txt

./indexer ../crawler/fjvioriorio  output &>> testoutput.txt


echo "" >> testoutput.txt
echo "" >> testoutput.txt

echo "Test #2: Running with a nonexistent target directory" >> testoutput.txt
echo "Command: ./indexer dlkdjfaslkdjf test_output.dat" >> testoutput.txt

echo "" >> testoutput.txt

./indexer  &>> testoutput.txt

echo "" >> testoutput.txt
echo "" >> testoutput.txt


echo "Test #3:Run one arguments" >> testoutput.txt
echo "Command: ./indexer ../crawler/testDir " >> testoutput.txt

echo "" >> testoutput.txt

./indexer ../crawler/testDir  &>> testoutput.txt

echo "" >> testoutput.txt
echo "" >> testoutput.txt

echo "Test #4:Run three arguments" >> testoutput.txt
echo "Command: ./indexer ../crawler/testDir output input" >> testoutput.txt

echo "" >> testoutput.txt

./indexer ../crawler/testDir output input &>> testoutput.txt

echo "" >> testoutput.txt
echo "" >> testoutput.txt

echo "Test #5: Running with two valid arguments" >> testoutput.txt
echo "Expected output: a complete index file named output" >> testoutput.txt
echo "Command: ./indexer ../crawler/testDir output" >> testoutput.txt

echo "" >> testoutput.txt

./indexer ../crawler/testDir output &>> testoutput.txt

echo "" >> testoutput.txt
echo "" >> testoutput.txt

echo "Testing the indexertest.c program" >> testoutput.txt

echo "Test #6: Run with few arguments" >> testoutput.txt
echo "Command: ./indextest output" >> testoutput.txt

echo "" >> testoutput.txt
./indextest output &>> testoutput.txt

echo "" >> testoutput.txt
echo "" >> testoutput.txt

echo "Test #7: Run with incorrect file index datastructure" >> testoutput.txt
echo "Command: ./indextest output1 newoutput" >> testoutput.txt

echo "" >> testoutput.txt
./indextest output1 newoutput &>> testoutput.txt

echo "" >> testoutput.txt
echo "" >> testoutput.txt


echo "Test #8:Running with correct arguments" >> testoutput.txt
echo "Command: ./indextest output  newoutput" >> testoutput.txt

echo "" >> testoutput.txt
./indextest output newoutput &>> testoutput.txt

echo "" >> testoutput.txt
echo "" >> testoutput.txt

echo "Sorting both output from indexer.c and indexertest.c" >> testoutput.txt

cat ./output | sort > ./output_sorted;cat ./newoutput| sort > ./newoutput_sorted

echo "" >> testoutput.txt
echo "" >> testoutput.txt

echo "Testing if output.dat and newoutput are the same" >> testoutput.txt

diff ./output_sorted ./newoutput_sorted >> testoutput.txt

echo "" >> testoutput.txt
echo "" >> testoutput.txt

echo "Testing finished at" `date` >> testoutput.txt