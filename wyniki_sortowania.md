## Sort time of the n-element data array of type double

Time results in table are shown in seconds.
System stack size: 8192 [kb] (cmd: ulimit -all)


| Sorting					| Cmp. average 	|Cmp. worst		|  n = 100 000	| n = 1 000 000	| Stability	| In-place	|
|:--------------------------|:--------------|:--------------|:--------------|:--------------|:----------|:----------|
| insertionSort				| O( n^2 )		|O( n^2 )		|	6.31128		|	637.653 	| Stable	| yes		|
| mergeSort (rekurenyjny)	| O( n\*log(n) )| O( n\*log(n) )|	0.017982 	|	SFCD		| Stable	| no		|
| mergeSort (iteracyjny)	| O( n\*log(n) )| O( n\*log(n) )|	0.017016 	|	SFCD		| Stable	| no		|
| heapSort					| O( n\*log(n) )| O( n\*log(n) )|	0.026897	| 	0.419463	| Unstable	| yes		|
| quickSort					| O( n*log(n) ) | O( n^2 )		|	0.010811	|	0.117219	| Unstable	| yes		|
| quickSort (random)		| O( n*log(n) ) | O( n^2 )		|	0.012149	|	0.127172	| Unstable	| yes		|

Stability - sorts the elements of identical key in the same order as they appear in the input
In-place - sorted items occupy the same storage as the original ones. 

*Cmp. - Complexity on*

*log(n) - natural logarithm of base 2 of n*
*SFCD - Segmentation fault (core dumped)*
*n/c - not checked*

