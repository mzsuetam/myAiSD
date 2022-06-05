#include <iostream>
#include <vector>
#include <algorithm>

#define DONT_INCLUDE_MAIN
#include "17_graph.cpp"

class SubSets
{
	long long sub_set = 0;
	long long end_set = 0;
	size_t size = 0;
	size_t k = 0;

public:
	SubSets() {}
	SubSets(size_t src_size, int _k = 0) : k(_k)
	{
		if (src_size > sizeof(long long) * 8 || k > src_size)
		{
			throw std::out_of_range("Too big!");
		}
		size = src_size;

		if (k == 0)
		{
			for (size_t i = 0; i < size; i++)
			{
				end_set |= (1ll << i); // << przesuwa się po incie, dlatego dajemy 1ll
			}
		}
		else
		{
			for (size_t i = 0; i < k; i++)
			{
				sub_set |= (1ll << i);
				end_set |= (1ll << (size - 1 - i));
			}
		}
	}

	long long getSubset() const
	{
		return sub_set;
	}

	long long popSubset()
	{
		long long tmp = sub_set;
		nextSubSet();
		return tmp;
	}

	bool nextSubSet()
	{
		if (sub_set == end_set)
			return false;

		if (k)
		{
			for (size_t i = 0, ile_jedynek = 0; i < size; i++)
			{
				if ((sub_set & (1ll << i)) && !(sub_set & (1ll << (i + 1))))
				{
					// znaleziona odpowiednia jedynka

					// zmiana miejsca tej jedynki
					sub_set ^= (3ll << i);
					break;
				}

				if (sub_set & (1ll << i))
				{
					sub_set |= (1ll << ile_jedynek);
					if (ile_jedynek != i)
						sub_set ^= (1ll << i);
					ile_jedynek++;
				}
			}
		}
		else
			sub_set++;

		return true;
	}

	operator std::string() const
	{
		std::string value = "";

		for (size_t i = 0; i < size; i++)
			value += (sub_set & (1ll << i)) ? '1' : '-';

		return value;
	}
};

class Permutations
{
	std::vector<int> perms;

	size_t n;

public:

	Permutations(size_t _n) : n(_n)
	{
		perms.resize(n);

		for (size_t i = 0; i < n; i++)
			perms[i] = i;
	}

	const std::vector<int> &getPermutation() const
	{
		return perms;
	}

	bool nextPermutation()
	{
		return std::next_permutation(perms.begin(), perms.end());
	}

	operator std::string() const
	{
		std::string value = "";

		for (size_t i = 0; i < perms.size(); i++)
		{
			value += '0' + perms[i];
		}

		return value;
	}
};

std::vector <int> komiwojazer( GraphMatrixBased& graph, int& _min_distance ){
	int min_distance = INT_MAX;
	std::vector <int> min_cycle;

	Permutations permutacja( graph.getSize() );
	do
	{
		std::vector <int> P = permutacja.getPermutation();
		//std::cout << static_cast<std::string>(permutacja) << std::endl;
		int sum=0;
		for (size_t i = 0; i < P.size() - 1; i++)
		{
			sum += graph.getWeight(P[i], P[i + 1]);
		}
		sum += graph.getWeight(P[P.size() - 1], P[0]);
		if ( sum < min_distance )
		{
			min_cycle = P;
			min_distance = sum;
		}
	}
	while (permutacja.nextPermutation());

	_min_distance = min_distance;
	return min_cycle;	
}

int main()
{
	// Generowanie wszystkich podzbiorów (ten nie jest NP):
	std::cout << "Podzbiory:" << std::endl;
	SubSets zbior(5, 2);
	do { std::cout << static_cast <std::string> (zbior) << '\n'; }	
	while(zbior.nextSubSet());


	// Problem komiwojażera

	std::cout << "Komiwojażer:" << std::endl;
	GraphMatrixBased graph;
	graph.makeTemplateFull();
	graph.printGraph("18_komiwojażer");
	int dist;
	std::vector<int> min_cycle = komiwojazer(graph, dist);
	for(size_t i = 0; i < min_cycle.size(); i++)
	{
		std::cout << min_cycle[i] << "->";
	}
	std::cout << min_cycle[0] << " dist: " << dist << std::endl;
	
	
	
	///
	return 0;
}