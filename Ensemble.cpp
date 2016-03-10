/**
 * @file Ensemble.cpp
 * @brief Corps de la classe Ensemble qui est le model des enveloppes convexes
 * @author Damien Morel et Maxime Mikotajewski
 */
#include <iostream>
#include <limits>
#include <cmath>
#include <algorithm>
#include <limits>
#include <iostream>
#include <sstream>
#include <string>


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

string Ensemble::exportTxt() const{
	stringstream sstm;
	//string exported = "";
	sstm << "# Ensemble\n";
	for(const unsigned int & i : ensemble){
		sstm << points[i]->exportTxt() + "\n";
	}
	sstm << "\n\n# Hull\n";
	for( const unsigned int &i : hull){
		sstm << points[i]->exportTxt() + "\n";
	}
	sstm << points[hull[0]]->exportTxt() + "\n";
	
	return sstm.str();
}


ostream & operator<<(std::ostream & o, Ensemble e){

	o << "Affichage de l'ensemble avec " << e.ensemble.size() << "points: \n";
	for(const unsigned int i : e.ensemble){

		o << *(Ensemble::points[i]) << "\n";
	}
	o << "Affichage de l'enveloppe convexe avec " << e.hull.size() << " points :\n";

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
	double minPos, maxPos, minNeg,maxNeg;
	unsigned int pp1, pp2;
	Point * p = Ensemble::points[posPoint];
	minPos = maxNeg = numeric_limits<double>::max();

	minNeg = maxPos = -numeric_limits<double>::max();

	*p1 = *p2 = pp1 = pp2 =  numeric_limits<unsigned int>::max();

	for(unsigned int pos : hull){
		Point * tmp = Ensemble::points[pos];
		double angleTmp = atan2(p->x,p->y) - atan2(tmp->x,tmp->y);

		// Montage compliqué pour dire qu'on cherche des angles les plus proches de zéro et si possible
		// Un positif et l'autre négatif. Sinon on prend juste les deux angles les plus éloignés
		if(angleTmp > 0){
			if(angleTmp < minPos){
				*p1 = pos;
				minPos = angleTmp;
			}
			if(angleTmp > maxPos){
				pp1 = pos;
				maxPos = angleTmp;
			}
		}
		else{
			if(angleTmp > minNeg){
				*p2 = pos;
				minNeg = angleTmp;
			}
			if(angleTmp < maxNeg){
				pp2 = pos;
				maxNeg = angleTmp;
			}
		}
	}

	if(*p1 == numeric_limits<unsigned int>::max()
			&& pp2 != numeric_limits<unsigned int>::max()){
		*p1 = pp2;
	}
	if(*p2 ==  numeric_limits<unsigned int>::max() 
			&& pp1 != numeric_limits<unsigned int>::max()){
		*p2 = pp1;
	}
}

