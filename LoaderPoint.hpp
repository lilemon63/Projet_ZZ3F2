/**
 * @file LoaderPoint.hpp
 * @brief Prototypes des fonctions relative au chargement de points à partir d'un fichier
 * @author Damien Morel et Maxime Mikotajewski
 */
#ifndef __LOADERPOINT_HPP__
#define __LOADERPOINT_HPP__

#include <string>

/**
 * @class LoaderPoint
 * Utilitaire permettant de charger des points à partir d'un fichier
 */
class LoaderPoint{
	public:
		/**
		 * @brief Constructeur
		 */ 
		LoaderPoint(){}
		
		/**
		 * @brief Destructeur
		 */ 
		~LoaderPoint(){}

		/**
		 * @brief charge un fichier "filename" en remplissant la variable statique "Ensemble::points"
		 * @param filename Le nom du fichier
		 * @return 1 s'il y a eu une erreur, 0 sinon
		 */ 
		int loadFile(std::string filename);

};

#endif // __LOADERPOINT_HPP__
