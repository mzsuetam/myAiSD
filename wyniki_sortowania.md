## Sort time of the n-element data array of type double

Time results in table are shown in seconds.
System stack size: 8192 [kb] (cmd: ulimit -all)


| Sorting					| Complexity	| n = 100 000	| n = 1 000 000	|
|:--------------------------|:--------------|:-------------:|:-------------:|
| insertionSort				| O( n^2 )		|	6.31128		|	637.653 	|
| mergeSort (rekurenyjny)	| O( n*log(n) )	|	0.017982 	|	SFCD		|
| mergeSort (iteracyjny)	| O( n*log(n) )	|	0.017016 	|	SFCD		|
| heapSort					| O( n*log(n) ) |	0.026897	| 	0.419463	|

*log(n) - natural logarithm of base 2 of n*
*SFCD - Segmentation fault (core dumped)*
*n/c - not checked*

