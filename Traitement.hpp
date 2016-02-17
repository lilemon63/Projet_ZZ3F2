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
  
};

#endif // __TRAITEMENT_HPP__
