## Sort time of the n-element data array of (mostly) type double

Time results in table are shown in seconds.
Elements values are from range -5000, 5000
System stack size: 8192 [kb] (cmd: ulimit -all)


| Sorting					| Cmpx. average	| Cmpx. worst	|  n = 100 000	| n = 1 000 000	| Type	 | Stability| In-place	|
|:--------------------------|:--------------|:--------------|:--------------|:--------------|:-------|:---------|:----------|
| insertionSort				| O( n^2 )		| O( n^2 )		|	6.31128		|	637.653 	| cmpr.	 | Stable	| yes		|
| mergeSort (rekurenyjny)	| O( n\*log(n) )| O( n\*log(n) )|	0.017982 	|	SFCD		| cmpr.	 | Stable	| no		|
| mergeSort (iteracyjny)	| O( n\*log(n) )| O( n\*log(n) )|	0.017016 	|	SFCD		| cmpr.	 | Stable	| no		|
| heapSort					| O( n\*log(n) )| O( n\*log(n) )|	0.026897	| 	0.419463	| cmpr.	 | Unstable	| yes		|
| quickSort					| O( n*log(n) ) | O( n^2 )		|	0.010811	|	0.117219	| cmpr.	 | Unstable	| yes		|
| quickSort (random)		| O( n*log(n) ) | O( n^2 )		|	0.012149	|	0.127172	| cmpr.	 | Unstable	| yes		|
| countingSort [ int > 0 ]	| O(n+k)		| O(n+k)		|	0.001119	|	0.012347	| n-cmpr.| Stable	| no		| 
| altCountingSort [ int ]	| O(n+k)		| O(n+k)		|	0.001181	|	0.013102	| n-cmpr.| Stable	| no		| 
| radixSort (on countingSort)| O( dn+dk )	| O( dn+dk )	|	0.051841	|	0.536251	| n-cmpr.| Stable	| no		| 
| bucketSort (on std::sort)	| O(n+k)		| O(n^2) 		|	0.043327	|	SFCD		| n-cmpr.| Stable	| no		| 

Stability - sorts the elements of identical key in the same order as they appear in the input
In-place - sorted items occupy the same storage as the original ones. 

*Cmpx. - Complexity on*
*cmpr. - comparison*
*n-cmpr. - Non-comparison*
*log(n) - natural logarithm of base 2 of n*
*SFCD - Segmentation fault (core dumped)*
*n/c - not checked*

