#include <iostream>
#include "Traitement.hpp"
#include "Front.hpp"
#include "Graham.hpp"

using namespace std;

Traitement::Traitement(){}

Traitement::~Traitement(){}

void Traitement::localSearch(unsigned int iter,  Front & f){
  for(unsigned int i = 0; i < iter; ++i){
    cerr << "localSearch ------------- " << i << "\n";
    Ensemble tmp = generateRandomHull();
    testerFront(f,tmp);
    
    cerr << "1st test\n";
    // ajout point
    if(tmp.ensemble.size() != Ensemble::points.size()){
      unsigned int add;
      Point * pAdd;
      cerr << "if done\n";
      do{
	
	add = (rand() % (unsigned int)(Ensemble::points.size()));
	pAdd = Ensemble::points[add];
      }while(pointInVector(pAdd,tmp.ensemble));
      cerr << "add : " << add << " " << *pAdd << "\n";
      cerr << "tmp : " << tmp;
      Ensemble tmpAdded = addPoint(tmp, add);
      cerr << "added\n";
    
      testerFront(f,tmp);
      cerr << "2nd test\n";
      unsigned int rm;
      Point * pRm;
      do{
		rm = (rand() % (unsigned int)(Ensemble::points.size()));
		pRm = Ensemble::points[rm];
		cerr << "!pointInVector(pRm,tmp.hull) : " << !pointInVector(pRm,tmp.hull) << " point : " << rm << "  " << *pRm << "\n";
		for(unsigned int i : tmpAdded.hull) cerr << i << " " << *Ensemble::points[i] << "\t";
		cerr << "\n";
	} while (!pointInVector(pRm,tmp.hull));
	// On prend la position d
	unsigned int posInHull;
	for(posInHull = 0; tmpAdded.hull[posInHull] != rm ; ++posInHull);
      cerr << "remove : " << rm << " " << *pRm << "\n";
      Ensemble tmpRm = removePoint(tmpAdded,posInHull);
      cerr << "removed\n";
      testerFront(f,tmp);
      cerr << "3rd test\n";
    }
    
  }

}

void Traitement::testerFront(Front & f, Ensemble tmp){
	
  tmp.calculPerimetre();
  for(Ensemble e : f.lstEnsemble){
    if(e.getRatio() == tmp.getRatio()){
      if(tmp.getPerimetre() < e.getPerimetre()){
	e.hull.clear();
	e.ensemble.clear();
	e = tmp;
      }
      break;
    }
  }
}

Ensemble Traitement::generateRandomHull(){
  Ensemble e;
  unsigned int size = Ensemble::points.size();
  if(size > 3 ){
    unsigned int pos1,pos2,pos3;
    
    
    // On génère 3 nombre aléatoires différents
    pos1 = (rand() % (unsigned int)(size));
    do {
      pos2 = (rand() % (unsigned int)(size));
    }while  (pos2 == pos1);
    do{
      pos3 = (rand() % (unsigned int)(size));
    }while ( pos3 == pos2 || pos3 == pos1);
    
    e.hull.push_back(pos1); e.ensemble.push_back(pos1);
    e.hull.push_back(pos2); e.ensemble.push_back(pos2);
    e.hull.push_back(pos3); e.ensemble.push_back(pos3);
    
    
    Point * p1, * p2, * p3;
    p1 = Ensemble::points[pos1];
    p2 = Ensemble::points[pos2];
    p3 = Ensemble::points[pos3];
    
    
    double tabX[3], tabY[3];
    
    tabX[0] = p1->x; tabX[1] = p2->x; tabX[2] = p3->x;
    tabY[0] = p1->y; tabY[1] = p2->y; tabY[2] = p3->y;
    
    for(unsigned int pos : Ensemble::posPoints){
      Point * p = Ensemble::points[pos];
      if(!pointInVector(p,e.hull) &&
	 pointInPolygon(3,tabX,tabY,p->x,p->y)){
	e.ensemble.push_back(pos);
	cerr << "bla :" << pos << " added" << *p <<"\n";
      }
    }
    
  }
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

