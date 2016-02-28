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
  std::list<Ensemble> lstEnsemble;
public:
  Front(Traitement * t);
  ~Front();

  void addEnsemble(Ensemble e);
  void setCurrent(Ensemble e);

  void removePoint();
  void showFront();
  void globalHull();
  Ensemble & getCurrent();
};


#endif
