## Louis Murerwa ,January 2019

## Professor Xia Zhou

## CS50 Software Development and Design.
#### Tiny Search Engine – Crawler Implemantation.

>**Error Verificiation.**
All the cases below test for invalid output. In each case the expected result returned. I test for invalid arguments first. Then I check for if the files don't exist. Finally I test for invalid queries.
```
[louis@flume querier]$ ./querier
Usage: /querier [CRAWLER_DIRECTORY] [INDEX_FILENAME] 

[louis@flume querier]$ ./querier pagedir
Usage: /querier [CRAWLER_DIRECTORY] [INDEX_FILENAME] 

[louis@flume querier]$ ./querier pagedir indexfile
Usage:pagedir is not a crawler directory.

[louis@flume querier]$ ./querier ../crawler/testDir indexfile
File indexfile doesnot exist

[louis@flume querier]$ ./querier ../crawler/testDir ../indexer/output
Enter your query: 

and 
Error:First word in query is an 'and' operator

or 
Error:First word in query is an 'or' operator

and dartmouth
Error:First word in query is an 'and' operator

or dartmouth 
Error:First word in query is an 'or' operator

dartmouth college or 
Error:Last word word in query is an 'or' operator

dartmouth college and 
Error:Last word word in query is an 'and' operator

dartmouth college and or computer 
Usage:Two concecutive operators in query.'and' and 'or' are 
consequtive.

dartmouth college and and computer 
Usage:Two concecutive operators in query.'and' and 'and' are 
consequtive.

dartmouth college or and computer
Usage:Two concecutive operators in query.'or' and 'and' are consequtive.

computer science 50
Error:'50' conatains a non-Alpahanumeric character

Dartmouth!
Error:'Dartmouth!' conatains a non-Alpahanumeric character

Backus-Naur Form
Error:'Backus-Naur' conatains a non-Alpahanumeric character

```

>**Testing searches.**
>I tested searches to see if the results were accurate and consistent. I first tested Dartmouth College. Querier should treat this as "dartmouth and college". Next I tested for Dartmouth and college individually. Then I tested for Dartmouth or college and simple addition will verify that the results are consistent. Finally I explicitly said Dartmouth and College and this was the same result as the first search. Finally I tried searching for my name and unexpectedly there were some matching documents.

```
[louis@flume querier]$ ./querier ../crawler/testDir ../indexer/output
Enter your query:

Query: dartmouth college
Matches 3 ranked (ranked) :
score 242 doc 4: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Dartmouth_College.html
score 1 doc 7: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html
score 1 doc 1: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/

Query: dartmouth
Matches 3 ranked (ranked) :
score 416 doc 4: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Dartmouth_College.html
score 1 doc 7: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html
score 1 doc 1: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/

Query: college
Matches 4 ranked (ranked) :
score 242 doc 4: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Dartmouth_College.html
score 2 doc 7: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html
score 1 doc 2: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Linked_list.html
score 1 doc 1: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/

Query: dartmouth or college
Matches 4 ranked (ranked) :
score 658 doc 4: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Dartmouth_College.html
score 3 doc 7: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html
score 2 doc 1: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/
score 1 doc 2: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Linked_list.html
[schaudhary@flume ~/cs50/labs/tse/querier]$ querier ../crawler/data ../indexer/file1

Query: dartmouth and college
Matches 3 ranked (ranked) :
score 242 doc 4: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Dartmouth_College.html
score 1 doc 7: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html
score 1 doc 1: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/

Query: louis murerwa
No documents match

Query:louis or murerwa
Matches 2 ranked (ranked) :
score 2 doc 7: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html
score 1 doc 4: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Dartmouth_College.html

Query: louis
Matches 2 ranked (ranked) :
score 2 doc 7: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html
score 1 doc 4: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Dartmouth_College.html

Additional Information
There were no memory leaks, which was tested with valgrind.

```


![Minion](https://octodex.github.com/images/minion.png)
![Stormtroopocat](https://octodex.github.com/images/stormtroopocat.jpg "The Stormtroopocat")



![Alt text][id]


[id]: https://octodex.github.com/images/dojocat.jpg  "The Dojocat"