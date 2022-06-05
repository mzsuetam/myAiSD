#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <climits>
#include <cstdlib>

#define INF INT_MAX

class GraphMatrixBased{

	struct Edge
	{
		int from, to;
		bool exist = false;
		int weight = 1;

		bool operator<(const Edge& other)const{
			return weight > other.weight; // > bo chcemy kolejkę typu min, a w std:: jest max
		}

	};

	std::vector< std::vector< Edge > > matrix;

public:

	std::vector< std::vector< Edge > > getMatrix() const{
		return matrix;
	}

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
		matrix[1][4].exist = true;
		matrix[2][3].exist = true;
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

	void makeTemplateFull(){
		// initing matrix
		matrix.resize(6);
		for (size_t i=0; i<matrix.size(); i++ ){
			matrix[i].resize(6);
			for (size_t j=0; j<matrix.size(); j++ ){
				matrix[i][j].from = i;
				matrix[i][j].to = j;
				matrix[i][j].exist = true;
			}
		}
		for (size_t i=0; i<matrix.size(); i++ ){
			for (size_t j=0; j<i; j++ ){ 
				matrix[j][i].weight =	matrix[i][j].weight = i*j + i + 1;
				//std::cout << i << j << ": " << matrix[i][j].from << "--" << matrix[i][j].to << " [w=" << matrix[i][j].weight <<"]"<< std::endl;
			}
		}
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
		matrix[0][1].weight = 8;
		matrix[0][2].exist = true;
		matrix[0][2].weight = 4;
		matrix[1][2].exist = true;
		matrix[1][2].weight = 16;
		matrix[1][3].exist = true;
		matrix[1][3].weight = 4;
		matrix[1][4].exist = true;
		matrix[1][4].weight = 32;
		matrix[2][4].exist = true;
		matrix[2][4].weight = 1;
		matrix[3][7].exist = true;
		matrix[3][7].weight = 4;
		matrix[5][8].exist = true;
		matrix[5][8].weight = 100000;
		matrix[6][9].exist = true;
		matrix[6][9].weight = 3;
		matrix[7][8].exist = true;
		matrix[7][8].weight = 9;
		matrix[7][9].exist = true;
		matrix[7][9].weight = 19;
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

	GraphMatrixBased(){}

	GraphMatrixBased( const std::vector<int>& predecesors ){
		size_t new_size = predecesors.size();
		matrix.resize(new_size);
		for (size_t i=0; i<new_size; i++ ){
			matrix[i].resize(new_size);
			for (size_t j=0; j<new_size; j++ ){
				matrix[i][j].from = i;
				matrix[i][j].to = j;
			}
		}
		for (size_t i=0; i<new_size; i++ ){
			int p = predecesors[i];
			if ( p == -1 ) continue;
			matrix[p][i].exist = true;
			matrix[p][i].weight = 1;
		}
	}

	size_t getSize() const{
		return matrix.size();
	}

	int getWeight(size_t x, size_t y) const{
		return matrix[x][y].weight;
	}

	bool getExists(size_t x, size_t y) const
	{
		return matrix[x][y].exist;
	}

private:
	void DFS( std::vector<bool>& visited, int v /* vertex */){
		visited[v] = true;
		// preorder
		std::cout << v << " ";
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
		std::cout << "DFS" << std::endl;
		std::vector<bool> visited( matrix.size() );
		visited.assign(matrix.size(),false);
		DFS(visited, start);
		std::cout << std::endl;
	}	

	void BFS(int start)	{
		std::cout << "BFS" << std::endl;
		std::vector<bool> visited( matrix.size() );
		visited.assign(matrix.size(),false);
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
			std::cout << i << "(" << predecesors[i] << "," << distance[i] << ")";
		}
		std::cout << std::endl;
	}

