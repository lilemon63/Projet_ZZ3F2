/**
 * @file Front.hpp
 * @brief Prototypes des fonctions utiles à faire le front pareto
 * @author Damien Morel et Maxime Mikotajewski
 */
#ifndef __FRONT_HPP__
#define __FRONT_HPP__

#include <list>

#include "Traitement.hpp"
#include "Ensemble.hpp"

class Front{
private:
  double pourcentActu;
  Traitement * t;
  Ensemble current;



public:
  std::list<Ensemble> lstEnsemble;
  Front(Traitement * t);
  ~Front();

  void addEnsemble(Ensemble e);
  void setCurrent(Ensemble e);

  void removePoint();
  void showFront();
  void globalHull();
  Ensemble & getCurrent();
  
  int getParetoSize() const;
  
  void constructionFirstPareto();
  void addPoint();
  std::vector<Point> getParetoPoints();
  void getRandomHull();
  void localSearch(unsigned int iter);
};


#endif
