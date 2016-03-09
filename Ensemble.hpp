/**
 * @file Ensemble.hpp
 * @brief Prototypes des fonctions relatives aux ensembles
 * @author Damien Morel et Maxime Mikotajewski
 */
#ifndef __ENSEMBLE_HPP__
#define __ENSEMBLE_HPP__

#include <vector>
#include "Point.hpp"

/**
 * @class Ensemble
 * Contient les données relatifs à plusieurs points, ainsi que plusieurs traitements
 * qui leurs seront associé (afin de calculer les enveloppes convexes)
 */
class Ensemble{
	private:

		/**
		 * @def perimetre
		 * @brief Le périmètre de l'enveloppe convexe
		 */
		double perimetre;

		/**
		 * @brief Calcule la distance entre deux points
		 * @param p1 Le premier point
		 * @param p2 Le deuxième point
		 * @return la distance entre p1 et p2
		 */
		double distance(Point * p1, Point * p2);
	public:
		/**
		 * @def points
		 * @brief le vecteur statique de l'ensemble des points existant pour un problème donné
		 */
		static std::vector<Point *> points;
		
		/**
		 * @def posPoints
		 * @brief le vecteur statique de l'ensemble des positions des points existants (corrélé avec points)
		 */ 
		static std::vector<unsigned int> posPoints;

		/**
		 * @brief constructeur de copie
		 */ 
		Ensemble(const Ensemble & e);

		/**
		 * @def ensemble
		 * @brief l'ensemble des points contenu dans l'enveloppe convexe (contient aussi les points de l'extérieur de la bordure)
		 */  
		std::vector<unsigned int> ensemble;
		
		/**
		 * @def hull
		 * @brief L'ensemble des points appartenant à l'enveloppe convexe
		 */
		std::vector<unsigned int> hull;

		/**
		 * @brief 
		 * Détruit l'ensemble des points existants physiquement (c'est à dire la variable statique point)
		 */
		static void destroy();

		/**
		 * @brief 
		 * Constructeur par défaut
		 */
		Ensemble();

		/**
		 * @brief 
		 * Destructeur
		 */
		~Ensemble();

		/**
		 * @brief
		 * Affiche l'ensemble des points du ensemble
		 */
		void afficherEnsemble();

		/**
		 * @brief Calcule le périmètre d'une enveloppe convexe, le resultat sera stoqué localement dans "perimetre"
		 */ 
		void calculPerimetre();

		/**
		 * @brief Donne le périmètre d'une enveloppe convexe calculé au préalable
		 * @return Le périmètre de l'enveloppe
		 */ 
		double getPerimetre();  

		/**
		 * @brief setter de Perimetre, initialise le périmètre à un périmètre max (utilisé pour initialisé "best" dans l'heuristique de construction)
		 */ 
		void setPerimetreToMax();

		/**
		 * @brief Donne le ratio de points dans l'enveloppe sur le nombre de points total existants
		 * @return Le ratio
		 */ 
		double getRatio() const;

		/**
		 * @brief Surcharge de l'opérateur égal
		 */ 
		Ensemble operator=(Ensemble e);
		
		/**
		 * @brief donne la position des deux points les plus proche d'un point donné
		 * @param posPoint La position du point que l'on souhaite intégrer à une enveloppe
		 * @param p1 La position d'un des deux points les plus proche
		 * @param p2 La position de l'autre point le plus proche
		 */ 
		void getNextsPoints(unsigned int posPoint, unsigned int * p1, unsigned int * p2);

		/**
		 * @brief Ajoute un point à l'ensemble statique des points en mettant à jour posPoint
		 * @param p Le point à ajouter
		 */ 
		static void addPoint(Point * p);
};


/**
 * @brief 
 * Surcharge de l'opérateur <<
 */
std::ostream & operator<<(std::ostream & o, Ensemble p);

#endif // __ENSEMBLE_HPP__
