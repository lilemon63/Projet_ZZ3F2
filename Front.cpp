
#include "Front.hpp"

Front::Front(Traitement * t):t(t){}
Front::~Front(){}

void Front::addEnsemble(Ensemble e){
  lstEnsemble.push_back(e);
}


void Front::setCurrent(Ensemble e){
  current = e ;
}

// Exploration de l'espace de manière à tout recouvrir, tout tester.
void Front::removePoint(){
  unsigned int size = current.hull.size();
  if(size > 3){
    Ensemble best;
    best.setPerimetreToMax();
    for(unsigned int i = 0; i < size; ++i){
      Ensemble tmp = t->removePoint(current, i);
      //tmp.hull.remove(tmp.hull.begin() + i);
      
      //remove tmp.hull[i]
    }
  }
}
