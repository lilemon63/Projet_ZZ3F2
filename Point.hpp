/**
 * @file Point.hpp
 * @brief Prototypes de points cartésiens
 * @author Damien Morel et Maxime Mikotajewski
 */
#ifndef __POINT_HPP__
#define __POINT_HPP__

#include <iostream>

/**
 * @struct Point
 *
 * Structure définissant des points en coordonnées cartésiennes pour un graphe
 */
struct Point{  
	/**
	 * @def x
	 * attribut contenant l'abscisse du point
	 */
	float x;

	/**
	 * @def y
	 * attribut contenant l'ordonnée du point
	 */
	float y;

	/**
	 * @brief
	 * Constructeur par défaut
	 */
	Point();

	/**
	 * @brief
	 * Destructeur
	 */
	~Point();

	/**
	 * @brief 
	 * Constructeur avec paramètres
	 */
	Point(float x,float y);

	/**
	 * @brief 
	 * Constructeur par copie
	 */
	Point(const Point &p);

	/**
	 * Surcharge de l'opérateur +
	 */
	Point operator+(const Point & p);

	/**
	 * @brief 
	 * Surcharge de l'opérateur =
	 */
	Point operator=(const Point & p);
};

/**
 * @brief 
 * Surcharge de l'opérateur <<
 */
std::ostream & operator<<(std::ostream & o, Point p);


#endif // __POINT_HPP__
