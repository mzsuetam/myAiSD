#include <iostream>

#include "lib/timer.h"
#include "lib/tables.h"

void altCountingSort(int A[], int n){
	// alternatywna wersja cointing sort potrafiąca sortować również liczby ujemne

	int k = 0;
	int min = 0;
	for (int i=0; i<n; i++){
		k = ( A[i] > k ) ? A[i] : k; 
		min = ( A[i] < min ) ? A[i] : min; 
	}
	k += 1 - min;
	int B[n]; // out table
	int C[k]; // count table
	for (int i=0; i<k; i++) { C[i] = 0; }

	// zliczamy ilosć wystąpień danych wartości
	for (int i=0; i<n; i++) {
		C[A[i]-min]++;
	}

	// C[i] zawiera liczbę elementów <= i
	for (int i=1; i<k; i++) {
		C[i] += C[i-1];
	}

	for (int i=n-1; i>=0; i--) {
		B[C[A[i]-min]-1] = A[i];
		C[A[i]-min]--;
	}

	for (int i=0; i<n; i++) {
		A[i] = B[i];
	}

}

void countingSort(int A[], int n){
	// dobre sortowanie dla duzej ilości całkowitych liczb nieujemnych ze stosunkowo małego zakresu
	// można zrobić alternatywną wersję potrafiącą korzystać z libcz ujemnych:
	//		należałoby 

	int k = 0;
	for (int i=0; i<n; i++){
		k = ( A[i] > k ) ? A[i] : k; 
		if ( A[i] < 0 ) return; // dane nie mogą być < 0
	}
	k++;
	int B[n]; // out table
	int C[k]; // count table
	for (int i=0; i<k; i++) { C[i] = 0; }

	// zliczamy ilosć wystąpień danych wartości
	for (int i=0; i<n; i++) {
		C[A[i]]++;
	}

	// C[i] zawiera liczbę elementów <= i
	for (int i=1; i<k; i++) {
		C[i] += C[i-1];
	}

	for (int i=n-1; i>=0; i--) {
		B[C[A[i]]-1] = A[i];
		C[A[i]]--;
	}

	for (int i=0; i<n; i++) {
		A[i] = B[i];
	}

}


int main(void){
	/////////////////

	int n=1000000;
	int range=10000;
	bool print_table=false;
	bool use_alt_counting_sort = false;

	if ( !use_alt_counting_sort ){
		int tab1[n];
		insertRandom(tab1,n,range, true);
		printTable(tab1, n, print_table);

		std::cout << "n=" << n << std::endl; 

		Timer tm;

		/////////////////

		std::cout << "Sorting with countingSort..." << std::endl;
		tm.start();
		countingSort(tab1,n);
		tm.stop();

		/////////////////
		
		printTable(tab1, n, print_table);
		tm.print();

		checkTable(tab1,n);
	}
	else{
		int tab1[n];
		insertRandom(tab1,n,range);
		printTable(tab1, n, print_table);

		std::cout << "n=" << n << std::endl; 

		Timer tm;

		/////////////////

		std::cout << "Sorting with altCountingSort..." << std::endl;
		tm.start();
		altCountingSort(tab1,n);
		tm.stop();

		/////////////////
		
		printTable(tab1, n, print_table);
		tm.print();

		checkTable(tab1,n);

	}

	return 0;
}