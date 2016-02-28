#include "EnsembleDisplay.hpp"

#include <iostream>
#include <vector>
#include <iterator>

#include <cmath>

using namespace std;

using namespace cimg_library;
using namespace cimg;

Point EnsembleDisplay::toDisplayableCoordinates(const Point& point)
{
	Point nPoint;
	// Formules à reprendre
	nPoint.x = (point.x*((_width/2)/_xMax))+_width/2;

	nPoint.y = _height-((point.y*((_height/2))/_yMax)+_height/2);
	return nPoint;
}

	EnsembleDisplay::EnsembleDisplay(int width, int height):current(NULL),_xMax(0),_yMax(0),
								img(width+10,height+10,1,3),_height(height),_width(width)
{
}

EnsembleDisplay::~EnsembleDisplay()
{
}

void EnsembleDisplay::drawConvexHull()
{
	float* red = new float[3]; // {1.f,0.f,0.f};
	red[0]=1.f; red[1]=0.f; red[2]=0.f;
	Point p1,p2;
	for(unsigned int i=0;i<current->hull.size();++i)
	{
		p1=toDisplayableCoordinates(*(*current).hull[i%(current->hull.size())]);		
		p2=toDisplayableCoordinates(*(*current).hull[(i+1)%(current->hull.size())]);
		img.draw_line(p1.x,p1.y,p2.x,p2.y,red);
	}
	img.display();
	delete[] red;
}

void EnsembleDisplay::drawPoints()
{

	float* red = new float[3]; // {1.f,0.f,0.f};
	red[0]=1.f; red[1]=0.f; red[2]=0.f;
	Point p;
	for(unsigned int i=0;i!=(*current).ensemble.size();++i)
	{

		p=toDisplayableCoordinates(*(*current).ensemble[i]);
		img.draw_point(p.x,p.y,0,red);
		//		cout << _displayPoints(i,0) << " " << _displayPoints(i,1) << endl;
		//		img.draw_line(_displayPoints(i-1,0),_displayPoints(i-1,1),
		//		_displayPoints(i,0),_displayPoints(i,1),
		//		red);
	}
	//	img.draw_line(0,_height-10,_displayPoints(_nbPoints-1,0),_displayPoints(_nbPoints-1,1),red).display();
	img.display();
	delete [] red;	
}


void EnsembleDisplay::setCurrentSet(Ensemble& e)
{
	_xMax=0; _yMax=0;
	current=&e;
	for(vector<Point*>::iterator it = e.ensemble.begin(); it != e.ensemble.end();++it)
	{
		// Mettre en valeur absolue
		if(std::abs((*it)->x) > _xMax)
		{
			_xMax = std::abs((*it)->x);
		}
		if(std::abs((*it)->y) > _yMax)
		{
			_yMax = std::abs((*it)->y);
		}
	}
}
