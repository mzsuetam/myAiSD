#include <iostream>

#include "lib/timer.h"
#include "lib/tables.h"

void insertionSort(double A[], int n){
	for (int j=1; j<n; j++){ // zaczynamy od indesku 1, żeby mieć z czym porównać
		double key = A[j];
		int i = j-1;
		while (i>=0 && A[i]>key){ // przechodzimy po już posortowanej tablicy od góry szukając miejsca dla key
			A[i+1]=A[i];
			i--;
		}
		A[i+1]=key;
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

	std::cout << "Sorting with insertionSort..." << std::endl;
	tm.start();
	insertionSort(tab1,n);
	tm.stop();

	/////////////////
	
	printTable(tab1, n, print_table);
	tm.print();

	checkTable(tab1,n);

	return 0;
}