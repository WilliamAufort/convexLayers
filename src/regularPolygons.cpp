#include <cmath>
#include <fstream>
#include "../include/minkowski.hpp"
#include "../include/convexHulls.hpp"

using namespace std;

float pi = 3.14159265358979323846;

int expectedBound(int n)
{
	int result = n*(n+1)*(n+2)/6;
	if (n % 3 == 0) result += 2*n/3;
	if (n % 2 == 0) result += n*(n+2)/2;
	else result += n*(n+1)/2;
	result /= (2*n);
	return result;
}	

set<pair<int,int>> buildPolygon(int n, int precision)
{
	set<pair<int,int>> myPolygon;
	for (int k = 0; k < n; k++)
	{
		double x = round(precision*cos(2*k*pi/n));
		double y = round(precision*sin(2*k*pi/n));
		//cout << x << " " << y << " " << static_cast<int>(x) << " " << static_cast<int>(y) << endl;
		myPolygon.insert(make_pair(static_cast<int>(x),static_cast<int>(y)));
	}	
	//cout << endl;
	return myPolygon;
}

void exportPolygon(int n, int precision, string filename)
{
	ofstream file;
	file.open(filename.c_str());
	if (file.is_open())
	{
		for (int k = 0; k < n; k++)
		{
			double x = round(precision*cos(2*k*pi/n));
			double y = round(precision*sin(2*k*pi/n));
			file << x << " " << y << endl;
		}	
		file.close();
}	}

int main(int argc, char* argv[])
{
	int n = atoi(argv[1]);
	cout << "Expected bound" << expectedBound(n) << endl;
	cout << "Precision      Number of layers" << endl;	
	for (int precision = 100; precision <= 10000000; precision *= 2)
	{	
		set<pair<int,int>> s = buildPolygon(n,precision);
		vector<vector<Point>> layers = getLayers(vector_of_set(powering(s,3)));
		cout << "   " << precision << "          " << layers.size() << endl;
	}
	// Debug
	/*Board2D board;
	drawLayers(layers.begin(), layers.end(),board, layers.size());
	board.saveEPS("debug13.eps");
	exportPolygon(13,precision,"13.txt");*/
	
	return EXIT_SUCCESS;
}
