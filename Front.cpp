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
  unsigned int sizeHull = current.hull.size() -1;
  cerr << "size : " << sizeHull << "\n";
  
  if(current.ensemble.size() > 3){
    
    Ensemble best;
    best.setPerimetreToMax();
    cerr << "best setted\n";
    for(unsigned int i = 0; i < sizeHull; ++i){
    //unsigned int i = 1;
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
      }
    current.ensemble.clear();
    current.hull.clear();
    current = best;
  }
  
}

void Front::constructionFirstPareto(){
  
  while(current.ensemble.size() > 3){
    removePoint();
    }
  /*
  for(unsigned int i = 0; i < 5; ++i) 
  removePoint();*/
  
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

int Front::getParetoSize() const{
  return lstEnsemble.size();
}

vector<Point> Front::getParetoPoints(){
  vector<Point> v;
  for(Ensemble e : lstEnsemble){
    v.push_back(Point(e.getRatio(),e.getPerimetre())); 
  }
  return v;
}
