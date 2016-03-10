/**
 * @file Exporter.cpp
 * @brief Corps des fonctions relative à l'exportation des enveloppes convexes sous format texte
 * @author Damien Morel et Maxime Mikotajewski
 */
#include <list>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Exporter.hpp"
#include "Front.hpp"

using namespace std;

Exporter::Exporter(){}
Exporter::~Exporter(){}
		
void Exporter::exportData(Front & f){
	for(const Ensemble & e : f.lstEnsemble){
		stringstream sstm;
		sstm << "HullData/bestHullWith" << setfill('0') << setw(3) << e.ensemble.size() << ".dat";
		std::ofstream fichier(sstm.str());
 
		if (!fichier.fail()) {
			fichier << e.exportTxt();
			fichier.close();
		}
	}
	
	
		
	std::ofstream fichier("HullData/pareto.dat");
	
	for(Point & p : f.getParetoPoints()){
		fichier << p.exportTxt() << "\n";
	}	
	fichier.close();
}
