/**
 * @file Ensemble.hpp
 * @brief Prototypes d'un modèle de ensemble
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
  

  double distance(Point * p1, Point * p2);
public:
  static std::vector<Point *> points;
  
  Ensemble(const Ensemble & e);

  std::vector<unsigned int> ensemble;
  /**
   * @def hull
   * @brief L'ensemble des points appartenant à l'enveloppe convexe
   */
  std::vector<unsigned int> hull;
  /**
   * @brief 
   * Détruit l'ensemble des points
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
  
  void calculPerimetre();

  double getPerimetre();  
  
  void setPerimetreToMax();
  
  Point * getFirst();
  
  Ensemble operator=(Ensemble e);
};


/**
 * @brief 
 * Surcharge de l'opérateur <<
 */
std::ostream & operator<<(std::ostream & o, Ensemble p);

#endif // __ENSEMBLE_HPP__
