
// obracanie

// DSW

#include <iostream>
#include <memory> // std::shared_ptr
#include <cstdlib>  //required for rand(), srand()
#include <ctime>    //required for time()

class AVL{
	// Drzewo AVL jest zrównoważonym drzewem BST
	//	 dzięki złożoność podstawowych operacji utrzymuje się na lg(n) (bo taka jest wysokość)
	// WŁASNOŚĆ DRZEWA BST
	// 	Niech x będzie węzłem drzwa BST.
	// 	Jeśli y jest węzłęm znajdującym się	w lewym poddrzewie węzła x, to y.key <= x.key. 
	// 	Jeśli y jest węzłęm znajdującym się	w prawym poddrzewie węzła x, to y.key >= x.key. 

	// STRUCTS: 

	class Node{
		public:

		int key;

		int height;
		std::shared_ptr<Node> p; // wskaźnik na rodzica
		std::shared_ptr<Node> left; // wskaźnik na lewego syna
		std::shared_ptr<Node> right; // wskaźnik na prawego syna

		void print(){ std::cout << "Node(" << key << ")" << std::endl;}

		Node():key(0),height(0),p(nullptr),left(nullptr),right(nullptr){voice();}
		Node(int key):key(key),height(0),p(nullptr),left(nullptr),right(nullptr){voice();}
		Node(int key, std::shared_ptr<Node> parent):key(key),height(0),p(parent),left(nullptr),right(nullptr){voice();}
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
		
	void insertNode(std::shared_ptr<Node> z){

		// BST insertion
		std::shared_ptr<Node> y = nullptr;
		std::shared_ptr<Node> x = root;
		while (x) {
			y = x;
			if ( z->key < x->key ){
				x = x->left;
			}
			else{
				x = x->right;
			}
		}
		z->p = y;
		if ( y == nullptr ) root = z;
		else if ( z->key < y->key ) y->left = z;
		else y->right = z;

		// balancing AVL

		// https://pl.wikipedia.org/wiki/Drzewo_AVL
		// https://www.javatpoint.com/insertion-in-avl-tree
		// https://www.geeksforgeeks.org/avl-tree-set-1-insertion/

		_setHeight(z);
		
		while ( y ){
			int l = ( y->left ) ? y->left->height : 0;
			int r = ( y->right ) ? y->right->height : 0;
			int weight = r-l;
			if ( weight == -2 ){
				//std::cout << "rR" << y->key <<std::endl;
				x=y->left;
				_rotateRight(y);
				break;
			}
			else if ( weight == 2 ){
				_rotateLeft(y);
				x=y->right;
				//std::cout << "rL" << y->key <<std::endl;
				break;
			}
			y = y->p;
		}

	}

	void DSW(){
		// https://pl.wikipedia.org/wiki/Algorytm_DSW
	}

	void _setHeight(std::shared_ptr<Node> x){
		do{
			
			int l = ( x->left ) ? x->left->height : 0;
			int r = ( x->right ) ? x->right->height : 0;
			x->height = 1 + ( ( l > r ) ? l : r );

			x=x->p;
		}while (x);
	}

	void _rotateRight(std::shared_ptr<Node> q){
		// obrót w prawo wokół krawędzi (q,p) drzewa
		std::shared_ptr<Node> p = q->left;
		if ( q == nullptr || p == nullptr) return;

		q->left = p->right;
		p->right = q;
		
		p->p = q->p;
		q->p = p;
		
		if ( root == q ) root = p;
		else if ( p->p->left == q ) p->p->left = p;
		else if ( p->p->right == q ) p->p->right = p;

		_setHeight(q);
	}

	void _rotateLeft(std::shared_ptr<Node> q){
		// obrót w lewo wokół krawędzi (q,p) drzewa
		std::shared_ptr<Node> p = q->right;
		if ( q == nullptr || p == nullptr ) return;

		q->right = p->left;
		p->left = q;
		
		p->p = q->p;
		q->p = p;
		
		if ( root == q ) root = p;
		else if ( p->p->left == q ) p->p->left = p;
		else if ( p->p->right == q ) p->p->right = p;

		_setHeight(q);
	}

public:
	AVL():root(nullptr){}
	~AVL(){_release(root);} // Złożoność przejścia całego drzewa: O(n)

	void insertNode(int key){
		// złożoność wstawiania: O(h) : h - wysokość drzewa (oczekiwana wartość h dla losowo skonstruowanego drzewa to O( lg(n) )
		std::shared_ptr<Node> z = std::make_shared<Node>(key); // zamiast new
		insertNode(z);
	}

	void print(const std::string& prefix, std::shared_ptr<Node> node, bool isLeft)
	{
		if( node != nullptr )
		{
			std::cout << prefix;

			if ( node == root) std::cout << "─R─";
			else std::cout << (isLeft ? "├l─" : "└p─" );

			// print the value of the node
			std::cout << node->key << "(" << node->height << ")" << std::endl;

			// enter the next tree level - left and right branch
			print( prefix + (isLeft ? "│   " : "    "), node->left, true);
			print( prefix + (isLeft ? "│   " : "    "), node->right, false);
		}
	}
	void print(){ print("", root, false); }

	void createSample(){
    	srand(time(0)); 
		for (int i=0;i<31;i++){
			insertNode( (rand () % 50) + 0 );
			print();
		}
	}

	void rR(){
		_rotateRight(root);
	}
	void rL(){
		_rotateLeft(root);
	}
};


int main(void){
	AVL tree;
	tree.createSample();
	tree.print();





	std::cout << "========================" << std::endl;
	return 0;
}