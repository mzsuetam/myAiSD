#include <iostream>
#include <vector>
#include <algorithm>

#define DONT_INCLUDE_MAIN
#include "17_graph.cpp"
#include "lib/timer.h"

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

std::vector<int> komiwojazer(const GraphMatrixBased &graph, int &_min_distance)
{
	// Znalezienie minimalnego cyklu Hamiltona w pełnym grafie ważonym
	int min_distance = INT_MAX;
	std::vector<int> min_cycle;

	Permutations permutacja(graph.getSize());
	do
	{
		std::vector<int> P = permutacja.getPermutation();
		// std::cout << static_cast<std::string>(permutacja) << std::endl;
		int sum = 0;
		for (size_t i = 0; i < P.size() - 1; i++)
		{
			sum += graph.getWeight(P[i], P[i + 1]);
		}
		sum += graph.getWeight(P[P.size() - 1], P[0]);
		if (sum < min_distance)
		{
			min_cycle = P;
			min_distance = sum;
		}
	}
	while (permutacja.nextPermutation());

	_min_distance = min_distance;
	return min_cycle;
}

std::vector<int> problem_kliki(const GraphMatrixBased &graph, int k)
{ 
	// Stwierdzenie, czy w danym grafie istnieje klika o podanym rozmiarze k
	std::vector<int> wynik;
	size_t n = graph.getSize();
	SubSets podzbior(n, k);

	do // przechodzimy się po podzbiorach o wielkości k
	{
		long long p = podzbior.getSubset();
		bool czy_dobry = true;

		for (size_t i = 0; i < n && czy_dobry; i++) // przejście po wierzchołkach w grafie
			if (p & (1 << i)) // czy wierzchołek jest w podzbiorze
				for (size_t j = 0; j < n && czy_dobry; j++) // prejście po wierzchołkach 
					if (i != j && !graph.getExists(i, j) && (p & (1 << j)))
						czy_dobry = false;

		if (czy_dobry)
		{
			for (size_t i = 0; i < n; i++)
				if (p & (1 << i))
					wynik.push_back(i);

			return wynik;
		}
	}
	while (podzbior.nextSubSet());

	return wynik;
}

std::vector <int> pokrycie_wierzcholkowe(const GraphMatrixBased &graph, int k)
{
	// Znalezie nie pokrycia wierzchołkowego o wielkości k 
	// Pokrycie wierzchołkowe grafu G to taki podzbiór wierzchołków G,
	//	że każda krawędź G jest incydentna do jakiegoś wierzchołka z tego podzbioru
	std::vector<int> wynik;
	size_t n = graph.getSize();
	SubSets podzbior(n, k);

	do
	{
		long long p = podzbior.getSubset();
		bool czy_dobry = true;

		for(size_t i = 0; i < n && czy_dobry; i++)
			for(size_t j = 0; j < n && czy_dobry; j++)
				if(graph.getExists(i, j) && !((p & (1 << i)) || (p & (1 << j))))
					czy_dobry = false;

		if(czy_dobry)
		{
			for (size_t i = 0; i < n; i++)
				if (p & (1 << i))
					wynik.push_back(i);

			return wynik;
		}
	}
	while(podzbior.nextSubSet());

	return wynik;
}

std::vector <int> cykl_Hamiltona(const GraphMatrixBased &graph)
{
	std::vector<int> wynik;
	size_t n = graph.getSize();
	Permutations perm(n);

	do
	{
		const std::vector<int> &perm_v = perm.getPermutation();
		bool czy_dobry = true;

		for(size_t i = 0; i < n - 1 && czy_dobry; i++)
			if(!graph.getExists(perm_v[i], perm_v[i + 1]))
				czy_dobry = false;
		if(!graph.getExists(perm_v[n - 1], perm_v[0]))
			czy_dobry = false;

		if(czy_dobry)
			return perm_v;
	}
	while(perm.nextPermutation());

	return std::vector <int> ();
}

