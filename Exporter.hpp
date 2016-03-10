/**
 * @file Exporter.hpp
 * @brief Prototypes des fonctions relative à l'exportation des enveloppes convexes sous format texte
 * @author Damien Morel et Maxime Mikotajewski
 */
#ifndef __EXPORTER_HPP__
#define __EXPORTER_HPP__

#include <list>

#include "Ensemble.hpp"
#include "Front.hpp"

/**
 * @class Traitement
 * @brief Effectue tous les traitements relatifs aux enveloppes convexes
 */ 
class Exporter
{
	public:
		Exporter();
		~Exporter();
		
		void exportData(Front & f);
};
	
	
#endif // __EXPORTER_HPP__
