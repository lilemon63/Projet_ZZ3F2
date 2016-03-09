/**
 * @file LoaderPoint.cpp
 * @brief Corps de la class LoaderPoint 
 * @author Damien Morel et Maxime Mikotajewski
 */
#include <string>
#include <fstream>

#include "LoaderPoint.hpp"
#include "Ensemble.hpp"

using namespace std;

int LoaderPoint::loadFile(std::string filename){
	int err = 0;

	ifstream fichier(filename.c_str());

	string line;
	while(!fichier.eof()){

		float x,y;
		fichier >> x;
		if(fichier.eof()){err = 1; break;}
		fichier >> y;
		Ensemble::addPoint(new Point(x,y));

	}


	fichier.close();
	return err;
}
