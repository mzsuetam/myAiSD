#include <iostream>
#include <random>

class Heap{
private:

double A[1000+1]; // tutaj zrobić std::vector
int _max_size=1000; // wielkość tablicy (bez pierwszego elementu)

int _size; // wielkość kopca 
// uwaga! kopiec nie korzysta z indeksu 0, tablica jest przesunięta o 1 w prawo 


int _parent(int ind){ return ind/2; } // podłoga z indeksu dziecka/2 to rodzic

int _left(int ind){	return ind*2; } //indeks rodzica*2 to lewe dziecko

int _right(int ind){ return ind*2+1; } //indeks rodzica*2+1 to prawe dziecko

public:

int getSize(){ return _size; }
int getMaxSize(){ return _max_size; }

void heapify(int i){
	// podajemy indeks elementu, który razem z dziećmi nie zachowuje własności kopca,
	// a jego dzieci ze swoimi potomkami zachowują

	int largest=i;
	int l = _left(i);
	int r = _right(i);

	// decydujemy, która z wartości (rodzic, prawy potomek, lewy potomek) jest największa
	if ( ( l <= _size+1 ) && ( A[l] >= A[largest]) ){
		largest=l;
	}
	if ( ( r <= _size+1 ) && ( A[r] >= A[largest] ) ){
		largest=r;
	}

	// jeżeli największy nie jest rodzicem, to zamieniamy go miejscami z rodzicem
	if ( largest != i ){
		double tmp = A[i];
		A[i] = A[largest];
		A[largest] = tmp;

		// badany węzeł zachowuje już własność kopca, ale 'spływająca' najmniejsza wartość
		// mogła zaburzyć własność w niższym węźle, więc ją naprawiamy
		heapify(largest);
	}
}

void buildHeap(double tab[], int n){
	// zapisujemy wielkość tablicy
	_size=n;
	// przepisujemy to przetrzymywanej tablicy wartości z zadanej
	for (int i=1; i<_size+1; i++){
		A[i] = tab[i-1];
	}
	// budujemy z niej kopiec
	for (int i=n/2; i > 0; i--){
		heapify(i);
	}
}

void printHeap(){
	// chciałbym to ja to napisać XD
	int height = log2(_size) + 1;

	for (int i = 1; i < _size+1; i++) {
		int level = log2(i) + 1;
		int spaces = (height - level + 1) * 2;

		for (int j=0; j<spaces; j++){
			std::cout << " ";
		}
		std::cout << A[i];

		if ((int)pow(2, level) - 1 == i) {
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}

void printTable(){
	// o, to sam napisałem XD
	for (int i=1; i<_size+1; i++){
		std::cout << A[i] << " ";
	}
	std::cout << std::endl;
}

};

int main(){

	int n=10;
	double tab1[n] = {5,1,2,3,4,0,6,7,8,9};
	
	Heap* heap1 = new Heap;

	heap1->buildHeap(tab1, n);

	heap1->printTable();
	heap1->printHeap();



	return 0;
}