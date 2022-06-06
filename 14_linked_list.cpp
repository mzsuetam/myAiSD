#include <iostream>
#include <vector>

class LinkedList{
	// z dowiązaniami, które pozwalają nie martwić się o warunki brzegowe
	struct Node
	{
		Node(int val, Node* p, Node*n):val(val),p(p),n(n){}
		int val;
		Node* p; // previous
		Node* n; // next
	};

	Node* warder;
	
public:

	LinkedList(){_init();}
	~LinkedList(){
		Node* ptr = warder->n;
		while ( ptr != warder ) {
			Node* next = ptr->n;
			delete ptr;
			ptr = next;
		}
		delete warder;
	}

	void _init(){
		Node* wrd = new Node(420,nullptr,nullptr);
		wrd->n = wrd;
		wrd->p = wrd;
		warder = wrd;
	}

	void push_back(int val){
		Node* new_node = new Node(val,warder->p,warder);
		warder->p->n = new_node;
		warder->p = new_node;
	}

	int pop(size_t ind){
		if ( warder->n != warder ){
			Node* ptr = warder->n;
			for (size_t i=0; i<ind;i++){
				if ( ptr->n == warder ){
					std::cout << "Error: No such index (" << ind << ")!" << std::endl;
					return 0;
				}
				ptr = ptr->n;
			}
			int tmp = ptr->val;
			ptr->p->n = ptr->n;
			ptr->n->p = ptr->p; 
			delete ptr;
			return tmp;
		}
		else{
			std::cout << "Error: LinkedList empty!" << std::endl;
			return 0;
		}	
	}

	Node* search(int key){
		Node* ptr = warder->n;
		while ( ptr != warder ) {
			if ( ptr->val == key ){
				return ptr;
			}
			ptr = ptr->n;
		}
		// if not found:
		std::cout << "Error: no such key!" << std::endl;
		return nullptr;
	}

	void print(){
		std::cout << "LinkedList: ";
		Node* ptr = warder->n;
		while ( ptr != warder ) {
			std::cout << ptr->val << " ";
			ptr = ptr->n;
		}
		std::cout << std::endl;
	}

};


int main(void){
	LinkedList queue1;

	std::cout << queue1.pop(3) << std::endl;
	queue1.print();

	for (size_t i=0;i<9;i++){
		queue1.push_back(i);
	}
	queue1.print();
	queue1.push_back(9);
	queue1.print();
	queue1.push_back(10);

	std::cout << queue1.pop(5) << std::endl;
	queue1.print();
	std::cout << queue1.pop(0) << std::endl;
	queue1.print();
	std::cout << queue1.pop(15) << std::endl;
	queue1.print();
	std::cout << queue1.pop(9) << std::endl;
	queue1.print();
	std::cout << queue1.pop(8) << std::endl;
	queue1.print();

	std::cout << queue1.search(2) << std::endl;



	return 0;
}