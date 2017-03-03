#include "../include/convexHulls.hpp"
#include "../include/minkowski.hpp"
#include "../include/parserArguments.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	parserArguments arguments(parserArguments::getOptionsNames(), parserArguments::getParametersNames());
	arguments.parse(argc,argv);
	if (arguments.askHelp())
	{
		cout << endl << "Use the following syntax :" << endl;
		cout << "-i=input             Import a polygon in a text file (default: polygon.txt)" << endl;
		cout << "--iterations=nb      Choose the powering of your polynomial (default: 1)" << endl;
		cout << "-o=output            Output the drawing in a eps file (default: test.eps)" << endl;
		cout << "--help               You're currently in the help mode" << endl;
		return EXIT_FAILURE;
	}

	// Compute the layers
	set<pair<int,int>> mySet = readFile(arguments.getParameter("i","polygon.txt"));
	int nbIterations = stoi(arguments.getParameter("-iterations","1"));
	set<pair<int,int>> s = powering(mySet,nbIterations);
	vector<vector<Point>> res = getLayers(vector_of_set(s));

	// Save the drawing
	Board2D board;
	drawLayers(res.begin(), res.end(),board, res.size());
	board.saveEPS((arguments.getParameter("o","test.eps")).c_str());

	return EXIT_SUCCESS;
}
