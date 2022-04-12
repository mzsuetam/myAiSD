#include <iostream>

#include "lib/timer.h"
#include "lib/tables.h"

int _min(int x, int y) {
    return (x < y) ? x : y;
}

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

	while((i <= q) && (i <= r)) { // dodać pozostałe elementy (jeżeli pierwsza skończyła się 2ga połowa)
		// 				^ różnica względem recursive
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

    // dzielimy A na bloki o rozmiarze `m`
    // m = [1, 2, 4, 8, 16…]
    for (int m = 1; m <= r - p; m = 2*m)
    {
        // for m = 1, i = 0, 2, 4, 6, 8…
        // for m = 2, i = 0, 4, 8…
        // for m = 4, i = 0, 8…
        // …
        for (int i = p; i < r; i += 2*m)
        {
            int from = i;
            int mid = i + m - 1; // aby nie uciekać z midem poza tablicę w _merge
								 // w przedostatnim while mamy  && (i <= r)
			int to = (i + 2*m - 1 < r) ? (i + 2*m - 1) : (r);
 
            _merge(A, from, mid, to);
        }
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

	std::cout << "Sorting with mergeSort (iterative)..." << std::endl;
	tm.start();
	mergeSort(tab1,0,n-1);
	tm.stop();

	/////////////////
	
	printTable(tab1, n, print_table);
	tm.print();

	checkTable(tab1,n);

	return 0;
}