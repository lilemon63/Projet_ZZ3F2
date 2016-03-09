/**
 * @file ParetoDisplay.cpp
 * @brief Corps de la class ParetoDisplay permettant l'affichage graphique d'un front de Pareto 
 * @author Damien Morel et Maxime Mikotajewski
 */
#include "ParetoDisplay.hpp"

#include <iostream>

using namespace std;

using namespace cimg_library;
using namespace cimg;

Point ParetoDisplay::toDisplayableCoordinates(const Point& point)
{
	Point nPoint;
	nPoint.x = point.x*_width/100;
	double criteria = (double)point.y/(double)_criteriaMax;

	nPoint.y = (_height-(criteria*_height))+10;
	return nPoint;
}


ParetoDisplay::ParetoDisplay(int nbPoints, int width, int height):_nbPoints(0),_nbPointsMax(nbPoints),_criteriaMax(0),
	_displayPoints(nbPoints,2),img(width+10,height+10,1,3),_height(height),_width(width)
{
}

ParetoDisplay::~ParetoDisplay()
{
}


void ParetoDisplay::addPoint(Point* point)
{

	if(_nbPoints==0)
	{
		_criteriaMax=point->y;
	}
	Point displayPoint(toDisplayableCoordinates(*point));
	if(_nbPoints<= _nbPointsMax)
	{
		_displayPoints(_nbPoints,0)=displayPoint.x;
		_displayPoints(_nbPoints,1)=displayPoint.y;
		_nbPoints++;
	}

}

void ParetoDisplay::drawParetoFront()
{

	//	const unsigned char color[] = { 255,128,64 };
	float* red = new float[3]; // {1.f,0.f,0.f};
	red[0]=1.f; red[1]=0.f; red[2]=0.f;
	for(int i=1;i!=_nbPoints;++i)
	{
		cout << _displayPoints(i,0) << " " << _displayPoints(i,1) << endl;
		img.draw_line(_displayPoints(i-1,0),_displayPoints(i-1,1),
				_displayPoints(i,0),_displayPoints(i,1),
				red);
	}
	img.draw_line(0,_height-10,_displayPoints(_nbPoints-1,0),_displayPoints(_nbPoints-1,1),red).display();
	delete [] red;	
}
