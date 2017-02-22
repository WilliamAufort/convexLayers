#include "../include/convexHulls.hpp"

using namespace std;
using namespace DGtal;

/**
* Delete naively a layer in a set
**/

vector<Point> getDiff(vector<Point> points, vector<Point> layer)
{
    vector<Point> result;
    for (vector<Point>::iterator it = points.begin(); it != points.end(); it++)
	{
		Point p = *it;
		bool inside = false;
		vector<Point>::iterator itl = layer.begin();
		while(itl != layer.end() and not inside)
		{
			if (*itl == p) inside = true;
			else itl++;
		}
		if (not inside) result.push_back(p);
	}
    return result;
}

/**
* Compute the onion peeling
**/

vector<vector<Point>> getLayers(vector<Point> data)
{
	//Set geometric predicate and namespaces
	typedef InHalfPlaneBySimple3x3Matrix<Point, DGtal::int64_t> Functor;  
	Functor functor; 
	typedef PredicateFromOrientationFunctor2<Functor> Predicate; 
	Predicate predicate( functor );
	using namespace functions::Hull2D;
 
	vector<vector<Point>> layers;
	vector<Point> pts = data;
	while (pts.size() != 0 and pts.size() != 1)
	{
		vector<Point> layer;
		andrewConvexHullAlgorithm(pts.begin(), pts.end(), back_inserter(layer), predicate);
		layers.push_back(layer);		
		pts = getDiff(pts,layer); 
	}
	if (pts.size() == 1) layers.push_back(pts);

	return layers;
}

/**
* Converter set<pairs> --> vector<Point> 
**/

vector<Point> vector_of_set(set<pair<int,int>> s)
{
	vector<Point> pts;
	for (set<pair<int,int>>::iterator it = s.begin(); it != s.end(); ++it)
		pts.push_back(Point(it->first,it->second));
	return pts;
}
