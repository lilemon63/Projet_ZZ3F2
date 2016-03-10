/**
 * @file Graham.hpp
 * @brief Prototypes des fonctions relative au traitement de Graham
 * @author Damien Morel et Maxime Mikotajewski
 */
#ifndef __GRAHAMS_HPP__
#define __GRAHAMS_HPP__

#include <stack>

#include "Traitement.hpp"
#include "Ensemble.hpp"
#include "Point.hpp"

/**
 * @class Graham
 * Traitement qui base sont algorithme sur celui de Graham
 */
class Graham : public Traitement{
	private:

		/**
		 * @brief Première étape de l'algorithme de Grahams, la selection du pivot
		 * @param e L'ensemble sur lequel on souhaite chercher le pivot
		 */
		void selectionPivot(Ensemble &e);

		/**
		 * @def pivot
		 * @brief Le pivot qui servira l'algorithme de Graham
		 */ 
		static Point * pivot;
		
		/**
		 * @def posPivot
		 * @brief La position du point "pivot"
		 */ 
		static unsigned int posPivot;

		/**
		 * @brief Calcul le produit vectoriel deux segments (p1;p2) / (p1:p3)
		 * @param p1 Le point p1
		 * @param p2 Le point p2
		 * @param p3 Le point p3
		 * @return Le produit vectoriel 
		 */ 
		double produitVectoriel(Point * p1, Point * p2, Point * p3);
		
		/**
		 * @brief Défini l'orientation d'un angle selon trois points
		 * @param p Le point p 
		 * @param q Le point q
		 * @param r Le point r
		 * @return 	<b>1</b> si tournant à gauche,
		 * 			<b>-1</b> si tournant à droite
		 * 			<b>0</b> si alignés
		 */ 
		int getOrientation(Point * p, Point *q, Point * r );

		/**
		 * @brief fonction utilisé pour le premier qsort nécessaire à l'algorithme de graham
		 * @param pos1 La position du point 1
		 * @param pos2 La position du point 2
		 * @return <b>true</b> si pos1 doit être avant pos2, <b>false</b> sinon
		 */ 
		static bool compare(unsigned int pos1,unsigned int pos2);

		/**
		 * @brief Fonction principale permettant de trouver l'enveloppe convexe liée à un ensemble e
		 * @brief e L'ensemble sur lequel on souhaite trouver l'enveloppe convexe
		 */ 
		void findHull(Ensemble & e);
		
		/**
		 * @brief Fonction permettant la reformation de l'enveloppe convexe du côté gauche suite à l'ajout d'un point sur celle-ci
		 * @param e L'ensemble sur lequel on ajoute un point
		 * @param posAdd La position du point qui est ajouté à l'ensemble e
		 * @param pos La position à gauche du point le plus proche du point posAdd
		 */ 
		void getShortcutPos1(Ensemble & e, unsigned int posAdd, unsigned int & pos);
		
		/**
		 * @brief Fonction permettant la reformation de l'enveloppe convexe du côté droit suite à l'ajout d'un point sur celle-ci
		 * @param e L'ensemble sur lequel on ajoute un point
		 * @param posAdd La position du point qui est ajouté à l'ensemble e
		 * @param pos La position à droite du point le plus proche du point posAdd
		 */ 
		void getShortcutPos2(Ensemble & e, unsigned int posAdd, unsigned int & pos);
		
		/**
		 * @brief Ajoute tous les points contenu dans le triangle (p1,p2,p3) au vecteur "ensemble" de e
		 * @brief e L'ensemble
		 * @brief p1 Le point p1
		 * @brief p2 Le point p2
		 * @brief p3 Le point p3
		 */ 
		void addAllNewPoints(Ensemble & e, unsigned int &p1, unsigned int &p2, unsigned int & p3);
	public:
		/**
		 * @brief Constructeur
		 */ 
		Graham(){};
		
		/**
		 * @brief Destructeur
		 */ 
		~Graham(){};

		/**
		 * @brief
		 * Effectue le calcule d'une enveloppe convexe en utilisant l'alorithme de Graham
		 * pour les points de l'ensemble.
		 */
		virtual Ensemble traiter(std::vector<unsigned int> points);

		/**
		 * @brief Enlève un point donnée d'un ensemble
		 * @param e L'ensemble auquel on souhaite enlever un point
		 * @param pos La position de l'ensemble que l'on souhaite retirer
		 * @return Un nouvel ensemble sans le point qui était situé à la position "pos"
		 */ 
		virtual Ensemble removePoint(Ensemble & e,unsigned int pos);

		/**
		 * @brief Ajoute un point à un ensemble
		 * @param e L'ensemble
		 * @param posAdd La position dans le vecteur Ensemble::points du point que l'on souhaite ajouter
		 * @return Un nouvel ensemble avec le nouveau point ajouté ainsi que tous les points trouvés au milieu
		 */ 
		Ensemble addPoint(Ensemble & e, unsigned int posAdd);


		/**
		 * @brief Vérifie si l'enveloppe est bien convexe. Si non, résout le problème grâce à l'orientation.
		 * @param e L'ensemble à vérifier
		 */
		 void verifierConvexiteHull(Ensemble & e);
};

#endif // __GRAHAMS_HPP__
