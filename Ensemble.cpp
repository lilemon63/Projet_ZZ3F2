#include <iostream>
#include <limits>
#include <cmath>
#include <algorithm>
#include <limits>
#include <iostream>


#include "Ensemble.hpp"

using namespace std;

std::vector<Point *> Ensemble::points;

Ensemble::Ensemble():perimetre(0){}

Ensemble::~Ensemble(){}

Ensemble::Ensemble(const Ensemble & e){
  copy(e.ensemble.begin(), e.ensemble.end(), back_inserter(this->ensemble));
  copy(e.hull.begin(), e.hull.end(), back_inserter(this->hull));
  this->perimetre = e.perimetre;
}

std::ostream & operator<<(std::ostream & o, Ensemble e){
  
  o << "Affichage de l'ensemble : \n";
  for(const Point * i : e.ensemble){
    o << *i << "\n";
  }
  o << "Affichage de l'enveloppe convexe :\n";
  
  for(const Point * i : e.hull){
    o << *i << "\n";
  }
  o << "perimètre : " << e.getPerimetre() << "\n";
  return o;
}

void Ensemble::destroy(){
  for(Point * p : points){
    delete p;
  }
}

Point * Ensemble::getFirst(){
  Point * tmp = 0;
  if(ensemble.size() > 1){
    tmp = ensemble[0];
  }
  return tmp;
}

double Ensemble::getPerimetre(){
  return perimetre;
}

double Ensemble::distance(Point * p1, Point * p2){
  return sqrt( (p2->x - p1->x) * (p2->x - p1->x) +
	       (p2->y - p1->y) * (p2->y - p1->y));
}

void Ensemble::calculPerimetre(){
  double tmp = 0;
  unsigned int size = hull.size();
  if(size > 3){ // Si on a au moins trois points
    for(unsigned int i = 1; i < size; ++i){ 
      tmp += distance(hull[i-1],hull[i]);
    }  
    // On boucle à la fin
    tmp += distance(hull[size-1],hull[0]); 
  }
  perimetre = tmp;
}

void Ensemble::setPerimetreToMax(){
  perimetre = numeric_limits<double>::max();
}
