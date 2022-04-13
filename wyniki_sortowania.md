## Czas sortowania n elementowej tablicy danych typu double

Czas w tabeli podany jest w sekundach.
Wielkość stosu w systemie: 8192 [kb] (cmd: ulimit -all)


|   SORTOWANIE				|   ZŁOŻONOŚĆ	| n = 100 000	| n = 1 000 000	| n = 10 000 000 |
|:--------------------------|:--------------|:-------------:|:-------------:|:-------------:|
| insertionSort				| O( n^2 )		|	6.31128		|	637.653 	|	n/c			|
| mergeSort (rekurenyjny)	| O( n*log(n) )	|	0.017982 	|	SFCD		|	SFCD		|
| mergeSort (iteracyjny)	| O( n*log(n) )	|	0.017016 	|	SFCD		|	SFCD		|

*log(n) - logarytm naturalny o podstawie 2 z n ( log_2(n) )*
*SFCD - Segmentation fault (core dumped)*
*n/c - nie sprawdzane*

