#ifndef __TRAITEMENT_HPP__
#define __TRAITEMENT_HPP__

#include <vector>

#include "Ensemble.hpp"

class Traitement
{
public:
  Traitement();
  virtual ~Traitement();
  
  virtual Ensemble traiter(std::vector<Point *> points) = 0;
  virtual Ensemble removePoint(Ensemble & e,unsigned int pos) = 0;
  
};

#endif // __TRAITEMENT_HPP__
