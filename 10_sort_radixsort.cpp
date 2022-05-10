#include <iostream>
#include <cmath>
#include <algorithm>

#include "lib/timer.h"
#include "lib/tables.h"

char _toChar(int input, int dmax, int d){
	// oddaje char z cyfry na pozycji d z liczby input 
	char out;
	std::string key_str = std::to_string(input);
	int diff = key_str.length()-dmax;
	out = ( d >= static_cast<int>(dmax - key_str.length()) ) ? key_str[d+diff] : '0';
	return out;
}

void _countingSort(int A[], int n, int dmax, int d){
	// korzystamy z counting sort, bo możliwych jest tylko mała liczba znaków - stąd złożoność O(n+k)
	// trzeba zastosować podmianę A[i] na _toChar(A[i],dmax, d)

	char k;
	for (int i=0; i<n; i++){
		k = ( _toChar(A[i],dmax, d) > k ) ? _toChar(A[i],dmax, d) : k; 
		//if ( A[i] < 0 ) return;
	}
	k++;
	int B[n];
	int C[k];
	for (int i=0; i<k; i++) { C[i] = 0; }

	for (int i=0; i<n; i++) {
		C[static_cast<std::size_t>(_toChar(A[i],dmax, d))]++;
	}

	for (int i=1; i<k; i++) {
		C[i] += C[i-1];
	}

	for (int i=n-1; i>=0; i--) {
		B[C[static_cast<std::size_t>(_toChar(A[i],dmax, d))]-1] = A[i];
		C[static_cast<std::size_t>(_toChar(A[i],dmax, d))]--;
	}

	for (int i=0; i<n; i++) {
		A[i] = B[i];
	}

}

void radixSort(int A[], int n){
	// szybki algorytm robiący d (max ilość cyfr w liczbach) sortowań o złożoności O(n+k)
	int d = log10(*std::max_element(A , A + n)) + 1;
	for (int i=0; i<d; i++){
		//_insertionSort(A,n,d,d-i-1);
		_countingSort(A,n,d,d-i-1);
	}
}

int main(void){
	/////////////////

	int n=1000000;
	int range=10000;
	bool print_table=false;

	int tab1[n];
	insertRandom(tab1,n,range,true);
	printTable(tab1, n, print_table);

	std::cout << "n=" << n << std::endl; 

	Timer tm;

	/////////////////

	std::cout << "Sorting with radixSort..." << std::endl;
	tm.start();
	radixSort(tab1,n);
	tm.stop();

	/////////////////
	
	printTable(tab1, n, print_table);
	tm.print();

	checkTable(tab1,n);

	return 0;
}