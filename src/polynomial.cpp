/***********************************
* Minkowski sums of identical sets *
************************************/

#include <iostream>
#include <cmath>
#include <set>
#include <utility> // pair
#include <vector>

using namespace std;

void print_set(set<pair<int,int>> s)
{
	for (set<pair<int,int>>::iterator it= s.begin(); it != s.end(); ++it)
		cout << "(" << it->first << "," << it->second << ")";
	cout << endl;
}

set<pair<int,int>> NaiveIteration(set<pair<int,int>> s, set<pair<int,int>> init) // Naive but OK
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

void generate_logs(int nb_iterations) {
	cout << "x <- c(";
	for (int i = 1; i < nb_iterations; i++) {
		cout << log(i) << ",";
	}
	cout << log(nb_iterations) << ")" << endl;
}


void generate_R_script(vector<int> sizes, int nb_iterations, bool log_plot) {
	cout << "# R script automatically generated" << endl;
	cout << "x <- c(";
	for (int i = 0; i < nb_iterations; i++) {
		cout << i << ",";
	}
	cout << nb_iterations << ")" << endl;
	cout << "y <- c(";
	for (int i = 0; i < nb_iterations; i++) {
		if (log_plot) { cout << log(sizes[i]) << ",";}
		else 		  { cout << sizes[i] << ",";}
	}
	if (log_plot) { cout << log(sizes[nb_iterations]) << ")" << endl;}
	else 		  { cout << sizes[nb_iterations] << ")" << endl;}
	cout << "plot(x,y, xlab=\"iterations\", ylab=\"number of monomials\", main=\"Size of a Minkowski sum of powers of a polynomial\", pch=20)";	
}

set<pair<int,int>> test_polygon(int t)
{
	set<pair<int,int>> init;
	init.insert(make_pair(10,1));
	init.insert(make_pair(1,9));
	init.insert(make_pair(1,1));
	return init;
}

set<pair<int,int>> build_my_polygon(int t)
{
	set<pair<int,int>> my_set;
	for (unsigned int i = 2; i <= t; i++) {
		my_set.insert(make_pair(i,1));
		my_set.insert(make_pair(1,i));
	}
	my_set.insert(make_pair(1,1));
	return my_set;
}

int main(int argc, char* argv[])
{
	int nb_iterations = 200;
	int t = 5 ; // The polygon will contain 2t-1 vertices
	vector<int> sizes(nb_iterations+1,0);
	bool verbose = false;
	bool log_plot = true;

	set<pair<int,int>> init = build_my_polygon(t);
	if (verbose) {print_set(init);}

	// Initialize
	set<pair<int,int>> res = init;
	sizes[0] = init.size();

	// Compute
	/*for (int i = 0; i < nb_iterations; i++) {
		res = NaiveIteration(res,init);
		sizes[i+1] = res.size();
		if (verbose) {cout << "At step " << i+1 << ", init contains:"; print_set(res);}
	}*/	
	//generate_R_script(sizes,nb_iterations,log_plot);
	generate_logs(nb_iterations);

	return EXIT_SUCCESS;
}
