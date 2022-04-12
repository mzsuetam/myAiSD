#include <iostream>

#include "lib/timer.h"
#include "lib/tables.h"

void _merge(double A[], int p, int q, int r){
	double tmp[r - p + 1]; // tworzymy tablicę na sortowane wartości

	int i = p, j = q+1, k = 0; // ustawiamy iteratory na początku obudwu połówek

	while(i <= q && j <= r) { // przejść po tablicach i zapisać do tmp mniejszy z kolejno porównywanych
		if(A[i] <= A[j]) {
			tmp[k] = A[i];
			i += 1;
		}
		else {
			tmp[k] = A[j];
			j += 1;
		}
		k += 1;
	}

	while(i <= q) { // dodać pozostałe elementy (jeżeli pierwsza skończyła się 2ga połowa)
		tmp[k] = A[i];
		i += 1;
		k += 1;
	}

	while(j <= r) { // dodać pozostałe elementy (jeżeli pierwsza skończyła się 1sza połowa)
		tmp[k] = A[j];
		j += 1;
		k += 1;
	}

	for(i = p; i <= r; i++) { // wpisać posortowane wartości do tablicy
		A[i] = tmp[i - p];
	}
}

void mergeSort(double A[], int p, int r){
	// przekazujemy granice przedziału do sortowania

	if ( p < r ){ // jeżeli p==r, to tablica ma 1 element => jest posortowana
		int q = (p+r)/2; // wyznaczamy środek przedziału (int zaokrągli do całkowitej wartości)

		mergeSort(A,p,q); // sortujemy pierwsze pół
		mergeSort(A,q+1,r); // sortujemy drugie pół
		_merge(A,p,q,r); // scalamy posortowane połówki
	}

}

int main(void){
	/////////////////

	int n=100000;
	int range=10000;
	bool print_table=false;

	double tab1[n];
	insertRandom(tab1,n,range);
	printTable(tab1, n, print_table);

	std::cout << "n=" << n << std::endl; 

	Timer tm;

	/////////////////

	std::cout << "Sorting with mergeSort (recursive)..." << std::endl;
	tm.start();
	mergeSort(tab1,0,n-1);
	tm.stop();

	/////////////////
	
	printTable(tab1, n, print_table);
	tm.print();

	checkTable(tab1,n);

	return 0;
}