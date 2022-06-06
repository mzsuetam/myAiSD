## Data structures methods complexities

### Table of Contents
1. [Stack](#stack)
1. [Queue](#queue)
1. [Linked list](#linked-list)
1. [Heap](#heap)
1. [Priority queue](#priority-queue)
1. [BST](#bst)
1. [AVL](#avl)
1. [Graphs](#graphs)

### Complexities:

#### Stack
| Method					| Cmpx.			|
|:--------------------------|:--------------|
| pop						| O( 1 )		|
| push						| O( 1 )		|
| full						| O( 1 )		|
| empty						| O( 1 )		|

#### Queue
| Method					| Cmpx.			|
|:--------------------------|:--------------|
| pop						| O( 1 )		|
| push						| O( 1 )		|
| full						| O( 1 )		|
| empty						| O( 1 )		|

#### Linked List 
| Method					| Cmpx.			|
|:--------------------------|:--------------|
| push_back					| O( 1 )		|
| pop_fornt					| O( 1 )		|
| erase, search				| O( n )		|

#### Heap
| Method					| Cmpx.			|
|:--------------------------|:--------------|
| heapify					| O( log(n) )	|
| build_heap				| O( n )		|
| insert, erase				| O( log(n) )	|
| left, right, parent		| O( 1 )		|

#### Priority queue
| Method					| Cmpx.			|
|:--------------------------|:--------------|
| pop ( Heap max + erase )	| O( log(n) )	|
| push( Heap insert )		| O( log(n) )	|
| full						| O( 1 )		|
| empty						| O( 1 )		|

#### BST
| Method					| Cmpx.			|
|:--------------------------|:--------------|
| walk						| O( n )		|
| insert, erase				| O( n ) *		|
| successor, predecessor 	| O( n ) *		|
| search, getMax, getMin 	| O( n ) *		|
* average is O( h ) : h - wyskokość drzewa

#### AVL
| Method					| Cmpx.			|
|:--------------------------|:--------------|
| walk						| O( log(n) )	|
| insert, erase				| O( log(n) )	|
| successor, predecessor 	| O( log(n) )	|
| search, getMax, getMin 	| O( log(n) )	|
| DSW 						| O( n )		|
| rotateRight, rotateLeft	| O( 1 )		|

#### Graphs
Adjacency List
| Method					|Cmpx. Adjacency List| Cmpx. Adjacency Matrix|
|:--------------------------|:------------------|:------------------|
| DFS, BFS					| O( V+E )			| O( V^2 )			|
| topologicalSort			| O( V+E )			| O( V^2 )			|
| Prim algorithm			| O( (V+E)\*log(E) )| O( (V^2)\*log(E) )|
| Bellman-Ford algorithm	| V*E				| V^3				|
| Dijkstra algorithm		| O( (V+E)\*log(V) )| O( (V^2)\*log(V) )|
| Floyd-Warschal			| O( V^3 )			| O( V^3 )			|
| Ford-Fulkerson			| O( f_max*(V+E) )	| O( w_max*V^2 )	|
where f_max - max weight/flow

