	std::vector<int> topologicalSort(){
		std::cout << "Topological Sort" << std::endl;
		std::vector<bool> visited( matrix.size() );
		visited.assign(matrix.size(),false);
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
		// Złożonośc O( (V+E)*log_2(V) )
		std::cout << "Prim algorithm" << std::endl;
		std::priority_queue<Edge> Q;
		std::vector<bool> visited( matrix.size() );
		visited.assign(matrix.size(),false);
		std::vector<int> predecesors( matrix.size() );
		for (size_t i=0; i<matrix.size(); i++){
			predecesors[i] = -1;
		}
		
		for (size_t v=0; v<matrix.size(); v++){
			if ( visited[v] ) continue;
			for (size_t i=0; i<matrix.size(); i++){
				if ( matrix[v][i].exist ){
					Q.push(matrix[v][i]);
					std::cout << "";
				}
			}
			visited[v] = true;
			while ( !Q.empty() ){
				Edge e = Q.top();
				Q.pop();
				//std::cout << e.from << "->" << e.to << std::endl;
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

	bool relax( std::vector<int>& predecesors, std::vector<int>& distance, const Edge& e ){
		if ( distance[e.from] == INF ) return false;
		if ( distance[e.from] + e.weight < distance[e.to] ){
			distance[e.to] = distance[e.from] + e.weight;
			predecesors[e.to] = e.from;
			return true;
		}
		return false;
	}

	std::vector<int> Bellman_Ford( int start, bool& exist_negative_cycle ){
		// Złożoność dla listy sąsiedztwa: O( V*E ) 
		// Nasza złożoność: O( V^3 ) (XD)

		std::cout << "Bellman-Ford algorithm" << std::endl;

		// działa również dla ujemnych krawędzi
		std::vector<int> predecesors( matrix.size() );
		std::vector<int> distance( matrix.size() ); 
		for (size_t i=0; i<matrix.size(); i++){
			predecesors[i] = -1;
			distance[i] = INF;
		}
		distance[start] = 0;

		for (size_t i=0; i<matrix.size() -1; i++ ){
			// przejście po wszystkich istniejących krawędziach
			for (size_t j=0; j<matrix.size(); j++ ){
				for (size_t k=0; k<matrix.size(); k++ ){
					if ( matrix[j][k].exist ){
						relax(predecesors, distance, matrix[j][k]);
					}
				}
			}
		}

		exist_negative_cycle = false;
		for (size_t i=0; i<matrix.size(); i++ ){
			for (size_t j=0; j<matrix.size(); j++ ){
				if ( matrix[i][j].exist && distance[matrix[i][j].from] + matrix[i][j].weight < distance[matrix[i][j].to] ){
					exist_negative_cycle = true;
					return predecesors;
				}
			}
		}

		return predecesors;
	}

	std::vector<int> Dijkstra( int start ){ // to się czyta "Dajkstra" :)
		// zwraca odległości pomiędzy startem a każdym innym wierzchołkiem
		// Złożonośc O( (V+E)*log_2(V) )
		std::cout << "Dijkstra algorithm" << std::endl;
		struct Pair{
			int dist; // from start to v
			int v;

			Pair(int _dist, int _v):dist(_dist),v(_v){}

			bool operator<(const Pair& other)const{
				return dist > other.dist; // > bo chcemy kopiec typu min, a w std:: jest max
			}
		};
		std::priority_queue<Pair> Q;
		std::vector<bool> visited( matrix.size() );
		visited.assign(matrix.size(),false);
		std::vector<int> predecesors( matrix.size() );
		std::vector<int> distance( matrix.size() ); 
		for (size_t i=0; i<matrix.size(); i++){
			predecesors[i] = -1;
			distance[i] = INF;
		}
		distance[start] = 0;
		Q.push(Pair(0,start));
		while ( !Q.empty() ){
			int v = Q.top().v;
			Q.pop();
			if ( visited[v] ) continue;
			visited[v]=true;
			for (size_t i=0; i<matrix.size(); i++) {
				if ( matrix[v][i].exist && !visited[i] ){
					if ( relax(predecesors, distance, matrix[v][i]) )
						Q.push(Pair(distance[i],i));
				}
			}
		}
		return predecesors;
	}

	std::vector< std::vector< int > > Floyd_Warshall(){
		std::cout << "Floyd-Warshall algorithm" << std::endl;
		// zwraca najkrótsze ścieżki między każdymi wierzchołkami
		// Złożoność O ( n^3 )
		std::vector< std::vector< int > > distance_matrix;
		std::vector< std::vector< int > > predecesors_matrix;
		distance_matrix.resize(matrix.size());
		predecesors_matrix.resize(matrix.size());
		for (size_t i=0; i<matrix.size(); i++ ){
			distance_matrix[i].resize(matrix.size());
			predecesors_matrix[i].resize(matrix.size());
			for (size_t j=0; j<matrix.size(); j++ ){
				distance_matrix[i][j] = INF;
				predecesors_matrix[i][j] = -1;
				if ( matrix[i][j].exist ){
					distance_matrix[i][j] = matrix[i][j].weight;
					predecesors_matrix[i][j] = i;
				}
				if ( i == j )
					distance_matrix[i][j] = 0;
			}
		}

		for (size_t k=0; k<matrix.size(); k++ ){ // przechodzi po wszystkich k
			for (size_t i=0; i<matrix.size(); i++ ){ // i,j przechodzą po macierzy 
				for (size_t j=0; j<matrix.size(); j++ ){ // ^
					if ( distance_matrix[i][k] != INF && distance_matrix[k][j] != INF
					&& distance_matrix[i][k] + distance_matrix[k][j] < distance_matrix[i][j] ){
						distance_matrix[i][j] = distance_matrix[i][k] + distance_matrix[k][j];
						predecesors_matrix[i][j] = predecesors_matrix[k][j];
					}
				}
			}
		}

		return predecesors_matrix;
	}

	int Ford_Fulkerson_DFS( std::vector< std::vector<int> >& flow_matrix, std::vector<bool>& visited, int v, int end, int min_flow){
		//std::cout << "FF_DFS " << matrix.size() << std::endl;
		visited[v] = true;
		if ( v == end ) return min_flow;
		for (size_t i=0; i<matrix.size(); i++){
			//std::cout << "for1" << std::endl;
			if ( matrix[v][i].exist && !visited[i] ){
				//std::cout << "if1" << std::endl;
				int flow_left = matrix[v][i].weight - flow_matrix[v][i];
				if ( flow_left > 0 ){
					//std::cout << "if2" << std::endl;
					int new_flow = Ford_Fulkerson_DFS(flow_matrix, visited, i, end, std::min(flow_left,min_flow));
					if ( new_flow ){ // znaleźliśmy jakiś przepływ
						//std::cout << "if3" << std::endl;
						flow_matrix[v][i] += new_flow;
						flow_matrix[i][v] -= new_flow;
						return new_flow;
					}
				}
			}
		}
		//std::cout << "FF_DFS end" << std::endl;
		return 0;
	}

	std::vector< std::vector<int> > Ford_Fulkerson(int start, int end){ // maksymalny przepływ
		std::cout << "Ford-Fulkerson algorithm" << std::endl;
		std::vector< std::vector<int> > flow_matrix;
		std::vector< bool > visited;
		visited.assign(matrix.size(),false);
		flow_matrix.resize( matrix.size() );
		for (size_t i=0; i<flow_matrix.size(); i++){
			flow_matrix[i].resize( matrix.size() );
			for (size_t j=0; j<flow_matrix.size(); j++){
				flow_matrix[i][j] = 0;
			}
		}	

		int e = Ford_Fulkerson_DFS(flow_matrix, visited, start, end, INF);
		while (1) {
			//std::cout << "(" << e << ")" << std::endl;
			visited.assign(matrix.size(),false);
			e = Ford_Fulkerson_DFS(flow_matrix, visited, start, end, INF);
			if ( e==0 ) break;
		}

		//std::cout << flow_matrix.size() << std::endl;

		return flow_matrix;
	}

	void printGraph(std::string name = "graph"){
		// http://graphviz.org/doc/info/command.html
		// program.out | dot -Tsvg > output.svg
		graph_type type = GRAPH;

		for ( size_t i=0; i < matrix.size() && type==GRAPH; i++){
			for ( size_t j=0; j < matrix.size(); j++){
				if ( matrix[i][j].exist != matrix[j][i].exist ){
					type = DIGRAPH;
					break;
				}
			}
		}

		std::string dot = "";

		if ( type==GRAPH )
			dot += "graph {";
		else // if (type==DIGRAPH)
			dot += "digraph {";

		for ( size_t i=0; i<matrix.size(); i++){
			dot += std::to_string(i) + " ";
			for ( size_t j=0; j<matrix[i].size(); j++){
				if ( matrix[i][j].exist && ( type==DIGRAPH || i<j )){
					dot += std::to_string(i);
					if ( type==GRAPH )
						dot += "--";
					else
						dot += "->";
					dot += std::to_string(j) + " [weight=" + std::to_string(matrix[i][j].weight) + "] ";
				}
			}
		}
		dot += "}";

		std::string cmd="echo \"" + dot + "\" | dot -Tsvg > graphs_svg/" + name + ".svg; gio open ./graphs_svg/" + name + ".svg";


		//std::cout << cmd << std::endl;

		std::system(cmd.c_str());
	}
};

#ifndef DONT_INCLUDE_MAIN

int main(){

	GraphMatrixBased graph;
	//graph.makeTemplate();
	graph.makeTemplateWithoutCycles();
	graph.printGraph("17_graph_without_cycles");


	// PODSTAWOWE ALGORYTMY GRAFOWE:

	graph.DFS(0);

	graph.BFS(0);
	{
		std::vector<int> out = graph.topologicalSort();
		for (size_t i=0; i<out.size(); i++){
			std::cout << out[i] << " ";
		}
		std::cout << std::endl;
	}

	// MINIMALNE DRZEWA ROZPINAJĄCE:
	{
		GraphMatrixBased g2 = graph;
		g2.makeNotDirected();
		//graph.print(GraphMatrixBased::GRAPH);
		std::vector<int> out = g2.Prim();
		for (size_t i=0; i<out.size(); i++){
			std::cout << out[i] << " ";
		}
		std::cout << std::endl;
	}

	// NAJKRÓTSZE ŚCIEŻKI Z 1 ŹRÓDŁEM:
	{
		//graph.print(GraphMatrixBased::DIGRAPH);

		bool exist_negative_cycle;
		std::vector<int> out = graph.Bellman_Ford(0,exist_negative_cycle);
		for (size_t i=0; i<out.size(); i++){
			std::cout << out[i] << " ";
		}
		std::cout << std::endl;

		std::vector out2 = graph.Dijkstra(0);
		for (size_t j=0; j<out.size(); j++){
			std::cout << ( (out2[j]!=INF) ? out2[j] : -1 ) << " ";
		}
		GraphMatrixBased dji_graph(out2);
		dji_graph.printGraph("17_dji_graph");
		std::cout << std::endl;

	}
	
	// NAJKRÓTSZE ŚCIEŻKI MIĘDZY WSZYSTKIMI PARAMI WIERZCHOŁKÓW
	{
		// *tego na kolosie nie będzie
		//graph.print(GraphMatrixBased::GRAPH);
		std::vector< std::vector<int> > out = graph.Floyd_Warshall();
		for (size_t i=0; i<out.size(); i++){
			for (size_t j=0; j<out.size(); j++){
				std::cout << ( ( out[i][j]!=INF ) ? out[i][j] : -1 ) << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		 
	}

	// MAKSYMALNY PRZEPŁYW:
	{
		graph.makeNotDirected();
		graph.printGraph("17_graph_not_directed");

		std::vector< std::vector<int> > out = graph.Ford_Fulkerson(0,9);
		//std::cout << out.size() <<  std::endl;	
		for (size_t i=0; i<out.size(); i++){
			for (size_t j=0; j<out.size(); j++){
				std::cout << ( ( out[i][j]!=INF ) ? out[i][j] : -1 ) << " ";
			}
			std::cout << std::endl;
		}
		std::cout <<  std::endl;	
	}

	return 0;
}

#endif