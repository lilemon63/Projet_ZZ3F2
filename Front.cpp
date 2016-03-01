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
    //for(unsigned int i = 0; i < lstEnsemble.size() -1; ++i){
    unsigned int i = 0;
    //for(unsigned int i = 0; i < 2; ++i){
      cerr << "iteration " << i << "\n";
      Ensemble tmp = t->removePoint(current, i);
      //cerr << "point removed\n";
      if(tmp.getPerimetre() < best.getPerimetre() ||
	 (tmp.getPerimetre() == best.getPerimetre() && tmp.getRatio() > best.getRatio()) ){
	best.ensemble.clear();
	best.hull.clear();
	best = tmp;
      
      }
      lstEnsemble.push_back(best);
      //}
    cerr << "BEST DANS FRONT " << best << "FINBESTFRONTTOUSSA\n";
    cerr << "current before affectation " << current << "fincurrentetc\n";
    current.ensemble.clear();
    current.hull.clear();
    current = best;
    cerr << "LAST : " << current << "FINLAST\n";
  }
}

void Front::showFront(){
  cout << "showFront : \n";
  for(const Ensemble & e : lstEnsemble){
    cout << "nbPoints : " << e.ensemble.size() << "\n"
	 << "ratio : " << e.getRatio() << "\n"
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
