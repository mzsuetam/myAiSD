#include <iostream>
#include <vector>

#define MAX_QUEUE_SIZE 10

class Queue{
	int queue[MAX_QUEUE_SIZE];
	std::size_t head = 0;
	std::size_t tail = 0;
	std::size_t len = 0;


	std::size_t increase(std::size_t ptr){
		if ( ptr == MAX_QUEUE_SIZE-1 ) return 0;
		return ++ptr;
	}
	std::size_t decrease(std::size_t ptr){
		if ( ptr == 0 ) return MAX_QUEUE_SIZE-1;
		return --ptr;
	}

	
public:

	bool push(int val){
		if ( len < MAX_QUEUE_SIZE ){
			queue[tail] = val;
			tail = increase(tail);
			len++;
			return 1;
		}
		else{
			std::cout << "Error: Queue full!" << std::endl;
			return 0;
		}
	}

	int pop(){
		if ( len > 0 ){
			std::size_t tmp = head;
			head = increase(head);
			len--;
			return queue[tmp];
		}
		else{
			std::cout << "Error: Queue empty!" << std::endl;
			return 0;
		}
	}

	void print(){
		std::cout << "Queue: ";
		std::size_t ptr = head;
		std::size_t l = len;
		while ( l > 0 ) {
			std::cout << queue[ptr] << " ";
			ptr = increase(ptr);
			l--;
		}
		std::cout << std::endl;
	}

};


int main(void){
	Queue queue1;

	std::cout << queue1.pop() << std::endl;
	queue1.print();

	for (size_t i=0;i<9;i++){
		queue1.push(i);
	}
	queue1.print();
	queue1.push(9);
	queue1.print();
	queue1.push(10);

	std::cout << queue1.pop() << std::endl;
	std::cout << queue1.pop() << std::endl;
	std::cout << queue1.pop() << std::endl;
	std::cout << queue1.pop() << std::endl;
	queue1.print();




	return 0;
}