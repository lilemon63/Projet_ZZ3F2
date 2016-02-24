#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>
#include <cmath>
#include <list>

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

void Graham::findHull(Ensemble & e){
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
  findHull(e);
  e.calculPerimetre();
  return e;
}

int pointInPolygon(int nvert, double *vertx, double *verty, double testx, double testy)
{
  int i, j, c = 0;
  cerr << "PointInPolygon : begin\n";
  for (i = 0, j = nvert-1; i < nvert; j = i++) {
    if ( ((verty[i]>testy) != (verty[j]>testy)) &&
	 (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
      c = !c;
  }
  cerr << "PointInPolygon : end\n";
  return c;

}

Ensemble Graham::removePoint( Ensemble & e, unsigned int pos){
  Ensemble tmp = e;
  
  Point * prec, *suiv, * removed;
  unsigned int posPrec, posSuiv;
  double tabX[3], tabY[3];
  
  vector<Point *> inTriangle;
  cerr << "removePoint begin\n";
  posPrec = (pos == 0) ? e.hull.size()-1 : pos-1;
  posSuiv = (pos == e.hull.size()) ? 0 : pos+1;
  
  // On va constituer un triangle fait grace au point que l'on souhaite enlever, 
  // Le précédent et le suivant.
  prec = tmp.hull[posPrec];
  suiv = tmp.hull[posSuiv];
  removed = tmp.hull[pos];
  cerr << "indices : " << posPrec << " ; " << pos << " ; " << posSuiv << "\n";
  cerr << "init des variables : " << *prec << " ; " << *removed << ";" << *suiv << "\n";
  tabX[0] = prec->x; tabX[1] = removed->x; tabX[2] = suiv->x;
  tabY[0] = prec->y; tabY[1] = removed->y; tabY[2] = suiv->y;
  //inTriangle.push_back(prec);
  

  for(Point * p : tmp.ensemble){
    if(pointInPolygon(3, tabX,tabY, p->x, p->y)){
      inTriangle.push_back(p);
    }
  }
  //inTriangle.push_back(suiv);
  
  tmp.hull.erase(tmp.hull.begin() + pos);
  if(inTriangle.size() < 1){
    cerr << "size < 1\n";
    
  }
  else{
    cerr << "size >= 1\n";
    //vector<Point * >::const_iterator it = e.hull.begin();// + pos+1;
    auto it = e.hull.begin();
    //it += pos +1;
    e.hull.insert(it+pos, inTriangle.begin(), inTriangle.end());//, inTriangle.end());
    //insert (const_iterator position, InputIterator first, InputIterator last);le.end());
   
  }
  
  /*single element (1)	
iterator insert (iterator position, const value_type& val);
fill (2)	
    void insert (iterator position, size_type n, const value_type& val);
range (3)	
template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last);
*/
  
  // On enlève le point de l'enveloppe convexe.
  tmp.hull.erase(tmp.hull.begin() + pos);
  
  // 
  
  
  cerr << "removePoint end\n";
  return tmp;
}
