#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>
#include <cmath>

#include "Graham.hpp"
#include "Ensemble.hpp"
#include "Point.hpp"

using namespace std;

Point * Graham::pivot;

void Graham::selectionPivot(Ensemble & e){
  
  pivot = e.getFirst();
  vector<Point *>::iterator ptr_pivot; //= e.getEnsemble().begin();
  // On prends le point avec l'ordonnée la plus basse.
  // Si plusieurs points on l'ordonnée la plus basse, on selectionne alors l'abscisse
  for(vector<Point*>::iterator it = e.ensemble.begin(); it != e.ensemble.end(); ++it){
    
    Point * p = *it;

    if( p->y < pivot->y || (p->y == pivot->y && p->x < pivot->x)){ // en bas à gauche
      pivot = p;
      ptr_pivot = it;
    }
    
  }

}

double Graham::produitVectoriel(Point * p1, Point * p2, Point * p3){

  //RENVOYER(p2.x - p1.x)*(p3.y - p1.y) - (p3.x - p1.x)*(p2.y - p1.y);
  //x(p2.x - p1.x)*(p3.y - p1.y) - (p2.y - p1.y)*(p3.x - p1.x)
  return (p2->x - p1->x) * (p3->y - p1->y) - (p3->x - p1->x) * (p2->y - p1->y);
}

// 1 : Tournant à gauche
// -1 : Tournant à droite
// 0 : points alignés

int Graham::getOrientation(Point *p, Point *q, Point *r){
  double prodVect = produitVectoriel(p,q,r);
  if(prodVect == 0) return 0;
  return (prodVect > 0) ? 1 : -1;
}

bool Graham::compare(Point * p1,Point * p2){
  /*
  Point * p1 = *(Point **)vp1;
  Point * p2 = *(Point **)vp2;
  */
  /*
  int orientation = getOrientation(pivot, p1, p2);
  if (orientation = 0)
    return 
  
  return false;
  */
  double result =  atan2(p1->x, p1->y) - atan2(p2->x,p2->y);
  return 
    result == 0 ? (p1->x > p2->x ? true : false ) : 
    result > 0 ? false : true;
}

/*
void showAngle(Point *p1, Point *p2, Point *p3, int o){
  
    cout << "ANGLE : " << *p1 << "/" << *p2 << "\\" << *p3
	 << " Orientation : " << o << endl;
}*/

void Graham::triPoints(Ensemble & e){
  // stack<Point *> pile;
  Ensemble ensEnv;
  //vector<Point *> env;
  vector<Point *> v;
  // Le pivot est insérré au début et à la fin
 
  // Trier les points par angle (les points d'angle égal seront triés par rapport à leur abscisse)
  v = e.ensemble;
  sort(v.begin(), v.end(), &Graham::compare);
  //v.push_back(pivot);
  
  //env = ensEnv.getEnsemble();
  
  //env.push_back(pivot);
  v.push_back(pivot);
  //env.push_back(v[0]);
  e.hull.push_back(v[0]);
  //pile.push(pivot);
  
  //pile.push(v[1]);
  //pile.push(v[]);
  
  for(unsigned int i = 1; i < v.size()-1; ++i){
    
    int s = e.hull.size();
    int o = getOrientation(e.hull[s-1], v[i], v[i+1]);
    if(o < 1){
      e.hull.push_back(v[i]);
    }
  }

  //return env;
}

Ensemble Graham::traiter(vector<Point *> points){
  Ensemble e;//, result;
  vector<Point *> v;
  
  for(Point * p : points){
    e.ensemble.push_back(p);
  }


  selectionPivot(e);
  //v = triPoints(&e);
  triPoints(e);
  /*
  for(unsigned int i = 0; i < v.size(); ++i){
    e.hull.push_back(v[i]);
    //result.addPoint(v[i]);
  }
  */
  e.calculPerimetre();
  /*
  while (!pile.empty()){
    result.addPoint(pile.top());
    pile.pop();
    }1
  */
  return e;
}
