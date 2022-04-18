#include <iostream>
#include <random>
#include <vector>

class Heap{
private:

std::vector<double> A;

int _size; // wielkość kopca 
// uwaga! kopiec nie korzysta z indeksu 0, tablica jest przesunięta o 1 w prawo 


int _parent(int ind){ return ind/2; } // podłoga z indeksu dziecka/2 to rodzic

int _left(int ind){	return ind*2; } //indeks rodzica*2 to lewe dziecko

int _right(int ind){ return ind*2+1; } //indeks rodzica*2+1 to prawe dziecko

public:

Heap(){ A.push_back(static_cast<double>(NULL)); }
~Heap(){}

int getSize(){ return _size; }

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
		A.push_back(tab[i-1]);
	}
	// budujemy z niej kopiec
	for (int i=_size/2; i > 0; i--){
		heapify(i);
	}
}

void insert(double val){
	A.push_back(val);
	_size++;
	// naprawiamy kopiec
	for (int i=_size/2; i > 0; i--){
		heapify(i);
	}
}

void printHeap(){
	// chciałbym to ja to napisać XD
	int height = log2(_size) + 1;

	for (int i = 1; i < _size+1; i++) {
		int level = log2(i) + 1;
		int spaces = pow(2,(height - level + 1));
		if ( level > 4 ) spaces *=2;

		if (((int)pow(2, level-1)+(int)pow(2, level))/2 == i) {
			for (int j=0; j<spaces/2+(height-level)*2; j++){
				std::cout << " ";
			}
		}
		else{
			for (int j=0; j<spaces; j++){
				std::cout << " ";
			}	
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

///////////////////////////////////////////////////////////////////////////////////

int main(){

	int n=13;
	double tab1[n] = {5,1,2,3,4,0,6,2,5,3,2,8,9};
	
	Heap* heap1 = new Heap;

	heap1->buildHeap(tab1, n);

	//heap1->printTable();
	//heap1->printHeap();

	heap1->insert(1);
	heap1->insert(0);

	heap1->printHeap();



	return 0;
}