std::vector <bool> podzial_zbioru(const std::vector <int> &liczby, bool &istnieje)
{
	int n = liczby.size(), suma = 0;
	SubSets podzbior(n);

	istnieje = false;

	for(int i = 0; i < n; i++)
		suma += liczby[i];
	
	if(suma % 2 == 1)
		return std::vector <bool> ();

	do
	{
		long long p = podzbior.getSubset();
		int suma_t = 0;

		for(int i = 0; i < n; i++)
			if(p & (1 << i))
				suma_t += liczby[i];
		
		if(suma_t * 2 == suma)
		{
			std::vector <bool> wynik(n);

			for(int i = 0; i < n; i++)
				wynik[i] = p & (1 << i);

			istnieje = true;
			return wynik;
		}
	}
	while (podzbior.nextSubSet());
	
	return std::vector <bool> ();
}

std::vector <bool> podzial_zbioru_dynamiczny_plecak(const std::vector <int> &liczby, bool &istnieje)
{
	int n = liczby.size(), suma = 0;

	istnieje = false;

	for(int i = 0; i < n; i++)
		suma += liczby[i];
	
	if(suma % 2 == 1)
		return std::vector <bool> ();

	int oczekiwana_suma = suma / 2;

	std::vector <std::vector<int>> plecak(n + 1);
	for(int i = 0; i <= n; i++)
		plecak[i].resize(oczekiwana_suma + 1);

	for(int i = 0; i <= n; i++)
	{
		for(int j = 0; j <= oczekiwana_suma; j++)
		{
			if(i == 0 || j == 0)
				plecak[i][j] = 0;
			else
			{
				plecak[i][j] = plecak[i - 1][j];
				if(j - liczby[i - 1] >= 0 && plecak[i - 1][j - liczby[i - 1]] + liczby[i - 1] > plecak[i][j])
					plecak[i][j] = plecak[i - 1][j - liczby[i - 1]] + liczby[i - 1];
			}
		}
	}

	if(plecak[n][oczekiwana_suma] != oczekiwana_suma)
		return std::vector <bool> ();

	istnieje = true;

	int suma_teraz = oczekiwana_suma, przedmiot = n;

	std::vector <bool> wynik(n);
	wynik.assign(n, false);

	while(suma_teraz > 0 && przedmiot > 0)
	{
		if(plecak[przedmiot][suma_teraz] == plecak[przedmiot - 1][suma_teraz])
		{
			przedmiot--;
		}
		else
		{
			wynik[przedmiot - 1] = true;
			przedmiot--;
			suma_teraz -= liczby[przedmiot];
		}
	}

	return wynik;
}

