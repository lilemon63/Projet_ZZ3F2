/**
 * @file ParetoDisplay.hpp
 * @brief Prototypes des fonctions relative à l'affichage graphique du front de pareto
 * @author Damien Morel et Maxime Mikotajewski
 */
#include "CImg.h"
#include "Point.hpp"

#ifndef __PARETODISPLAY_HPP__
#define __PARETODISPLAY_HPP__

using namespace cimg_library;
using namespace cimg;


/**
 * @class ParetoDisplay
 * @brief : Sert à afficher le front de Pareto en utilisant la bibliothèque CImg
 * 		Les points doivent donc avoir une coordonnée x comprise entre 0 et 100 (Le pourcentage de points inclus dans l'enveloppe convexe), alors que la y doit être entre 0 et la valeur max du critère. Cela sous-entend que le premier point que l'on doit passer à la méthode addPoint est celui qui sera tout en haut du Front de Pareto.
 */
class ParetoDisplay {

	public:
		ParetoDisplay(int nbPoints, int width, int height);
		~ParetoDisplay();
		void addPoint(Point* point);
		void drawParetoFront();
	private:
		// Private methods
		Point toDisplayableCoordinates(const Point& point);

		// Private attributes
		int _nbPoints;
		int _nbPointsMax;
		float _criteriaMax;
		CImg<int> _displayPoints;
		CImg<float> img;
		int _height;
		int _width;
};

#endif
