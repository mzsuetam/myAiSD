#include <iostream>
#include <random>
#include <vector>

class MaxHeap{
private:

std::vector<double> A;

int _size;

int _parent(int ind){ return (ind-1)/2; } // podłoga z indeksu dziecka/2 to rodzic przy numeracji od 1 (przesunięcie o 1 bo 0)

int _left(int ind){	return ind*2+1; } // lewe dziecko to 2*indeks_rodzica przy numeracji od 1 (przesunięcie o 1 bo 0)

int _right(int ind){ return ind*2+2; } // prawe dziecko to 2*indeks_rodzica+1 przy numeracji od 1 (przesunięcie o 1 bo 0)

void _heapify(int ind){
	// podajemy indeks elementu, który razem z dziećmi nie zachowuje własności kopca,
	// a jego dzieci ze swoimi potomkami zachowują

	int largest=ind;
	int l = _left(ind);
	int r = _right(ind);

	// decydujemy, która z wartości (rodzic, prawy potomek, lewy potomek) jest największa (przy okazji czy nie wychodzą poza wiekość)
	if ( ( l <= _size-1 ) && ( A[l] > A[largest]) ){ // nie >= bo nie chemy zamieniać specjalnie jak nie trzeba
		largest=l;
	}
	if ( ( r <= _size-1 ) && ( A[r] > A[largest] ) ){
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

MaxHeap(){ std::cout << "MaxHeap constructed (empty)." << std::endl;}
MaxHeap(double tab[], int n){ std::cout << "MaxHeap constructed." << std::endl; buildHeap(tab,n); }
~MaxHeap(){ std::cout << "MaxHeap destructed." << std::endl; }

void buildHeap(double tab[], int n){
	A.clear();

	// zapisujemy wielkość tablicy
	_size=n;

	// przepisujemy to przetrzymywanej tablicy wartości z zadanej
	for (int i=0; i<_size; i++){
		A.push_back(tab[i]);
	}
	// budujemy z niej kopiec
	for (int i=_size/2; i >= 0; i--){
		_heapify(i);
	}

	std::cout << "MaxHeap has been built from table." << std::endl; 
}

void insert(double val){
	A.push_back(val);
	_size++;
	// przechodzimy z wartością na odpowiednie miejsce
	int i = _size-1;
	while ( ( i > 0 ) && ( A[_parent(i)] < val ) ){
		A[i] = A[_parent(i)];
		i = _parent(i);
	}
	A[i]=val;
	// naprawiamy kopiec (to rozwiązanie jest gorsze od powyższego)
	// for (int i=_size/2; i >= 0; i--){
	// 	_heapify(i);
	// }

	std::cout << "Value " << val << " has been added." << std::endl; 
}

void erase(int ind){
	// to chyba nie jest najbardziej optymalny sposób

	if ( ( 0 <= ind ) && ( ind < _size ) ){
		std::cout << "Value under index " << ind << " (" << A[ind] << ") has been deleted." << std::endl; 

		A[ind] = A[_size-1];
		A.pop_back();
		// naprawiamy kopiec
		_heapify(ind);
	}
	else std::cout << "No such index in MaxHeap!" << std::endl;
}

int getSize(){ return _size; }

double getMax() {
	if ( _size > 0 ){
		return A[0]; 
	}
	else std::cout << "MaxHeap empty!" << std::endl;
	return -1;
}

void printHeap(){
	// chciałbym to ja to napisać XD
	int height = log2(_size) + 1;
	for (int i = 1; i < _size+1; i++) {
		int level = log2(i) + 1;
		int spaces = pow(2,(height - level + 1));
		if ( level > 4 ) spaces *=2;
		if (((int)pow(2, level-1)+(int)pow(2, level))/2 == i) { for (int j=0; j<spaces/2+(height-level)*2; j++){ std::cout << " "; } }
		else{ for (int j=0; j<spaces; j++){ std::cout << " "; }	}
		std::cout << A[i-1];
		if ( i%2 ){	std::cout << "|";}
		if ((int)pow(2, level) - 1 == i) {std::cout << std::endl;}
	}
	std::cout << std::endl;
}

void printTable(){
	// o, to sam napisałem XD
	int height = log2(_size) + 1;
	std::cout << "||";
	for (int i = 1; i < _size+1; i++) {
		int level = log2(i) + 1;
		int spaces = pow(2,(height - level + 1));
		if ( level > 4 ) spaces *=2;
		std::cout << " " << A[i-1]; if ( i%2 ){ std::cout << " |"; }
		if ((int)pow(2, level) - 1 == i) { std::cout << "|"; }
	}
	std::cout << std::endl;
}

};

///////////////////////////////////////////////////////////////////////////////////

int main(){

	int n=13;
	double tab1[n] = {5,1,2,3,4,0,6,2,5,3,2,8,9};
	
	MaxHeap* heap1 = new MaxHeap;

	heap1->buildHeap(tab1, n);
	heap1->printHeap();

	heap1->insert(1);
	heap1->insert(11);

	heap1->printTable();

	std::cout << "Size: " << heap1->getSize() << std::endl;
	std::cout << "Max: " << heap1->getMax() << std::endl;

	heap1->printHeap();

	heap1->erase(0);

	heap1->printHeap();

	delete heap1;

	return 0;
}