int main()
{
	srand(time(nullptr));

	// Generowanie wszystkich podzbiorów (ten nie jest NP):
	std::cout << "Podzbiory:" << std::endl;
	SubSets zbior(5, 2);
	do
	{
		std::cout << static_cast<std::string>(zbior) << '\n';
	}
	while (zbior.nextSubSet());

	{
		// Problem komiwojażera
		std::cout << std::endl;
		std::cout << "Komiwojażer:" << std::endl;
		GraphMatrixBased graph;
		graph.makeTemplateFull();
		graph.printGraph("18_komiwojażer");
		int dist;
		std::vector<int> min_cycle = komiwojazer(graph, dist);
		for (size_t i = 0; i < min_cycle.size(); i++)
		{
			std::cout << min_cycle[i] << "->";
		}
		std::cout << min_cycle[0] << " dist: " << dist << std::endl;
	}

	{
		// Problem podkliki
		std::cout << std::endl;
		std::cout << "Problem kliki:" << std::endl;
		// czy w danym grafie istnieje klika o podanym rozmiarze k
		GraphMatrixBased graph;
		graph.makeTemplate();
		graph.makeNotDirected();
		graph.printGraph("18_klika");

		int k = 4;

		std::vector <int> klika = problem_kliki(graph, k);

		if(klika.size() != 0)
		{
			for(size_t i = 0; i < klika.size(); i++)
				std::cout << klika[i] << ' ';
			std::cout << std::endl;
		}
		else
			std::cout << "Nie istnieje " << k << "-klika jako podgraf tego grafu" << std::endl;
	}

	{
		// Pokrycie wierzcholkowe
		std::cout << std::endl;
		std::cout << "Problem pokrycia wierzcholkowego:" << std::endl;
		GraphMatrixBased graph;
		graph.makeTemplate();
		graph.makeNotDirected();
		graph.printGraph("18_pokrycie_wierzcholkowe");

		int k = 4;

		std::vector <int> pokrycie = pokrycie_wierzcholkowe(graph, k);

		if(pokrycie.size() != 0)
		{
			for(size_t i = 0; i < pokrycie.size(); i++)
				std::cout << pokrycie[i] << ' ';
			std::cout << std::endl;
		}
		else
			std::cout << "Nie istnieje pokrycie wierzcholkowe o k = " << k << std::endl;
	}

	{
		// Cykl Hamiltona
		std::cout << std::endl;
		std::cout << "Cykl Hamiltona: " << std::endl;
		GraphMatrixBased graph;
		graph.makeTemplate();
		graph.makeNotDirected();
		graph.printGraph("18_cykl_Hamiltona");

		std::vector <int> cykl = cykl_Hamiltona(graph);

		if(cykl.size() != 0)
		{
			for(size_t i = 0; i < cykl.size(); i++)
				std::cout << cykl[i] << ' ';
			std::cout << std::endl;
		}
		else
			std::cout << "Nie ma cyklu Hamiltona w tym grafie!" << std::endl;
	}

	{
		// Problem podzialu zbioru
		std::cout << std::endl;
		std::cout << "Problem podzialu zbioru:" << std::endl; // Mozna zrobic dla malych liczb szybciej dynamicznie (problem plecakowy)
		size_t n = 64, maks = 1000;
		bool istnieje = true;
		int suma;
		std::vector <int> liczby(n);
		
		for(size_t i = 0; i < n; i++)
			std::cout << (liczby[i] = rand() % (maks + 1)) << ' ';
		std::cout << std::endl;

		std::vector <bool> wynik = podzial_zbioru(liczby, istnieje);
		if(istnieje)
		{
			suma = 0;
			std::cout << "Podzial:\nCzesc 1:" << std::endl;
			for(size_t i = 0; i < n; i++)
				if(wynik[i])
				{
					suma += liczby[i];
					std::cout << liczby[i] << ' ';
				}
			std::cout << std::endl;
			std::cout << "Suma: " << suma << std::endl;

			suma = 0;
			std::cout << "\nCzesc 2:" << std::endl;
			for(size_t i = 0; i < n; i++)
				if(!wynik[i])
				{
					suma += liczby[i];
					std::cout << liczby[i] << ' ';
				}
			std::cout << std::endl;
			std::cout << "Suma: " << suma << std::endl;
		}
		else
			std::cout << "Nie istnieje podzial tego zbioru" << std::endl;

		// Dynamicznie
		std::cout << std::endl;
		std::cout << "Problem podzialu zbioru dynamicznie:" << std::endl;
		wynik = podzial_zbioru_dynamiczny_plecak(liczby, istnieje);
		if(istnieje)
		{
			suma = 0;
			std::cout << "Podzial:\nCzesc 1:" << std::endl;
			for(size_t i = 0; i < n; i++)
				if(wynik[i])
				{
					suma += liczby[i];
					std::cout << liczby[i] << ' ';
				}
			std::cout << std::endl;
			std::cout << "Suma: " << suma << std::endl;

			suma = 0;
			std::cout << "\nCzesc 2:" << std::endl;
			for(size_t i = 0; i < n; i++)
				if(!wynik[i])
				{
					suma += liczby[i];
					std::cout << liczby[i] << ' ';
				}
			std::cout << std::endl;
			std::cout << "Suma: " << suma << std::endl;
		}
		else
			std::cout << "Nie istnieje podzial tego zbioru" << std::endl;
	}

	///
	return 0;
}