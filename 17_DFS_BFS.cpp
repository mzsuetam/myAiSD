#include <iostream>
#include <vector>
#include <queue>
#include <list>

class GraphMatrixBased{

	struct Edge
	{
		int from, to;
		bool exist = false;
		int weight = 1;

		bool operator<(const Edge& other)const{
			return weight < other.weight;
		}

	};

	

	std::vector< std::vector<Edge> > matrix;

public:
	enum graph_type{ GRAPH, DIGRAPH };

	void makeTemplate(){
		// initing matrix
		matrix.resize(8);
		for (size_t i=0; i<matrix.size(); i++ ){
			matrix[i].resize(8);
			for (size_t j=0; j<matrix.size(); j++ ){
				matrix[i][j].from = i;
				matrix[i][j].to = j;
			}
		}
		matrix[0][1].exist = true;
		matrix[1][2].exist = true;
		matrix[2][4].exist = true;
		matrix[3][0].exist = true;
		matrix[3][1].exist = true;
		matrix[3][4].exist = true;
		matrix[3][7].exist = true;
		matrix[4][3].exist = true;
		matrix[4][5].exist = true;
		matrix[5][6].exist = true;
		matrix[6][4].exist = true;
		matrix[7][4].exist = true;
	}

	void makeTemplateWithoutCycles(){
		// initing matrix
		matrix.resize(10);
		for (size_t i=0; i<matrix.size(); i++ ){
			matrix[i].resize(10);
			for (size_t j=0; j<matrix.size(); j++ ){
				matrix[i][j].from = i;
				matrix[i][j].to = j;
			}
		}
		matrix[0][1].exist = true;
		matrix[0][2].exist = true;
		matrix[1][2].exist = true;
		matrix[1][3].exist = true;
		matrix[1][4].exist = true;
		matrix[2][4].exist = true;
		matrix[3][7].exist = true;
		matrix[5][8].exist = true;
		matrix[6][9].exist = true;
		matrix[7][8].exist = true;
		matrix[7][9].exist = true;
	}

	void makeNotDirected(){
		for (size_t i=0; i<matrix.size(); i++){
			for (size_t j=0; j<matrix.size(); j++){
				if ( matrix[i][j].exist ){
					matrix[j][i].exist = true;
					matrix[j][i].weight =  matrix[i][j].weight; 
				}
			}
		}
	}

	void print(graph_type type){
		// http://graphviz.org/doc/info/command.html
		// program.out | dot -Tsvg > output.svg

		if ( type==GRAPH )
			std::cout << "graph {";
		else // if (type==DIGRAPH)
			std::cout << "digraph {";
		for ( size_t i=0; i<matrix.size(); i++){
			std::cout << i << std::endl;
			for ( size_t j=0; j<matrix[i].size(); j++){
				if ( matrix[i][j].exist && ( type==DIGRAPH || i<j )){
					std::cout << i;
					if ( type==GRAPH )
						std::cout << "--";
					else
						std::cout << "->";
					std::cout << j << std::endl;
				}
			}
		}
		
		std::cout << "}" << std::endl;
	}

private:
	void DFS( std::vector<bool>& visited, int v /* vertex */){
		visited[v] = true;
		// preorder
		std::cerr << v << " ";
		for (size_t i=0; i<matrix.size(); i++){
			if ( matrix[v][i].exist && !visited[i] ){
				// inorder
				DFS(visited, i);
			}
		}
		// postorder
	}

	void topologicalSort_DFS( std::queue<int>& order, std::vector<bool>& visited, int v /* vertex */){
		visited[v] = true;
		for (size_t i=0; i<matrix.size(); i++){
			if ( matrix[v][i].exist && !visited[i] ){
				topologicalSort_DFS(order, visited, i);
			}
		}
		// postorder
		order.push( v );
	}

public:
	void DFS(int start){
		std::cerr << "DFS" << std::endl;
		std::vector<bool> visited( matrix.size() );
		DFS(visited, start);
		std::cerr << std::endl;
	}	

	void BFS(int start)	{
		std::cerr << "BFS" << std::endl;
		std::vector<bool> visited( matrix.size() );
		std::vector<int> predecesors( matrix.size() );
		std::vector<int> distance( matrix.size() ); // w drzewie to wysokość
		std::queue<int> for_visit;
		for (size_t i=0; i<matrix.size(); i++){
			predecesors[i] = -1;
			distance[i] = 0;
		}

		for_visit.push(start);

		while ( !for_visit.empty() ){
			int v = for_visit.front();
			for_visit.pop();

			for (size_t i=0;  i<matrix.size(); i++){
				if ( matrix[v][i].exist && !visited[i] ){
					visited[i] = true;
					predecesors[i] = v;
					distance[i] = distance[v] + 1;
					for_visit.push(i);
				}
			}
		}

		for (size_t i=0; i<matrix.size(); i++){
			std::cerr << i << "(" << predecesors[i] << "," << distance[i] << ")";
		}
		std::cerr << std::endl;
	}

	std::vector<int> topologicalSort(){
		std::cerr << "Topological Sort" << std::endl;
		std::vector<bool> visited( matrix.size() );
		std::queue<int> order;
		for (size_t i=0; i<matrix.size();i++){
			if ( !visited[i] )
				topologicalSort_DFS(order, visited, i);
		}

		std::vector<int> out( matrix.size() );
		for (size_t i=0; i<matrix.size(); i++){
			out[matrix.size()-1-i] = order.front();
			order.pop();
		}
		return out;
	}

	std::vector<int>/*poprzedników*/ Prim(){
		// zwraca minimalne drzewo rozpinające
		std::cerr << "Prim algorithm" << std::endl;
		std::priority_queue<Edge> Q;
		std::vector<bool> visited( matrix.size() );
		std::vector<int> predecesors( matrix.size() );
		for (size_t i=0; i<matrix.size(); i++){
			predecesors[i] = -1;
		}
		
		for (size_t v=0; v<matrix.size(); v++){
			if ( visited[v] ) continue;
			for (size_t i=0; i<matrix.size(); i++){
				if ( matrix[v][i].exist ){
					Q.push(matrix[v][i]);
					std::cerr << "";
				}
			}
			visited[v] = true;
			while ( !Q.empty() ){
				Edge e = Q.top();
				Q.pop();
				std::cerr << e.from << "->" << e.to << std::endl;
				if ( !visited[e.to] ){
					visited[e.to] = true;
					predecesors[e.to] = e.from;
					for (size_t i=0; i<matrix.size(); i++){
						if ( matrix[e.to][i].exist && !visited[i] )
							Q.push(matrix[e.to][i]);
					}
				}
			}
		}
		return predecesors;

	}


};

int main(){

	GraphMatrixBased graph;
	//graph.makeTemplate();
	graph.makeTemplateWithoutCycles();
	//graph.print(GraphMatrixBased::DIGRAPH);


	// PODSTAWOWE ALGORYTMY GRAFOWE:

	graph.DFS(0);

	graph.BFS(0);
	{
	std::vector<int> out = graph.topologicalSort();
	for (size_t i=0; i<out.size(); i++){
		std::cerr << out[i] << " ";
	}
	std::cerr << std::endl;
	}

	// MINIMALNE DRZEWA ROZPINAJĄCE:
	{
	graph.makeNotDirected();
	graph.print(GraphMatrixBased::GRAPH);
	std::vector<int> out = graph.Prim();
	for (size_t i=0; i<out.size(); i++){
		std::cerr << out[i] << " ";
	}
	std::cerr << std::endl;
	}

	return 0;
}