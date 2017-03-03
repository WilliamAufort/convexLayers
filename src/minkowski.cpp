#include "../include/minkowski.hpp"
#include <fstream>

using namespace std;

/**
* The (naive) Minkowski sum P + P
**/

set<pair<int,int>> NaiveIteration(set<pair<int,int>> s, set<pair<int,int>> init)
{
	set<pair<int,int>> result;

	for (set<pair<int,int>>::iterator it1 = init.begin(); it1 != init.end(); ++it1)
	for (set<pair<int,int>>::iterator it2 = s.begin(); it2 != s.end(); ++it2)
	{
		pair<int,int> p = make_pair(it1->first + it2->first, it1->second + it2->second);
		result.insert(p);
	}
	return result;
}

/**
* The powering of a set (P + P + ... + P)
**/

set<pair<int,int>> powering(set<pair<int,int>> init, int nbIterations)
{
	if (nbIterations <= 1) return init;
	set<pair<int,int>> s = init;
	int n = nbIterations;
	while (n > 1) {
		s = NaiveIteration(s,init);
		n--;
	}
	return s;
}

/**
* Read a polygon contained in a file
**/

set<pair<int,int>> readFile(string filename)
{
	set<pair<int,int>> s;

	ifstream stream(filename);
	int x, y;

	while (stream >> x >> y)
	{
		s.insert(make_pair(x,y));
	}
	return s;
}
