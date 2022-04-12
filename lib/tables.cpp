#include <iostream>
#include <stdlib.h>     
#include <time.h> 

#include "tables.h"

void insertRandom(double table[], int n, int range){
	srand(time(0));

	for (int i=0; i<n; i++){
		table[i]=static_cast<double>(rand()%(range*10))/10-range/2;
	}
}

void printTable(double table[], int n, bool print){
	if (print){
		std::cout << "Printing table..." << std::endl;
		for (int i=0; i<n-1; i++){
			std::cout << table[i] << ", ";
		}
		std::cout << table[n-1] << std::endl;
		std::cout << "--" << std::endl;
	}
}

void checkTable(double table[], int n){
	for (int i=1; i<n; i++){
		if ( table[i-1] > table[i] ){
			std::cout << "[checkTable] BŁĄD! Tablica nieposortowana!" << std::endl;
			return;
		}
	}
	std::cout << "[checkTable] Tablica posorotwana poprawnie." << std::endl;
}