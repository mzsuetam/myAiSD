#include <iostream>
#include <memory> // std::shared_ptr

class BST{
	// WŁASNOŚĆ DRZEWA BST
	// 	Niech x będzie węzłem drzwa BST.
	// 	Jeśli y jest węzłęm znajdującym się	w lewym poddrzewie węzła x, to y.key <= x.key. 
	// 	Jeśli y jest węzłęm znajdującym się	w prawym poddrzewie węzła x, to y.key >= x.key. 

	// STRUCTS: 

	class Node{
		public:// temp. here
		int key;

		std::shared_ptr<Node> p; // wskaźnik na rodzica
		std::shared_ptr<Node>  left; // wskaźnik na lewego syna
		std::shared_ptr<Node>  right; // wskaźnik na prawego syna

		// public:

		int getKey(){ return key;}
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

	void inorderTreeWalk(std::shared_ptr<Node> x){
		if (x){ //!= nullptr
			inorderTreeWalk(x->left);
			std::cout << x->key << " ";
			inorderTreeWalk(x->right);
		}
	}

	std::shared_ptr<Node> treeSearch(std::shared_ptr<Node> x, int key){
		if ( ( x==nullptr ) || ( x->key == key ) ){
			return x;
		}
		if ( x->key > key) return treeSearch(x->left, key);
		else return treeSearch(x->right,key);
	}

	std::shared_ptr<Node> max(std::shared_ptr<Node> x){
		while ( x->right ){
			x = x->right;
		}
		return x;
	}	

	std::shared_ptr<Node> min(std::shared_ptr<Node> x){
		while ( x->left ){
			x = x->left;
		}
		return x;
	}	
	

public:
	BST():root(nullptr){}
	~BST(){_release(root);} // Złożoność przejścia całego drzewa: O(n)

	void inorderTreeWalk(){
		// Złożoność przejścia całego drzewa: O(n)
		inorderTreeWalk(root);
		std::cout << std::endl;
	}

	std::shared_ptr<Node> treeSearch(int key){
		// złożoność wyszykiwania: O(h) : h - wysokość drzewa
		return treeSearch(root,key);
	}

	std::shared_ptr<Node> iterativeTreeSearch(int key){
		// złożoność wyszykiwania: O(h) : h - wysokość drzewa
		std::shared_ptr<Node> x = root;
		while ( ( x ) || ( x->key != key ) ){
			if ( x->key > key) x = x->left;
			else x = x->right;
		}
		return x;
	}

	std::shared_ptr<Node> min(){
		// złożoność wyszykiwania: O(h) : h - wysokość drzewa
		return min(root);
	}	

	std::shared_ptr<Node> max(){
		// złożoność wyszykiwania: O(h) : h - wysokość drzewa
		return max(root);
	}	

	std::shared_ptr<Node> treeSuccessor(std::shared_ptr<Node> x){
		// złożoność wyszykiwania: O(h) : h - wysokość drzewa
		if ( x->right )	{ return min(x->right);}
		std::shared_ptr<Node> y = x->p;
		while ( ( y ) && ( x == y->right ) ){
			x = y;
			y = y->p;
		}
		return y;
	}

	std::shared_ptr<Node> treePredecessor(std::shared_ptr<Node> x){
		// złożoność wyszykiwania: O(h) : h - wysokość drzewa
		if ( x->left )	{ return max(x->left);}
		std::shared_ptr<Node> y = x->p;
		while ( ( y ) && ( x == y->left ) ){
			x = y;
			y = y->p;
		}
		return y;
	}






	void fake_create(){
		std::shared_ptr<Node> a = std::make_shared<Node>(6); // zamiast new
		root = a;
		std::shared_ptr<Node> b = std::make_shared<Node>(3,root);
		root->left = b;
		std::shared_ptr<Node> c = std::make_shared<Node>(7,root);
		root->right = c;
		std::shared_ptr<Node> b1 = std::make_shared<Node>(2,b);
		std::shared_ptr<Node> b2 = std::make_shared<Node>(5,b);
		b->left = b1;
		b->right = b2;
		std::shared_ptr<Node> c1 = std::make_shared<Node>(8,c);
		c->right = c1;
	}
};


int main(void){
	BST tree;
	tree.fake_create();

	tree.inorderTreeWalk();

	std::cout << tree.treeSearch(4) << std::endl;

	std::cout << "min key: " << tree.min()->getKey() << " in: " << tree.min() << std::endl;
	std::cout << "max key: " << tree.max()->getKey() << " in: " << tree.max() << std::endl;
	std::cout << std::endl;
	std::cout << "searched(3) key: " << tree.treeSearch(3)->getKey() << " in: " << tree.treeSearch(3) << std::endl;
	std::cout << "searched(2) key: " << tree.treeSearch(2)->getKey() << " in: " << tree.treeSearch(2) << std::endl;
	std::cout << std::endl;
	std::cout << "successor of 3 key: " << tree.treeSuccessor(tree.treeSearch(3))->getKey() << " in: " << tree.treeSuccessor(tree.treeSearch(3)) << std::endl;
	std::cout << "successor of 5 key: " << tree.treeSuccessor(tree.treeSearch(5))->getKey() << " in: " << tree.treeSuccessor(tree.treeSearch(5)) << std::endl;
	std::cout << "successor of 2 key: " << tree.treeSuccessor(tree.treeSearch(2))->getKey() << " in: " << tree.treeSuccessor(tree.treeSearch(2)) << std::endl;
	std::cout << std::endl;
	std::cout << "predecessor of 7 key: " << tree.treePredecessor(tree.treeSearch(7))->getKey() << " in: " << tree.treePredecessor(tree.treeSearch(7)) << std::endl;
	std::cout << "predecessor of 5 key: " << tree.treePredecessor(tree.treeSearch(5))->getKey() << " in: " << tree.treePredecessor(tree.treeSearch(5)) << std::endl;
	std::cout << "predecessor of 2 key: - in: " << tree.treePredecessor(tree.treeSearch(2)) << std::endl;





	std::cout << "========================" << std::endl;
	return 0;
}