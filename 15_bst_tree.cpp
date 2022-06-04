#include <iostream>
#include <memory> // std::shared_ptr

class BST{
	// WŁASNOŚĆ DRZEWA BST
	// 	Niech x będzie węzłem drzwa BST.
	// 	Jeśli y jest węzłęm znajdującym się	w lewym poddrzewie węzła x, to y.key <= x.key. 
	// 	Jeśli y jest węzłęm znajdującym się	w prawym poddrzewie węzła x, to y.key >= x.key. 

	// STRUCTS: 

	class Node{
		public:

		int key;

		std::shared_ptr<Node> p; // wskaźnik na rodzica
		std::shared_ptr<Node> left; // wskaźnik na lewego syna
		std::shared_ptr<Node> right; // wskaźnik na prawego syna

		void print(){ std::cout << "Node(" << key << ")" << std::endl;}

		Node():key(0),p(nullptr),left(nullptr),right(nullptr){voice();}
		Node(int key):key(key),p(nullptr),left(nullptr),right(nullptr){voice();}
		Node(int key, std::shared_ptr<Node> parent):key(key),p(parent),left(nullptr),right(nullptr){voice();}
		~Node(){std::cout << "Node(" << key << ") dead" << std::endl;}

		void voice(){ std::cout << "Node(" << key << ") born" << std::endl; }
	};

	// DATA TYPES:

	std::shared_ptr<Node>  root;

	// METHODS:

	void _release(std::shared_ptr<Node> x){
		if (x){
			_release(x->left);
			x->left = nullptr;
			_release(x->right);
			x->right = nullptr;
		}
	}

	void inorderWalk(std::shared_ptr<Node> x){
		if (x){ //!= nullptr
			inorderWalk(x->left);
			std::cout << x->key << " ";
			inorderWalk(x->right);
		}
	}

	std::shared_ptr<Node> search(std::shared_ptr<Node> x, int key){
		if ( ( x==nullptr ) || ( x->key == key ) ){
			return x;
		}
		if ( x->key > key) return search(x->left, key);
		else return search(x->right,key);
	}

	std::shared_ptr<Node> getMax(std::shared_ptr<Node> x){
		while ( x->right ){
			x = x->right;
		}
		return x;
	}	

	std::shared_ptr<Node> getMin(std::shared_ptr<Node> x){
		while ( x->left ){
			x = x->left;
		}
		return x;
	}	
	
	void insertNode(std::shared_ptr<Node> z){
		std::shared_ptr<Node> y = nullptr;
		std::shared_ptr<Node> x = root;
		while (x) {
			y = x;
			if ( z->key < x->key ) x = x->left;
			else x = x->right;
		}
		z->p = y;

		if ( y == nullptr ) root = z;
		else if ( z->key < y->key ) y->left = z;
		else y->right = z;
	}

public:
	BST():root(nullptr){}
	~BST(){_release(root);} // Złożoność przejścia całego drzewa: O(n)

	void inorderWalk(){
		// Złożoność przejścia całego drzewa: O(n)
		inorderWalk(root);
		std::cout << std::endl;
	}

	std::shared_ptr<Node> search(int key){
		// złożoność wyszykiwania: O(h) : h - wysokość drzewa (oczekiwana wartość h dla losowo skonstruowanego drzewa to O( lg(n) )
		return search(root,key);
	}

	std::shared_ptr<Node> iterativeSearch(int key){
		// złożoność wyszykiwania: O(h) : h - wysokość drzewa (oczekiwana wartość h dla losowo skonstruowanego drzewa to O( lg(n) )
		std::shared_ptr<Node> x = root;
		while ( ( x ) || ( x->key != key ) ){
			if ( x->key > key) x = x->left;
			else x = x->right;
		}
		return x;
	}

	std::shared_ptr<Node> getMin(){
		// złożoność podania min elementu: O(h) : h - wysokość drzewa (oczekiwana wartość h dla losowo skonstruowanego drzewa to O( lg(n) )
		return getMin(root);
	}	

	std::shared_ptr<Node> getMax(){
		// złożoność podania max elementu: O(h) : h - wysokość drzewa (oczekiwana wartość h dla losowo skonstruowanego drzewa to O( lg(n) )
		return getMax(root);
	}	

	std::shared_ptr<Node> getSuccessor(std::shared_ptr<Node> x){
		// złożoność podania następnika: O(h) : h - wysokość drzewa (oczekiwana wartość h dla losowo skonstruowanego drzewa to O( lg(n) )
		if ( x->right )	{ return getMin(x->right);}
		std::shared_ptr<Node> y = x->p;
		while ( ( y ) && ( x == y->right ) ){
			x = y;
			y = y->p;
		}
		return y;
	}

