/**
 * @file Graham.cpp
 * @brief Corps de la classe Graham ; effectues les traitements demandés en se basant sur l'algorithme de Graham 
 * @author Damien Morel et Maxime Mikotajewski
 */
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
	// On prends le point avec l'ordonnée la plus basse.
	// Si plusieurs points on l'ordonnée la plus basse, on selectionne alors l'abscisse
	for(vector<unsigned int>::iterator it = e.ensemble.begin(); it != e.ensemble.end(); ++it){

		Point * p = Ensemble::points[*it];

		if( p->y < pivot->y || (p->y == pivot->y && p->x < pivot->x)){ // en bas à gauche
			pivot = p;
			posPivot = *it;
		}
	}
}

double Graham::produitVectoriel(Point * p1, Point * p2, Point * p3){
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
	Point * p1, * p2;
	p1 = Ensemble::points[pos1];
	p2 = Ensemble::points[pos2];
	double result =  atan2(p1->x, p1->y) - atan2(p2->x,p2->y);
	return 
		result == 0 ? (p1->x > p2->x ? true : false ) : 
		result > 0 ? false : true;
}


void Graham::findHull(Ensemble & e){
	Ensemble ensEnv;
	vector<unsigned int> v;

	// Le pivot est insérré au début et à la fin
	// Trier les points par angle (les points d'angle égal seront triés par rapport à leur abscisse)
	v = e.ensemble;
	sort(v.begin(), v.end(), &Graham::compare);

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



Ensemble Graham::removePoint( Ensemble & e, unsigned int pos){

	Ensemble tmp = e;
	Point * prec, *suiv, * removed;
	unsigned int posPrec, posSuiv;

	double tabX[3], tabY[3];

	unsigned int posInEnsemble = 0;
	vector<unsigned int> inTriangle;
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
	tmp.hull.erase(tmp.hull.begin() + pos);
	if(inTriangle.size() > 0){
		if(inTriangle.size() > 2){

		}
		tmp.hull.insert(tmp.hull.begin()+pos, inTriangle.begin(), inTriangle.end());
	}

	tmp.ensemble.erase(tmp.ensemble.begin() + posInEnsemble);



	tmp.calculPerimetre();//calculerPerimetre();
	return tmp;
}

Ensemble Graham::addPoint(Ensemble & e, unsigned int posAdd){
	Ensemble ens = e;
	unsigned int pos1, pos2;
	ens.getNextsPoints(posAdd,&pos1,&pos2);



	// On met pos1 "à gauche" ou sur le futur "précédent"
	unsigned int pp1, pp2;
	for(pp1 = 0; ens.hull[pp1] != pos1; ++pp1);
	for(pp2 = 0; ens.hull[pp2] != pos2; ++pp2);
	if( (pp1 + 1)% ens.hull.size() != pp2){
		unsigned int tmp = pos2;
		pos2 = pos1; 
		pos1 = tmp;
	}


	getShortcutPos1(ens,posAdd,pp1);

	pp2 = pp1;
	pp2+1 == ens.hull.size() ? pp2 = 0:  ++pp2; 

	getShortcutPos2(ens,posAdd,pp2);

	ens.ensemble.push_back(posAdd);
	ens.hull.insert(ens.hull.begin() + pp2, posAdd);
	//addAllNewPoints(ens,posAdd,e.hull[pos1],e.hull[pos2]);
	addAllNewPoints(ens,posAdd,pos1,pos2);
	ens.calculPerimetre();
	return ens;
}

void Graham::getShortcutPos1(Ensemble & ens, unsigned int posAdd, unsigned int & pos){
	unsigned int oldpos; 
	Point * added = Ensemble::points[posAdd];
	while( oldpos != pos){
		Point * p = Ensemble::points[ens.hull[pos]];
		unsigned int before;// = pos - 1;

		oldpos = pos;

		if(pos == 0){
			before = ens.hull.size()-1;
		}
		else
		{
			before = pos -1;
		}
		Point * b = Ensemble::points[ens.hull[before]];
		if(getOrientation(added, p,b) == -1){ 
			ens.hull.erase(ens.hull.begin() + pos);
			pos == 0 ? pos = ens.hull.size()-1 : --pos;
		}
	}  
}

void Graham::getShortcutPos2(Ensemble & ens, unsigned int posAdd, unsigned int & pos){
	unsigned int oldpos = numeric_limits<unsigned int>::max(); 
	Point * added = Ensemble::points[posAdd];
	unsigned int after;
	while( oldpos != pos){
		Point * p = Ensemble::points[ens.hull[pos]];
		after = pos +1;
		oldpos = pos;
		if (after == ens.hull.size()) after = 0;
		Point * a = Ensemble::points[ens.hull[after]];

		int orientation = getOrientation(added, p,a);

		if(orientation == 1){ 
			ens.hull.erase(ens.hull.begin() + pos);
			++pos;
			if(pos  == ens.hull.size()) pos = 0;
			pos = ((pos+1)%ens.hull.size());
		}
	}  
}


void Graham::addAllNewPoints(Ensemble & e, unsigned int &p1, unsigned int &p2, unsigned int & p3){

	double tabX[3], tabY[3];
	Point * pp1 = Ensemble::points[p1];
	Point * pp2 = Ensemble::points[p2];
	Point * pp3 = Ensemble::points[p3];

	tabX[0] = pp1->x; tabX[1] = pp2->x; tabX[2] = pp3->x;
	tabY[0] = pp1->y; tabY[1] = pp2->y; tabY[2] = pp3->y;
	for(unsigned int p : Ensemble::posPoints){
		Point * pp = Ensemble::points[p];
		if(
				!pointInVector(pp,e.ensemble) &&
				pointInPolygon(3, tabX,tabY, pp->x, pp->y) ){
			e.ensemble.push_back(p);
		}
	}
}
