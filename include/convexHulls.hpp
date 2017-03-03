#include <iostream>
#include <cmath>

#include "DGtal/base/Common.h"
#include "DGtal/base/IteratorCirculatorTraits.h"
#include "DGtal/helpers/StdDefs.h"

#include "DGtal/geometry/tools/Hull2DHelpers.h"
#include "DGtal/geometry/tools/determinant/InHalfPlaneBySimple3x3Matrix.h"

#include "DGtal/shapes/ShapeFactory.h"
#include "DGtal/shapes/Shapes.h"

#include "DGtal/topology/DigitalSetBoundary.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/graph/DepthFirstVisitor.h"

#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/colormaps/HueShadeColorMap.h"

using namespace DGtal;

typedef PointVector<2,DGtal::int32_t> Point;

/**
* Display a polygon
**/

template <typename ForwardIterator, typename Board>
void drawPolygon(const ForwardIterator& itb, const ForwardIterator& ite, Board& aBoard, Color c)
{
	BOOST_CONCEPT_ASSERT(( boost_concepts::ForwardTraversalConcept<ForwardIterator> )); 
	BOOST_CONCEPT_ASSERT(( boost_concepts::ReadableIteratorConcept<ForwardIterator> )); 
	typedef typename IteratorCirculatorTraits<ForwardIterator>::Value Point; 

	ForwardIterator it = itb; 
	if (it != ite) 
	{
		// First point
		Point p1 = *it;
		Point p = p1;

		aBoard << SetMode(p.className(),"Grid")
			   << CustomStyle( p.className()+"/Grid",new CustomColors(c,c))
			   << p;

		Point prev = p; 
		for (++it; it != ite; ++it, prev = p) 
		{
			// All other points
			p = *it; 
			aBoard << p; 
			if (prev != p) aBoard.drawLine(prev[0], prev[1], p[0], p[1]); 
		}

    // Display the last edge too
	if (prev != p1) aBoard.drawLine(prev[0], prev[1], p1[0], p1[1]); 
}   }


/**
* Display a point set
**/

template <typename ForwardIterator, typename Board>
void drawPointset(const ForwardIterator& itb, const ForwardIterator& ite, Board& aBoard)
{
	BOOST_CONCEPT_ASSERT(( boost_concepts::ForwardTraversalConcept<ForwardIterator> )); 
	BOOST_CONCEPT_ASSERT(( boost_concepts::ReadableIteratorConcept<ForwardIterator> )); 
	typedef typename IteratorCirculatorTraits<ForwardIterator>::Value Point; 
	ForwardIterator it = itb; 
	if (it != ite)
	{
		// First point
		Point p1 = *it;
		Point p = p1; 
		// Display
		aBoard << SetMode( p.className(), "Grid" ) << p;
		Point prev = p; 
		for (++it; it != ite; ++it, prev = p)
		{
			// All other points
			p = *it; 
			aBoard << p;
}	}	}

/* Convex layers functions */

std::vector<Point> getDiff(std::vector<Point> points, std::vector<Point> layer);
std::vector<std::vector<Point>> getLayers(std::vector<Point> data);
std::vector<Point> vector_of_set(std::set<std::pair<int,int>> s);

/**
* Display the layers
**/

template <typename ForwardIterator, typename Board>
void drawLayers(const ForwardIterator& itb, const ForwardIterator& ite, Board& aBoard, unsigned int size)
{
    BOOST_CONCEPT_ASSERT(( boost_concepts::ForwardTraversalConcept<ForwardIterator> )); 
    BOOST_CONCEPT_ASSERT(( boost_concepts::ReadableIteratorConcept<ForwardIterator> )); 
    typedef typename IteratorCirculatorTraits<ForwardIterator>::Value Point; 

	HueShadeColorMap<double> colorMap(1,size+1);
	unsigned int compteur = 1;
    ForwardIterator it = itb;

	for (ForwardIterator it = itb; it != ite; it++)
	{
		Color c = colorMap(compteur);
		drawPolygon(it->begin(),it->end(),aBoard,c);
		compteur++;
}	}
