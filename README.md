# myAiSD

My implementations of some basic algorithrms and data structures.
Based on Cormen's "Introduction to algorithms".

### Content:

##### Sorting:
- Comparison sorts:
	- insertionSort, [01], Cor. 1.2
	- mergeSort (recursive), [02], Cor 1.3
	- mergeSort (iterative), [03]
	- heapSort, [05], Cor 7.4
	- quickSort, [07], Cor 8
	- quickSort (randomized), [08], Cor 8
- Non-comparison sorts:
	- countingSort [09], Cor 9.2
	- radixSort (on countingSort) [10], Cor 9.3
	- bucketSort (on std::sort) [11] Cor 9.4

##### Data Structures:
- maxHeap, [04], Cor 7.1-3
- priorityQueue, [06], Cor 7.5
- stack [12], Cor 11.1

##### Folder lib:
- timer.h - klasa minutnika do mierzenia czasu działania algorytmów
- tables.h, tables.cpp - funkcje pomocnicze do pracy z tablicami
	- insertRandom - wypełnianie tablicy losowymi wartościami
	- printTable - wyświetlanie zawartości tablicy
	- checkTable - sprawdzanie posortowania tablicy