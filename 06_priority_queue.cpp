#include <iostream>
#include <random>
#include <vector>


class PriorityQueue{
// PriorityQueue bazuje na MaxHeap ponieważ A[0] zawsze daje nam element o najwyższej wartości 
private:

struct Elem{
	Elem(double _val, int _key):val(_val),key(_key){}

	double val;
	int key;
};

std::vector<Elem> S;

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
	if ( ( l <= _size-1 ) && ( S[l].key > S[largest].key ) ){ // nie >= bo nie chemy zamieniać jak było inaczej dodane do kolejki
		largest=l;
	}
	if ( ( r <= _size-1 ) && ( S[r].key > S[largest].key ) ){
		largest=r;
	}

	// jeżeli największy nie jest rodzicem, to zamieniamy go miejscami z rodzicem
	if ( largest != ind ){
		int tmp_k = S[ind].key;
		double tmp_v = S[ind].val;
		S[ind].key = S[largest].key;
		S[ind].val = S[largest].val;
		S[largest].key = tmp_k;
		S[largest].val = tmp_v;

		// badany węzeł zachowuje już własność kopca, ale 'spływająca' najmniejsza wartość
		// mogła zaburzyć własność w niższym węźle, więc ją naprawiamy
		_heapify(largest);
	}
}

public:

PriorityQueue(){ std::cout << "PriorityQueue constructed (empty)." << std::endl;}
PriorityQueue(double values[], int keys[], int n){ std::cout << "PriorityQueue constructed." << std::endl; buildHeap(values, keys ,n); }
~PriorityQueue(){ std::cout << "PriorityQueue destructed." << std::endl; }

void buildHeap(double values[], int keys[], int n){
	S.clear();

	// zapisujemy wielkość tablicy
	_size=n;

	// przepisujemy to przetrzymywanej tablicy wartości z zadanej
	for (int i=0; i<_size; i++){
		S.push_back(Elem(values[i],keys[i]));
	}
	// budujemy z niej kopiec
	for (int i=_size/2; i >= 0; i--){
		_heapify(i);
	}

	std::cout << "PriorityQueue has been builded from tables." << std::endl; 
}

void insert(double val, int key){
	S.push_back(Elem(0,0));
	_size++;
	// przechodzimy z wartością na odpowiednie miejsce
	int i = _size-1;
	while ( ( i > 0 ) && ( S[_parent(i)].key < key ) ){
		S[i].val = S[_parent(i)].val;
		S[i].key = S[_parent(i)].key;
		i = _parent(i);
	}
	S[i].val=val;
	S[i].key=key;

	std::cout << "Value " << val << " (key: " << key << ") has been added." << std::endl; 
}

int getSize(){ return _size; }

double getMax() {
	if ( _size > 0 ){
		return S[0].val; 
	}
	else std::cout << "PriorityQueue empty!" << std::endl;
	return -1;
}

double popMax() {
	// złożoność O( log(n) ) tylko przez _heapify
	double max;
	if ( _size > 0 ){
		max = S[0].val; 
		if ( _size > 1){
			S[0].key = S[_size-1].key;
			S[0].val = S[_size-1].val;
			_heapify(0);
		}
		_size--;
		S.pop_back();
		return max;
	}
	else std::cout << "PriorityQueue empty!" << std::endl;
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
		std::cout << S[i-1].val << "(" << S[i-1].key << ")";
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
		std::cout << " " << S[i-1].val << "(" << S[i-1].key << ")"; if ( i%2 ){ std::cout << " |"; }
		if ((int)pow(2, level) - 1 == i) { std::cout << "|"; }
	}
	std::cout << std::endl;
}

};

///////////////////////////////////////////////////////////////////////////////////

int main(){

	double values1[10] = {0,1,2,3,4,5,6,7,8,9};
	int keys1[10]      = {8,8,4,6,5,4,2,2,0,0};

	PriorityQueue* pqueue1 = new PriorityQueue(values1, keys1, 10);
	pqueue1->printHeap();
	
	std::cout << "Max: " << pqueue1->popMax() << std::endl;
	pqueue1->printHeap();
	
	pqueue1->insert(14,8);
	pqueue1->printHeap();

	pqueue1->insert(15,8);
	pqueue1->printHeap();

	std::cout << "Max: " << pqueue1->popMax() << std::endl;
	pqueue1->printHeap();

	std::cout << "Max: " << pqueue1->popMax() << std::endl;
	pqueue1->printHeap();

	delete pqueue1;
	

	return 0;
}