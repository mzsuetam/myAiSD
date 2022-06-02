
// obracanie

// DSW

#include <iostream>
#include <memory> // std::shared_ptr
#include <cstdlib>  //required for rand(), srand()
#include <ctime>    //required for time()

class AVL{
	// Drzewo AVL jest zrównoważonym drzewem BST bez duplikatów kluczy (które mogą być implementowane przez dodatkowe pole ilość w Node)
	//	 dzięki złożoność podstawowych operacji utrzymuje się na lg(n) (bo taka jest wysokość)

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
		~Node(){/*std::cout << "Node(" << key << ") dead" << std::endl;*/}

		void voice(){ /*std::cout << "Node(" << key << ") born" << std::endl;*/ }
	};
	// DATA TYPES:
public:
	int good =0;
	int dpl=0;
	int N=100;
private:
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

	std::shared_ptr<Node> search(std::shared_ptr<Node> x, int key){
		if ( ( x==nullptr ) || ( x->key == key ) ){
			return x;
		}
		if ( x->key > key) return search(x->left, key);
		else return search(x->right,key);
	}
		
	void insertNode(std::shared_ptr<Node> z){

		if ( search(root, z->key) ){
			dpl++;
			return;
		}

		// BST insertion
		std::shared_ptr<Node> y = nullptr;
		std::shared_ptr<Node> x = root;
		while (x) {
			y = x;
			if ( z->key < x->key ){
				x = x->left;
			}
			else if (z->key > x->key){
				x = x->right;
			}
		}
		z->p = y;
		if ( y == nullptr ) root = z;
		else if ( z->key < y->key ) y->left = z;
		else y->right = z;

		// balancing AVL

		_setHeight(z);
		
		// balancing AVL: searching critical node
		int balance = 0;
		std::shared_ptr<Node> c = z;
		while ( c ){
			int l = ( c->left ) ? (c->left->height) : -1;
			int r = ( c->right ) ? (c->right->height) : -1;
			balance = l-r;

			if ( balance < -1 || balance > 1 ) break;			

			c = c->p;
		}

		if ( c ) {
			if ( balance > 1 && c->left && z->key < c->left->key ){
				// LL Rotation - The new node is inserted to the left sub-tree
				//	of left sub-tree of critical node.
				//std::cout << "LL" << std::endl;
				_rotateRight(c);
			}
			else if ( balance < -1 && c->right && z->key > c->right->key ){
				// RR Rotation - The new node is inserted to the right sub-tree
				//	of the right sub-tree of the critical node.
				//std::cout << "RR" << std::endl;
				_rotateLeft(c);
			}
			else if ( balance > 1 && c->left && z->key > c->left->key ){
				// LR Rotation - The new node is inserted to the right sub-tree
				//	of the left sub-tree of the critical node.
				//std::cout << "LR" << std::endl;
				_rotateLeft(c->left); // wyrzucamy wagę ze środka na lewo
				_rotateRight(c);
			}
			else if ( balance < -1 && c->right && z->key < c->right->key ){
				// RL Rotation - The new node is inserted to the left sub-tree
				//	of the right sub-tree of the critical node.
				//std::cout << "RL" << std::endl;
				_rotateRight(c->right); // wyrzucamy wagę ze środka na prawo
				_rotateLeft(c);
			}
			// do else nigdy nie dochodzi
		}
	}

	void DSW(){
		// https://pl.wikipedia.org/wiki/Algorytm_DSW
	}

	void _setHeight(std::shared_ptr<Node> x){
		do{
			int l = ( x->left ) ? x->left->height : -1;
			int r = ( x->right ) ? x->right->height : -1;
			x->height = 1 + ( ( l > r ) ? l : r );

			x=x->p;
		}while (x);
	}

	void _rotateRight(std::shared_ptr<Node> q){
		// obrót w prawo wokół krawędzi (q,p) drzewa
		std::shared_ptr<Node> p = q->left;
		if ( q == nullptr || p == nullptr){
			return;
		}

		// 6 zmian - warto rozpisać na kartce obrót dla 1,2,3,4,5 i zawuażyć,
		//	co się zmieniana na których krawędziach 
		q->left = p->right;
		if ( p->right ) p->right->p = q;
		p->right = q;
		if ( root == q ) root = p;
		else if ( q->p->left == q ) q->p->left = p;
		else if ( q->p->right == q ) q->p->right = p;
		p->p = q->p;
		q->p = p;

		_setHeight(q);

	}

	void _rotateLeft(std::shared_ptr<Node> q){
		// obrót w lewo wokół krawędzi (q,p) drzewa
		std::shared_ptr<Node> p = q->right;
		if ( q == nullptr || p == nullptr ){
			return;
		}

		// 6 zmian - warto rozpisać na kartce obrót dla 1,2,3,4,5 i zawuażyć,
		//	co się zmieniana na których krawędziach 
		q->right = p->left;
		if ( p->left ) p->left->p = q;
		p->left = q;
		if ( root == q ) root = p;
		else if ( q->p->left == q ) q->p->left = p;
		else if ( q->p->right == q ) q->p->right = p;
		p->p = q->p;
		q->p = p;
		
		_setHeight(q);
	}

public:
	AVL():root(nullptr){}
	~AVL(){_release(root);} // Złożoność przejścia całego drzewa: O(n)

	void insertNode(int key){
		std::shared_ptr<Node> z = std::make_shared<Node>(key); // zamiast new
		insertNode(z);
	}

	void print(const std::string& prefix, std::shared_ptr<Node> node, bool isLeft)
	{
		if( node != nullptr )
		{
			std::cout << prefix;

			if ( node == root) std::cout << "─R─";
			else std::cout << (isLeft ? "├l─" : "└r─" );


			int l = ( node->left ) ? (node->left->height) : -1;
			int r = ( node->right ) ? (node->right->height) : -1;
			int balance = l-r;

			// tylko dla sprawdzenia:
			if ( balance < -1 || balance > 1  ) std::cout << "UWAGA! GAŁĄŹ NIEZRÓWNOWAŻONA!";

			// print the value of the node
			std::cout << node->key << std::endl;
			//std::cout << node->key << "(" << node->height << ";" << balance << ";" << ( (node->p) ? node->p->key : -1 ) << ")" << std::endl;
			good++;
			// enter the next tree level - left and right branch
			print( prefix + (isLeft ? "│   " : "    "), node->left, true);
			print( prefix + (isLeft ? "│   " : "    "), node->right, false);
		}
	}
	void print(){ print("", root, false); }

	void createSample(){
    	srand(time(0)); 
		for (int i=0;i<N;i++){
			insertNode( (rand () % (5*N)) + 0 );
		}
	}
};


int main(void){
	AVL tree;
	tree.createSample();
	tree.print();

	std::cout << tree.good << "/" << tree.N << "(" << tree.dpl << ")" << std::endl;

	std::cout << "========================" << std::endl;
	return 0;
}