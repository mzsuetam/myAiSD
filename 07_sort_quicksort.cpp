#include <iostream>

#include "lib/timer.h"
#include "lib/tables.h"

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

void quickSort(double A[], size_t p, size_t r){
	if ( p < r ){
		size_t q = _paritition(A,p,r);
		quickSort(A,p,q);
		quickSort(A,q+1,r);
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

	std::cout << "Sorting with quickSort..." << std::endl;
	tm.start();
	quickSort(tab1,0,n-1);
	tm.stop();

	/////////////////
	
	printTable(tab1, n, print_table);
	tm.print();

	checkTable(tab1,n);

	return 0;
}