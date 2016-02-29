/**
 * @file Front.hpp
 * @brief Implémentation des fonctions utiles à faire le front pareto
 * @author Damien Morel et Maxime Mikotajewski
 */
#include <iostream>
#include "Front.hpp"

using namespace std;
Front::Front(Traitement * t):t(t){}
Front::~Front(){}

void Front::addEnsemble(Ensemble e){
  lstEnsemble.push_back(e);
}


void Front::setCurrent(Ensemble e){
  current = e ;
}

// Exploration de l'espace 
void Front::removePoint(){
  unsigned int size = current.hull.size();
  cerr << "size : " << size << "\n";
  if(size > 3){
    Ensemble best;
    best.setPerimetreToMax();
    cerr << "best setted\n";
    unsigned int i = 0;
      //for(unsigned int i = 0; i < size; ++i){
      cerr << "iteration " << i << "\n";
      Ensemble tmp = t->removePoint(current, i);
      //cerr << "point removed\n";
      if(tmp.getPerimetre() < best.getPerimetre()) 
	best = tmp;
      
      //}
    lstEnsemble.push_back(best);
    current = best;
  }
}

void Front::showFront(){
  cout << "showFront : \n";
  for(const Ensemble & e : lstEnsemble){
    cout << "nbPoints : " << e.ensemble.size() << "\n"
	 << "ratio : " << (Ensemble::points.size() / (double) e.ensemble.size()) * 100 << "\n"
	 << e;
  }
  cout << "endFront\n";
}



void Front::globalHull(){  
  
  current = t->traiter(Ensemble::posPoints);
  lstEnsemble.push_back(current);
  
}

Ensemble & Front::getCurrent(){
  return this->current;
}
