/**
 * @file Front.hpp
 * @brief Implémentation des fonctions utiles pour faire le front pareto
 * @author Damien Morel et Maxime Mikotajewski
 */
#include <iostream>
#include <limits>
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

	if(current.ensemble.size() > 3){
		cerr << "current.ensemble.size() ?! " << current.ensemble.size() << "\n";
		Ensemble best;
		best.setPerimetreToMax();
		for(unsigned int i = 0; i < sizeHull; ++i){
			Ensemble tmp = t->removePoint(current, i);
			if(tmp.getPerimetre() < best.getPerimetre() ){
					//||(tmp.getPerimetre() == best.getPerimetre() && tmp.getRatio() > best.getRatio()) ){
				best.ensemble.clear();
				best.hull.clear();
				best = tmp;
			}
		}
		current.ensemble.clear();
		current.hull.clear();
		if(best.getPerimetre() != numeric_limits<double>::max()){
			current = best;
			lstEnsemble.push_back(current);
		}
	}

}

void Front::addPoint(){
	if(current.ensemble.size() < 
			Ensemble::points.size()){
		Ensemble tmp;
		tmp = t->addPoint(current, 7);
		current.ensemble.clear();
		current.hull.clear();
		current = tmp;
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
		cout << "- - - - - - - - - -\n" 
			<< "ratio : " << e.getRatio() << "\t"
			<< "nbPoints : " << e.ensemble.size() << "\n"
			<< e;
	}
	cout << "endFront\n";
}

void Front::getRandomHull(){
	current = t->generateRandomHull();
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


void Front::localSearch(unsigned int iter){
	t->localSearch(iter,*this);
}

void Front::localSearch_v2(unsigned int iter){
	t->localSearch_v2(iter, *this);
}
