#ifndef TIMER_H
#define TIMER_H

#include <iostream>

// CLASS TIMER
// METHODS:
//	START() - start (and reset) timer
//	STOP() - stops timer
//	PRINT() - prints clocked time (in [ms], [s] and [min]) 
 
class Timer{
	clock_t s,e;
	double duration;
	int running;
public:
	Timer(){running=0;}
	void start(){
		if(!running){
			s=clock();running=1;
	}}
	void stop(){
		if (running){
			e=clock();running=0;
	}}
	void print(){
		if (!running){
			duration=(e-s)/static_cast<double>(CLOCKS_PER_SEC);
			std::cout << "[Timer] time: " << " " << duration*1000 << " [ms] == " << duration << " [s] == " << duration/60 << " [min]" << std::endl;
		}
		else std::cout << "[Timer] timer running!" << std::endl;
	}
};

#endif