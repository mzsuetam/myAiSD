#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "lib/timer.h"
#include "lib/tables.h"

inline size_t _random(size_t a, size_t b){
	size_t n = static_cast<size_t>(rand());
	n = a + n % ( b - a + 1);
	return n;
}

inline void _swap(double A[], size_t a, size_t b){
	double tmp = A[a];
	A[a] = A[b];
	A[b] = tmp;
}

size_t _paritition(double A[], size_t p, size_t r){
	double x = A[p]; // ustalenie miejsca podziału
	size_t i = p-1;
	size_t j = r+1;

	while (true){
		do {
			j--;
		} while ( A[j] > x ); 
		do {
			i++;
		} while ( A[i] < x ); 
		if ( i < j ){
			_swap(A,i,j);
		}
		else return j;
	}
}

size_t _randPartition(double A[], size_t p, size_t r){
	size_t i = _random(p,r);
	_swap(A,p,i);
	return _paritition(A,p,r);
}

void randQuickSort(double A[], size_t p, size_t r){
	if ( p < r ){
		size_t q = _randPartition(A,p,r); 
		// dzięki randomizacji ^ elementu dzielącego spodziewamy się,
		//		że w przypadku śrendim podział tablicy będzie dobrze zrównoważnony
		randQuickSort(A,p,q);
		randQuickSort(A,q+1,r);
	}
}

int main(void){
	/////////////////

	int n=1000000;
	int range=10000;
	bool print_table=false;

	double tab1[n];
	insertRandom(tab1,n,range);
	printTable(tab1, n, print_table);

	std::cout << "n=" << n << std::endl; 

	Timer tm;


	/////////////////

	srand( (unsigned)time(NULL) );
	std::cout << "Sorting with randQuickSort..." << std::endl;
	tm.start();
	randQuickSort(tab1,0,n-1);
	tm.stop();

	/////////////////
	
	printTable(tab1, n, print_table);
	tm.print();

	checkTable(tab1,n);

	return 0;
}