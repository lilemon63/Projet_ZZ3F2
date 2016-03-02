#include <iostream>
#include <limits>
#include <cmath>
#include <algorithm>
#include <limits>
#include <iostream>


#include "Ensemble.hpp"

using namespace std;

std::vector<Point *> Ensemble::points;
std::vector<unsigned int> Ensemble::posPoints;

Ensemble::Ensemble():perimetre(0){}

Ensemble::~Ensemble(){}

Ensemble::Ensemble(const Ensemble & e){
  copy(e.ensemble.begin(), e.ensemble.end(), back_inserter(this->ensemble));
  copy(e.hull.begin(), e.hull.end(), back_inserter(this->hull));
  this->perimetre = e.perimetre;
}


Ensemble Ensemble::operator=(Ensemble e){
  if(this != &e){
    copy(e.ensemble.begin(), e.ensemble.end(), back_inserter(this->ensemble));
    copy(e.hull.begin(), e.hull.end(), back_inserter(this->hull));
    this->perimetre = e.perimetre;
  }
  return *this;
}

std::ostream & operator<<(std::ostream & o, Ensemble e){
  
  o << "Affichage de l'ensemble : \n";
  for(const unsigned int i : e.ensemble){
    
    o << *(Ensemble::points[i]) << "\n";
  }
  o << "Affichage de l'enveloppe convexe :\n";
  
  for(const unsigned int i : e.hull){
    o << *(Ensemble::points[i]) << "\n";
  }
  o << "perimètre : " << e.getPerimetre() << "\n";
  return o;
}

double Ensemble::getRatio() const {
  return ensemble.size()/(double) Ensemble::points.size() * 100;
}

void Ensemble::destroy(){
  for(Point * p : points){
    delete p;
  }
}

Point * Ensemble::getFirst(){
  Point * tmp = 0;
  if(ensemble.size() > 1){
    tmp = points[ensemble[0]];
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
  
  if(size >= 3){ // Si on a au moins trois points
    for(unsigned int i = 1; i < size; ++i){ 
      tmp += distance(points[hull[i-1]],points[hull[i]]);
    }  
    // On boucle à la fin
    tmp += distance(points[hull[size-1]],points[hull[0]]); 
  }
  perimetre = tmp;
}

void Ensemble::setPerimetreToMax(){
  perimetre = numeric_limits<double>::max();
}

void Ensemble::addPoint(Point *p){
  points.push_back(p);
  posPoints.push_back(points.size() - 1);
}


void Ensemble::getNextsPoints(unsigned int posPoint, unsigned int * p1, unsigned int * p2){
  double min1, min2;
  Point * p = Ensemble::points[posPoint];
  min1 = min2 = numeric_limits<double>::max();
  for(unsigned int pos : hull){
    Point * tmp = Ensemble::points[pos];
    double distTmp = distance(p,tmp);
    if(distTmp < min1){
      // le min1 devient le min2
      *p2 = *p1;
      min2 = min1;
      
      // le min1 est réactualisé
      *p1 = pos;
      min1 = distTmp;
      
    }
    else if (distTmp < min2){
      *p2 = pos;
      min2 = distTmp;
    }
  }
}
