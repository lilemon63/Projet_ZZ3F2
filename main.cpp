/**
 * @file main.cpp
 * @brief Programme principal
 * @author Damien Morel et Maxime Mikotajewski
 */
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Ensemble.hpp"
#include "Point.hpp"

#include "Front.hpp"
#include "Traitement.hpp"
#include "Graham.hpp"
#include "LoaderPoint.hpp"
#include "SquareGenerator.hpp"
#include "ParetoDisplay.hpp"
#include "EnsembleDisplay.hpp"

using namespace std;

int main(int, char**){
  string filename  = "data.txt";
  LoaderPoint loader;
  // Remplit un ensemble de points en static (Il n'y a dans tous les cas qu'un seul ensemble de point par exécution du programme)
  loader.loadFile(filename);
 
  // Graham hérite de Traitement.
  Traitement *t = new Graham();

  
  EnsembleDisplay dis(1600,900);
  //EnsembleDisplay  dis2(1600,900);
  
  Front f(t);
  
  std::srand(std::time(0));
  cerr << "main\n";
  //f.globalHull();
  f.getRandomHull();
  //f.showFront();
  //dis.setCurrentSet(f.getCurrent());
  
  //dis.drawPoints();
  //dis.drawConvexHull();
  
  //std::srand(std::time(0));
  //f.removePoint();
  //f.removePoint();
  //f.constructionFirstPareto();
  
  //f.showFront();
  //f.addPoint();
  //f.removePoint();
  dis.setCurrentSet(f.getCurrent());
  dis.drawPoints();
  dis.drawConvexHull();
  
  /*

  ParetoDisplay p(f.getParetoSize(), 1600,900);
  
  vector<Point> v = f.getParetoPoints();
  
  for(Point point : v){
    p.addPoint(&point);
  }
  
  p.drawParetoFront();
*/
  /*
  p.addPoint();
  p.addPoint();
  p.addPoint();
  */
  //cerr << "current à la fin : "<<    f.getCurrent() << "voilà\n";
  //dis.setCurrentSet(f.getCurrent());
  
  //dis.drawConvexHull();
  
  delete t;
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
