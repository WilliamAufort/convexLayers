#include <iostream>
#include <cmath>

#include "DGtal/base/Common.h"
#include "DGtal/base/IteratorCirculatorTraits.h"
#include "DGtal/helpers/StdDefs.h"

#include "DGtal/geometry/tools/Hull2DHelpers.h"
#include "DGtal/geometry/tools/PolarPointComparatorBy2x2DetComputer.h"
#include "DGtal/geometry/tools/determinant/AvnaimEtAl2x2DetSignComputer.h"
#include "DGtal/geometry/tools/determinant/InHalfPlaneBySimple3x3Matrix.h"

#include "DGtal/shapes/ShapeFactory.h"
#include "DGtal/shapes/Shapes.h"

#include "DGtal/topology/DigitalSetBoundary.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/graph/DepthFirstVisitor.h"

#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/colormaps/HueShadeColorMap.h"

using namespace std;
using namespace DGtal;

typedef PointVector<2,DGtal::int32_t> Point;


////////////////////// RANDOM ENGINE //////////////////////////////////////////////////////////////////////

class RandomEngine
{
	public:
		RandomEngine(unsigned int n);
		~RandomEngine() {};

		unsigned int sample();

	private:
		std::default_random_engine m_engine;
		std::uniform_real_distribution<double> m_distrib;
};

RandomEngine::RandomEngine(unsigned int n) : m_engine(default_random_engine()), m_distrib(uniform_real_distribution<double>(0,n+1)) {}

unsigned int RandomEngine::sample()
{
	double d = m_distrib(m_engine);
	return static_cast<unsigned int>(floor(d));	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////


template <typename ForwardIterator, typename Board>
void drawPolygon(const ForwardIterator& itb, const ForwardIterator& ite, Board& aBoard, Color c)
{
    BOOST_CONCEPT_ASSERT(( boost_concepts::ForwardTraversalConcept<ForwardIterator> )); 
    BOOST_CONCEPT_ASSERT(( boost_concepts::ReadableIteratorConcept<ForwardIterator> )); 
    typedef typename IteratorCirculatorTraits<ForwardIterator>::Value Point; 

    ForwardIterator it = itb; 
    if (it != ite) {
        // First point
        Point p1 = *it;
        Point p = p1;

        aBoard << SetMode(p.className(),"Grid")
	           << CustomStyle( p.className()+"/Grid",new CustomColors(c,c))
	           << p;

        Point prev = p; 
        for (++it; it != ite; ++it, prev = p) {
            // All other points
	        p = *it; 
	        aBoard << p; 
	        if (prev != p) aBoard.drawLine(prev[0], prev[1], p[0], p[1]); 
	    }

    //display the last edge too
	if (prev != p1) aBoard.drawLine(prev[0], prev[1], p1[0], p1[1]); 
}   }


template <typename ForwardIterator, typename Board>
void drawPointset(const ForwardIterator& itb, const ForwardIterator& ite, 
		 Board& aBoard)
{
  BOOST_CONCEPT_ASSERT(( boost_concepts::ForwardTraversalConcept<ForwardIterator> )); 
  BOOST_CONCEPT_ASSERT(( boost_concepts::ReadableIteratorConcept<ForwardIterator> )); 
  typedef typename IteratorCirculatorTraits<ForwardIterator>::Value Point; 
  ForwardIterator it = itb; 
  if (it != ite)
  {
    //for the first point
    Point p1 = *it;
    Point p = p1; 
    //display
    aBoard << SetMode( p.className(), "Grid" )
	       << p;
    Point prev = p; 
    for (++it; it != ite; ++it, prev = p)
	{
	  //for all other points
	  p = *it; 
	  aBoard << p;
}  }  }

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
		/*cout << "Layer " << endl;		
		copy(layer.begin(), layer.end(), ostream_iterator<Point>( cout, "\n" ) );
		cout << endl;*/
		
		pts = getDiff(pts,layer); 
	}
	if (pts.size() == 1)
	{
		layers.push_back(pts);
		/* << "Layer " << endl;		
		copy(pts.begin(), pts.end(), ostream_iterator<Point>( cout, "\n" ) );
		cout << endl;*/
	}
	return layers;
}

template <typename ForwardIterator, typename Board>
void drawLayers(const ForwardIterator& itb, const ForwardIterator& ite, Board& aBoard, unsigned int size)
{
    BOOST_CONCEPT_ASSERT(( boost_concepts::ForwardTraversalConcept<ForwardIterator> )); 
    BOOST_CONCEPT_ASSERT(( boost_concepts::ReadableIteratorConcept<ForwardIterator> )); 
    typedef typename IteratorCirculatorTraits<ForwardIterator>::Value Point; 

	HueShadeColorMap<double> colorMap(1,size);
	unsigned int compteur = 1; 

    ForwardIterator it = itb;
	for (ForwardIterator it = itb; it != ite; it++)
	{
		Color c = colorMap(compteur);
		drawPolygon(it->begin(),it->end(),aBoard,c);
		compteur++;
	}
}

vector<Point> randomSet(RandomEngine& eng, unsigned int t)
{
	vector<Point> set;
    for (unsigned int i = 0; i < t; i++)
	{
		unsigned int x = eng.sample();
		unsigned int y = eng.sample();
		set.push_back(Point(x,y));
	}
	return set;
}

void doStatistics(unsigned int n, unsigned int t, unsigned int nb_exp, ostream& s)
{
	RandomEngine eng(n);
	for (unsigned int i = 0; i < nb_exp; i++)
	{
		vector<Point> set = randomSet(eng, t);
		vector<vector<Point>> res = getLayers(set);
		unsigned int nb_layers = res.size();
		unsigned int monomials = 0;
		for (unsigned int j = 0; j < nb_layers;j++)
			monomials += res[j].size();
		s << monomials << "," << nb_layers << endl;
}	}

    

int main(int argc, char** argv) {
  
  DGtal::trace.info() << "Some test for convex hull " << endl;

  unsigned int n = 200;
  vector<unsigned int> t_values = {10,20,30,40,50,60,70,80,90,100,120,140,160,180,200,230,260,290,320};
  ofstream file("values.csv");
  if (file.is_open())
  {
	file << "nb of monomials, nb layers" << endl; 
    for (unsigned int i = 0; i != t_values.size(); i++)
    {
	  unsigned int t = t_values[i];
	  cout << "Processing t = " << t << endl;
      doStatistics(n,t,5*t,file);
  } }

  /*  Board2D board;
  drawLayers(res.begin(),res.end() ,board, res.size());
  board.saveEPS( "test.eps" );*/
  
  return 0;
}
