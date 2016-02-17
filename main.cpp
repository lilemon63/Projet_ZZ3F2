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

#include "Traitement.hpp"
#include "Graham.hpp"
#include "LoaderPoint.hpp"

using namespace std;


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
}

