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
unsigned int Graham::posPivot;

void Graham::selectionPivot(Ensemble & e){
  
  pivot = e.getFirst();
  //vector<Point *>::iterator ptr_pivot; //= e.getEnsemble().begin();
  // On prends le point avec l'ordonnée la plus basse.
  // Si plusieurs points on l'ordonnée la plus basse, on selectionne alors l'abscisse
  for(vector<unsigned int>::iterator it = e.ensemble.begin(); it != e.ensemble.end(); ++it){
    
    Point * p = Ensemble::points[*it];
    
    if( p->y < pivot->y || (p->y == pivot->y && p->x < pivot->x)){ // en bas à gauche
      pivot = p;
      posPivot = *it;
      // ptr_pivot = it;
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

bool Graham::compare(unsigned int pos1,unsigned int pos2){
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
  
  Point * p1, * p2;
  p1 = Ensemble::points[pos1];
  p2 = Ensemble::points[pos2];
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
  vector<unsigned int> v;
  // Le pivot est insérré au début et à la fin
 
  // Trier les points par angle (les points d'angle égal seront triés par rapport à leur abscisse)
  v = e.ensemble;
  sort(v.begin(), v.end(), &Graham::compare);
  //v.push_back(pivot);
  
  //env = ensEnv.getEnsemble();
  
  v.push_back(posPivot);
  e.hull.push_back(v[0]);

  for(unsigned int i = 1; i < v.size()-1; ++i){
    
    int s = e.hull.size();
    int o = getOrientation(
			   Ensemble::points[e.hull[s-1]], 
			   Ensemble::points[v[i]], 
			   Ensemble::points[v[i+1]]);
    if(o < 1){
      e.hull.push_back(v[i]);
    }
  }

}

Ensemble Graham::traiter(vector<unsigned int> points){
  Ensemble e;//, result;
  vector<unsigned int> v;
  
  for(unsigned int p : points){
    e.ensemble.push_back(p);
  }


  selectionPivot(e);

  findHull(e);
  e.calculPerimetre();
  return e;
}

int pointInVector(const Point * e ,const vector<unsigned int>  & v) {
  int res = 0;
  
  for(unsigned int i : v){
    Point * p = Ensemble::points[i];
    
    if(p == e){
      res = 1;
    }
  }
  
  return res;
}

int pointInPolygon(int nvert, double *vertx, double *verty, double testx, double testy) 
{
  int i, j, c = 0;
  for (i = 0, j = nvert-1; i < nvert; j = i++) {
    if ((((verty[i] <= testy) && (testy < verty[j])) ||
	 ((verty[j] <= testy) && (testy < verty[i]))) &&
	(testx < (vertx[j] - vertx[i]) * (testy - verty[i]) / (verty[j] - verty[i]) + vertx[i]))
      c = !c;
  }
  return c;
}



Ensemble Graham::removePoint( Ensemble & e, unsigned int pos){
  
  Ensemble tmp = e;
  Point * prec, *suiv, * removed;
  unsigned int posPrec, posSuiv;
  
  double tabX[3], tabY[3];
  
  unsigned int posInEnsemble = 0;
  vector<unsigned int> inTriangle;
  
  cerr << "removePoint begin\n";
  
  posPrec = (pos == 0) ? e.hull.size()-1 : pos-1;
  posSuiv = (pos == e.hull.size()) ? 0 : pos+1;
  
  int posReached = 0;
  for(vector<unsigned int>::iterator it = e.ensemble.begin(); it != e.ensemble.end(); ++it){
    
    if( (*it) == tmp.hull[pos]){ 
      posReached = 1; 
    }
    if(!posReached){
      ++posInEnsemble;
    }
  }

  // On va constituer un triangle fait grace au point que l'on souhaite enlever, 
  // Le précédent et le suivant.
  prec = Ensemble::points[tmp.hull[posPrec]];//tmp.hull[posPrec];
  suiv = Ensemble::points[tmp.hull[posSuiv]];//tmp.hull[posSuiv];
  
  removed = Ensemble::points[tmp.hull[pos]];
  tabX[0] = prec->x; tabX[1] = removed->x; tabX[2] = suiv->x;
  tabY[0] = prec->y; tabY[1] = removed->y; tabY[2] = suiv->y;
  //inTriangle.push_back(prec);
  
  
  for(unsigned int pos : tmp.ensemble){
    Point * p = Ensemble::points[pos];
    
    if(!pointInVector(p,inTriangle) &&
       !pointInVector(p,e.hull) &&
       pointInPolygon(3, tabX,tabY, p->x, p->y) ){
      inTriangle.push_back(pos);
    }
  }
  //inTriangle.push_back(suiv);
  //tmp.ensemble.erase(tmp.hull.begin() + pos);
  
  //cerr << "";
  /*
  for(Point * p : inTriangle){
    cerr << *p << "&";
    }*/

  tmp.hull.erase(tmp.hull.begin() + pos);
  if(inTriangle.size() < 1){
    //cerr << "size < 1\n";
  }
  else{
    // cerr << "size >= 1\n";
    //auto it = tmp.hull.begin();
    
    tmp.hull.insert(tmp.hull.begin()+pos, inTriangle.begin(), inTriangle.end());//, inTriangle.end());
  }
  

  //tmp.hull.erase(tmp.hull.begin() + pos);
  // cerr << "graham remove after erase : " << tmp <<"\n";
  
  /*
  cerr << "poInEnsemble :" << posInEnsemble << "\n";
  cerr << "point supprimé : " << Ensemble::points[* (tmp.ensemble.begin() + posInEnsemble)] << "oupa\n";
  */
  tmp.ensemble.erase(tmp.ensemble.begin() + posInEnsemble);
  
  tmp.calculPerimetre();//calculerPerimetre();
  return tmp;
}

Ensemble Graham::addPoint(Ensemble & e, unsigned int posAdd){
  cerr << "addPoint : begin()\n";
  Ensemble ens = e;
  unsigned int pos1, pos2;
  ens.getNextsPoints(posAdd,&pos1,&pos2);
  
  // On met pos1 "à gauche" ou sur le futur "précédent"
 
  //cerr << "after inversion : " << pos1 << " ; " << pos2 << "\n";
  /*
  if( ens.hull[pos1 + 1] != pos2 ){
    unsigned int tmp = pos2;
    pos2 = pos1; 
    pos1 = tmp;
    
    cerr << "test Inversion !\n";
    }
  */
  cerr << "test";  
  cerr << " pos1 : " <<* Ensemble::points[pos1] ;
  cerr << " pos2 : " <<* Ensemble::points[pos2] << "\n";
  cerr << "after inversion : " << pos1 << " ; " << pos2 << "\n";
  /*
  cerr << "posAdd : " << *Ensemble::points[posAdd] ;
  cerr << " pos1 : " <<* Ensemble::points[ens.hull[pos1]] ;
  cerr << " pos2 : " <<* Ensemble::points[ens.hull[pos2]] << "\n";
  */
  cerr << "foreach";
  unsigned int i;
  for(i = 0; i < ens.hull.size() ; ++i){
    cerr << ens.hull[i] << " ";
  }
  cerr << "\n";
  for(i = 0; ens.hull[i] != pos1; ++i);
  cerr << "i = " << i << "\n";
  cerr << "push";
  ens.ensemble.push_back(posAdd);
  ens.hull.insert(ens.hull.begin() + i+1, posAdd);
  cerr << "foreach";
  for(unsigned int u : ens.hull){
    cerr << " " << u ;
  }
  cerr <<"\n";
  //cerr << "ENS : " << ens;
  /* A faire dans une fonction à coté*/
  unsigned int oldpos = -1;
  
  
  Point * added = Ensemble::points[posAdd];
  /*
  unsigned int pos = pos1;
  // Tant que l'on a pas fini de trouver des tournants à droite
  while( oldpos != pos){
    Point * p = Ensemble::points[ens.hull[pos1]];
    unsigned int before = pos - 1;
    oldpos = pos;
    // On initialise le "before" la position avant. si before < 0 alors on est à la fin
    if (before < 0) before = e.hull.size()-1;
    Point * b = Ensemble::points[e.hull[before]];
    

    if(getOrientation(added, p,b) == -1){ // Si on fait un tournant à droite ici, cela signifie que l'enveloppe doit enlever un de ses points
      ens.hull.erase(ens.hull.begin() + before);
      if(pos != 0) --pos;
    }
  }  
  */
  return ens;
}


