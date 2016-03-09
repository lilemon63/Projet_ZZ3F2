#include "CImg.h"
#include "Point.hpp"
#include "Ensemble.hpp"

#ifndef __ENSEMBLEDISPLAY_HPP__
#define __ENSEMBLEDISPLAY_HPP__

using namespace cimg_library;
using namespace cimg;


/**
 * @brief : Sert à afficher un ensemble et son enveloppe convexe en utilisant la bibliothèque CImg
 */
class EnsembleDisplay {

	public:
		EnsembleDisplay(int width, int height);
		~EnsembleDisplay();
		void addPoint(Point* point);
		void drawConvexHull();
		void drawPoints();
		void setCurrentSet(Ensemble& e);
	private:
		// Private methods
		Point toDisplayableCoordinates(const Point& point);

		// Private attributes
		Ensemble* current;

		//		int _nbPoints;
		//		int _nbPointsMax;
		float _xMax;
		float _yMax;
		//		CImg<int> _displayPoints;
		CImg<float> img;
		int _height;
		int _width;
};

#endif
