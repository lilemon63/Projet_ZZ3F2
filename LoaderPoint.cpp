#include <string>
#include <fstream>

#include "LoaderPoint.hpp"
#include "Ensemble.hpp"

using namespace std;

int LoaderPoint::loadFile(std::string filename){
  int err = 0;
  //int i = 0;//, max;
  
  ifstream fichier(filename.c_str());
  
  //fichier.open(filename.c_str());
  
  //fichier >> max;
  string line;
  unsigned int posPoint = 0;
  while(!fichier.eof()){
    
    float x,y;
    fichier >> x;
    if(fichier.eof()){err = 1; break;}
    fichier >> y;
    Ensemble::addPoint(new Point(x,y));
    /*
    Ensemble::points.push_back(new Point(x,y));
    Ensemble::posPoints.push_back(posPoint++);
    */
    //cout << "x : " << x << " y : " << y << "\n";
  
  }
  
  
  fichier.close();
  return err;
}
