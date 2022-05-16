#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

#include "lib/timer.h"
#include "lib/tables.h"

void bucketSort(double A[], int n){
	// algorytm o złożoności liniowej do sortowania liczb rzeczywistych z przedziału 0-1

	// kubełki 
	std::vector<double> B[n];

	// elementy do kubełków
	for (int i=0; i<n; i++){
		int bi = n * A[i]; // Index w kubełku
        B[bi].push_back(A[i]);
	}

	// sortowanie kubełków
    for (int i = 0; i < n; i++)
        std::sort(B[i].begin(), B[i].end());
 
    // scalenie kubełków
    int index = 0;
    for (int i = 0; i < n; i++) // po kubełkach
        for (int j = 0; j < B[i].size(); j++) // po zawartości kubełków
            A[index++] = B[i][j];


}


int main(void){
	/////////////////

	int n=1000000;
	int range=10000; // zakres 0-1, więc ...
	bool print_table=false;

	double tab1[n];
	insertRandom(tab1,n,range, true);
	for (int i=0; i<n; i++) tab1[i] /= range; // ... dzielimy przez zakres
	printTable(tab1, n, print_table);

	std::cout << "n=" << n << std::endl; 

	Timer tm;

	/////////////////

	std::cout << "Sorting with bucketSort..." << std::endl;
	tm.start();
	bucketSort(tab1,n);
	tm.stop();

	/////////////////
	
	printTable(tab1, n, print_table);
	tm.print();

	checkTable(tab1,n);

	return 0;
}