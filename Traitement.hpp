/**
 * @file Traitement.hpp
 * @brief Prototypes des fonctions relative aux traitements
 * @author Damien Morel et Maxime Mikotajewski
 */
#ifndef __TRAITEMENT_HPP__
#define __TRAITEMENT_HPP__

#include <vector>

#include "Ensemble.hpp"
#include "Point.hpp"

class Front;

/**
 * @class Traitement
 * @brief Effectue tous les traitements relatifs aux enveloppes convexes
 */ 
class Traitement
{
	public:
		/**
		 * @brief Constructeur
		 */ 
		Traitement();
		
		/**
		 * Destructeur
		 */ 
		virtual ~Traitement();

		/**
		 * @brief
		 * Effectue le calcule d'une enveloppe convexe 
		 * pour les points de l'ensemble.
		 */
		virtual Ensemble traiter(std::vector<unsigned int> points) = 0;
		
		/**
		 * @brief Enlève un point donnée d'un ensemble
		 * @param e L'ensemble auquel on souhaite enlever un point
		 * @param pos La position de l'ensemble que l'on souhaite retirer
		 * @return Un nouvel ensemble sans le point qui était situé à la position "pos"
		 */ 
		virtual Ensemble removePoint(Ensemble & e,unsigned int pos) = 0;
		
		/**
		 * @brief Ajoute un point à un ensemble
		 * @param e L'ensemble
		 * @param posAdd La position dans le vecteur Ensemble::points du point que l'on souhaite ajouter
		 * @return Un nouvel ensemble avec le nouveau point ajouté ainsi que tous les points trouvés au milieu
		 */ 
		virtual Ensemble addPoint(Ensemble &e, unsigned int posAdd) = 0;
		
		/**
		 * @brief Effectue une recherche locale sur un front de pareto déjà formé
		 * @param iter Le nombre d'itérations souhaités
		 * @param f Le front de Pareto
		 */ 
		void localSearch(unsigned int iter, Front & f);
		
		/**
		 * @brief Effectue une recherche locale mais en utilisant seulement la suppression de point (de la même manière que l'heuristique de construction)
		 * @param iter le nombre d'itérations souhaités
		 * @param f Le front de Pareto
		 */ 
		void localSearch_v2(unsigned int iter, Front &f);
		
		/**
		 * @brief Génère une enveloppe convexe aléatoirement (avec 3 points sur l'enveloppe)
		 * @return L'enveloppe convexe généré
		 */ 
		Ensemble generateRandomHull();
		
		/**
		 * @brief Test si un ensemble donnée est assez bon qualitativement pour se retrouver sur le front de Pareto
		 * @param f Le front de pareto
		 * @param tmp L'ensemble à tester
		 */ 
		void testerFront(Front & f, Ensemble tmp);

};


/**
 * @brief Algorithme pointInPolygon permettant de savoir si un point se trouve dans un polygon donné
 * @param nvert Le nombre de points du polygon
 * @param vertx Les abscisses des différents points
 * @param verty Les ordonnées des différents points
 * @param testx L'abscisse du point à tester
 * @param testy L'ordonnée du point à tester
 * @return 1 si le point est dans le polygon, 0 sinon
 */ 
int pointInPolygon(int nvert, double *vertx, double *verty, double testx, double testy);

/**
 * @brief Test si un point se situe dans un vecteur
 * @param e Le point à tester
 * @param v Le vecteur
 * @return 1 si le point se trouve dans le vecteur, 0 sinon
 */ 
int pointInVector(const Point * e, const std::vector<unsigned int> & v);
#endif // __TRAITEMENT_HPP__
