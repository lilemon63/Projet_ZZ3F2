/**
 * @file main.cpp
 * @brief Programme principal
 * @author Damien Morel et Maxime Mikotajewski
 */
#include <iostream>
#include <vector>
#include <string>
#include "Ensemble.hpp"
#include "Point.hpp"

#include "Front.hpp"
#include "Traitement.hpp"
#include "Graham.hpp"
#include "LoaderPoint.hpp"
#include "SquareGenerator.hpp"


using namespace std;

/*
int main(int, char **){  
  string filename = "data.txt";
  LoaderPoint loader;
  loader.loadFile(filename);
  
  Traitement * t = new Graham();
  Ensemble e;
  e = t->traiter(Ensemble::points);
  cout << e;

  
  delete t;
  Ensemble::destroy();
  return 0;
}*/


int main(int, char**){
  string filename  = "data.txt";
  LoaderPoint loader;
  // Remplit un ensemble de points en static (Il n'y a dans tous les cas qu'un seul ensemble de point par exécution du programme)
  loader.loadFile(filename);
 
  // Graham hérite de Traitement.
  Traitement *t = new Graham();


  Front f(t);
  
  cerr << "wtfman\t";
  f.globalHull();
  cerr << "\t </wtfman>";
  f.showFront();
  f.removePoint();
  f.showFront(); 
 

  Ensemble::destroy();
  return 0;
}

/*
int main(int, char**)
{
	SquareGenerator generator(12);
	generator.generateSquare(5,4,2,10);

	for(std::vector<Point*>::iterator it = Ensemble::points.begin();
			it!=Ensemble::points.end();
			++it)
	{
		cout << *(*it) << endl;
	}
}
*/
