#include <iostream>
#include <vector>

#define MAX_STACK_SIZE 10

class Stack{
	int stack[MAX_STACK_SIZE];
	std::size_t top = 0; // indeks następnego wolnego miejsca
	
public:
	bool empty(){
		if ( top == 0 ) return true;
		else return false;
	}

	bool full(){
		if ( top == MAX_STACK_SIZE ) return true;
		else return false;
	}

	bool push(int val){
		if ( !full() ){ // jest wolne miejsce na stosie
			stack[top] = val;
			top++;
			return 1; // dodano pomyślnie
		}
		else{ // stos przepełniony
			std::cout << "Error: Stack full!" << std::endl;
			return 0; // wartość nie została dodana
		}
	}

	int pop(){
		if ( !empty() ){
			top--;
			return stack[top];
		}
		else{
			std::cout << "Error: Stack empty!" << std::endl;
			return 0;
		}
	}

	void print(){
		std::cout << "Stack: ";
		for (size_t i=0;i<top;i++){
			std::cout << stack[i] << " ";
		}
		std::cout << std::endl;
	}

};


int main(void){
	Stack stack1;

	std::cout << stack1.pop() << std::endl;
	stack1.print();

	for (size_t i=0;i<9;i++){
		stack1.push(i);
	}
	stack1.print();
	stack1.push(9);
	stack1.print();
	stack1.push(10);

	std::cout << stack1.pop() << std::endl;
	stack1.print();




	return 0;
}