#ifndef __TRAITEMENT_HPP__
#define __TRAITEMENT_HPP__

#include <vector>

#include "Ensemble.hpp"

class Front;
class Traitement
{
public:
  Traitement();
  virtual ~Traitement();
  
  virtual Ensemble traiter(std::vector<unsigned int> points) = 0;
  virtual Ensemble removePoint(Ensemble & e,unsigned int pos) = 0;
  virtual Ensemble addPoint(Ensemble &e, unsigned int posAdd);
  virtual void localSearch(unsigned int iter, Front f) = 0;
  virtual Ensemble generateRandomHull();
};

#endif // __TRAITEMENT_HPP__