	std::shared_ptr<Node> getPredecessor(std::shared_ptr<Node> x){
		// złożoność podania poprzednika: O(h) : h - wysokość drzewa (oczekiwana wartość h dla losowo skonstruowanego drzewa to O( lg(n) )
		if ( x->left )	{ return getMax(x->left);}
		std::shared_ptr<Node> y = x->p;
		while ( ( y ) && ( x == y->left ) ){
			x = y;
			y = y->p;
		}
		return y;
	}

	void insertNode(int key){
		// złożoność wstawiania: O(h) : h - wysokość drzewa (oczekiwana wartość h dla losowo skonstruowanego drzewa to O( lg(n) )
		if ( search(root, key) ){
			return;
		}
		std::shared_ptr<Node> z = std::make_shared<Node>(key); // zamiast new
		insertNode(z);
	}

	void deleteNode(std::shared_ptr<Node> z){
		// złożoność usuwania: O(h) : h - wysokość drzewa (oczekiwana wartość h dla losowo skonstruowanego drzewa to O( lg(n) )

		// Ogólnie są 3 przypadki do usuwania Node z:
		//  - z nie ma synów > w ojcu z zastępujemy wskaźnik na z na nullptr
		//  - z ma jednego syna > w ojcu z zastępujemy wskaźnik na z na syna z
		//  	i w synu wskaźnik ojca na wskaźnik na ojca z
		//  - z ma 2 synów > wycinamy pierwszy następnik z, który nie ma lewego syna i nadpisujemy z jego danymi
		// Poniższy algorytm realizuje powyższe przypadki nieco inaczej:

		std::shared_ptr<Node> x = nullptr;
		std::shared_ptr<Node> y = nullptr;

		if ( ( z->left == nullptr ) || (z->right == nullptr ) )
			y = z;
		else y = getSuccessor(z);
		
		if ( y->left ) x = y->left;
		else x = y->right;
		
		if ( x ) x->p = y->p;
		
		if ( y->p == nullptr ) root = x;
		else if ( y == y->p->left ) y->p->left = x;
		else y->p->right = x;

		if ( y!=z ) z->key = y->key;
	}

	void print(const std::string& prefix, std::shared_ptr<Node> node, bool isLeft)
	{
		if( node != nullptr )
		{
			std::cout << prefix;

			if ( node == root) std::cout << "─R─";
			else std::cout << (isLeft ? "├l─" : "└p─" );

			// print the value of the node
			std::cout << node->key << std::endl;

			// enter the next tree level - left and right branch
			print( prefix + (isLeft ? "│   " : "    "), node->left, true);
			print( prefix + (isLeft ? "│   " : "    "), node->right, false);
		}
	}
	void print(){ print("", root, false); }

	void createSample(){
		insertNode(6);
		insertNode(3);
		insertNode(7);
		insertNode(2);
		insertNode(5);
		insertNode(8);
	}
};


int main(void){
	BST tree;
	tree.createSample();

	tree.inorderWalk();
	tree.print();

	std::cout << tree.search(4) << std::endl;

	std::cout << "getMin key: " << tree.getMin()->key << " in: " << tree.getMin() << std::endl;
	std::cout << "getMax key: " << tree.getMax()->key << " in: " << tree.getMax() << std::endl;
	std::cout << std::endl;
	std::cout << "searched(3) key: " << tree.search(3)->key << " in: " << tree.search(3) << std::endl;
	std::cout << "searched(2) key: " << tree.search(2)->key << " in: " << tree.search(2) << std::endl;
	std::cout << std::endl;
	std::cout << "successor of 3 key: " << tree.getSuccessor(tree.search(3))->key << " in: " << tree.getSuccessor(tree.search(3)) << std::endl;
	std::cout << "successor of 5 key: " << tree.getSuccessor(tree.search(5))->key << " in: " << tree.getSuccessor(tree.search(5)) << std::endl;
	std::cout << "successor of 2 key: " << tree.getSuccessor(tree.search(2))->key << " in: " << tree.getSuccessor(tree.search(2)) << std::endl;
	std::cout << std::endl;
	std::cout << "predecessor of 7 key: " << tree.getPredecessor(tree.search(7))->key << " in: " << tree.getPredecessor(tree.search(7)) << std::endl;
	std::cout << "predecessor of 5 key: " << tree.getPredecessor(tree.search(5))->key << " in: " << tree.getPredecessor(tree.search(5)) << std::endl;
	std::cout << "predecessor of 2 key: - in: " << tree.getPredecessor(tree.search(2)) << std::endl;

	tree.insertNode(4);
	tree.print();
	tree.insertNode(1);
	tree.print();
	tree.insertNode(9);
	tree.print();
	tree.insertNode(13);
	tree.print();

	tree.deleteNode(tree.search(1));
	tree.print();
	tree.deleteNode(tree.search(6));
	tree.print();
	tree.deleteNode(tree.search(4));
	tree.print();


	std::cout << "========================" << std::endl;
	return 0;
}