#include <iostream>

#include "lib/timer.h"
#include "lib/tables.h"

class MaxHeap{
private:

double* A;

int _size;

int _parent(int ind){ return ind/2-1; } // podłoga z indeksu dziecka/2 to rodzic przy numeracji od 1 (przesunięcie o 1 bo 0)

int _left(int ind){	return ind*2+1; } // lewe dziecko to 2*indeks_rodzica przy numeracji od 1 (przesunięcie o 1 bo 0)

int _right(int ind){ return ind*2+2; } // prawe dziecko to 2*indeks_rodzica+1 przy numeracji od 1 (przesunięcie o 1 bo 0)

void _heapify(int ind){
	// podajemy indeks elementu, który razem z dziećmi nie zachowuje własności kopca,
	// a jego dzieci ze swoimi potomkami zachowują

	int largest=ind;
	int l = _left(ind);
	int r = _right(ind);

	// decydujemy, która z wartości (rodzic, prawy potomek, lewy potomek) jest największa (przy okazji czy nie wychodzą poza wiekość)
	if ( ( l <= _size-1 ) && ( A[l] >= A[largest]) ){
		largest=l;
	}
	if ( ( r <= _size-1 ) && ( A[r] >= A[largest] ) ){
		largest=r;
	}

	// jeżeli największy nie jest rodzicem, to zamieniamy go miejscami z rodzicem
	if ( largest != ind ){
		double tmp = A[ind];
		A[ind] = A[largest];
		A[largest] = tmp;

		// badany węzeł zachowuje już własność kopca, ale 'spływająca' najmniejsza wartość
		// mogła zaburzyć własność w niższym węźle, więc ją naprawiamy
		_heapify(largest);
	}
}

public:

MaxHeap(){}
MaxHeap(double tab[], int n){ buildHeap(tab,n); }
~MaxHeap(){}

void buildHeap(double tab[], int n){

	// przypisujemy tablice
	A=tab;

	// zapisujemy wielkość tablicy
	_size=n;

	// budujemy z niej kopiec
	for (int i=_size/2; i >= 0; i--){
		_heapify(i);
	}
}

void sort(){
	// kolejno od końca zamieniamy wszystkie wartości z aktualnie największą (ind 0),
	// a następnie kopcujemy się przez kopiec bez wyciągniętej wartości 
	for (int i=_size-1; i>0; i--){
		double tmp = A[i];
		A[i] = A[0];
		A[0] = tmp;

		_size--;
		_heapify(0);

	}
	// finalnie otrzymując posortowaną tablicę
}

};

void heapSort(double tab[], int n){

	MaxHeap* heap = new MaxHeap; // korzystamy z ograniczonego do _heapify() i buildHeap() MaxHeap operującego na wskaźniku
	// tworzymy kopiec z tablicy
	
	heap->buildHeap(tab, n);

	// sortujemy 
	heap->sort();
	// usuwamy zbędną strukturę
	delete heap;
}

///////////////////////////////////////////////////////////////////////////////////

int main(){	

	int n=1000000;
	int range=10000;
	bool print_table=false;

	double tab1[n];
	insertRandom(tab1,n,range);
	printTable(tab1, n, print_table);

	std::cout << "n=" << n << std::endl; 

	Timer tm;

	/////////////////

	std::cout << "Sorting with heapSort..." << std::endl;
	tm.start();
	heapSort(tab1,n);
	tm.stop();

	/////////////////
	
	printTable(tab1, n, print_table);
	tm.print();

	checkTable(tab1,n);

	return 0;
}