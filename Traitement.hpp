#ifndef __TRAITEMENT_HPP__
#define __TRAITEMENT_HPP__

#include <vector>

#include "Ensemble.hpp"
#include "Point.hpp"

class Front;
class Traitement
{
public:
  Traitement();
  virtual ~Traitement();
  
  virtual Ensemble traiter(std::vector<unsigned int> points) = 0;
  virtual Ensemble removePoint(Ensemble & e,unsigned int pos) = 0;
  virtual Ensemble addPoint(Ensemble &e, unsigned int posAdd) = 0;
  void localSearch(unsigned int iter, Front & f);
  Ensemble generateRandomHull();
  void testerFront(Front & f, Ensemble tmp);

};


int pointInPolygon(int nvert, double *vertx, double *verty, double testx, double testy);
int pointInVector(const Point * e, const std::vector<unsigned int> & v);
#endif // __TRAITEMENT_HPP__
