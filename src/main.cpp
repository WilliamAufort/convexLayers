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
		cout << "./program --stats    For the default statistics" << endl;
		cout << "./program --cex      To display the counter-example" << endl;
		cout << "For a general usage, there are the following options :" << endl;
		cout << "-i=input             Import a polygon in a text file (see polygon.txt)" << endl;
		cout << "--iterations=nb      Choose the powering of your polynomial (default 1)" << endl;
		cout << "-o=output            Output the drawing in a eps file (default test.eps)" << endl;
		cout << "--help               You're currently in the help mode" << endl;
		return EXIT_FAILURE;
	}

	// Set the options
	bool optStats = arguments.getOption("-stats");
	bool optCex = arguments.getOption("-cex");

	if (optStats) {
		cout << "Not implemented yet" << endl;
		// TODO Just copy-paste, not used anymore in the internship
	}

	else if (optCex) {
		Board2D board;
		set<pair<int,int>> init = buildCounterExample();
		set<pair<int,int>> s = NaiveIteration(init,init);
		vector<vector<Point>> res = getLayers(vector_of_set(s));
		drawLayers(res.begin(), res.end(), board, res.size());
		board.saveEPS((arguments.getParameter("o","counter_ex.eps")).c_str());
	}

	else 
	{
		set<pair<int,int>> mySet = readFile(arguments.getParameter("i","polygon.txt"));
		int nbIterations = stoi(arguments.getParameter("-iterations","1"));
		Board2D board;
		set<pair<int,int>> s = powering(mySet,nbIterations);
		vector<vector<Point>> res = getLayers(vector_of_set(s));
		drawLayers(res.begin(), res.end(),board, res.size());
		board.saveEPS((arguments.getParameter("o","test.eps")).c_str());
	}

	return EXIT_SUCCESS;
}
