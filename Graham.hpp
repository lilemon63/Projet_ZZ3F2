#ifndef __GRAHAMS_HPP__
#define __GRAHAMS_HPP__

#include <stack>

#include "Traitement.hpp"
#include "Ensemble.hpp"
#include "Point.hpp"

class Graham : public Traitement{
private:
  
  /**
   * @brief
   * Première étape de l'algorithme de Grahams, la selection du pivot
   */
  void selectionPivot(Ensemble &e);

  static Point * pivot;
  static unsigned int posPivot;
  
  double produitVectoriel(Point * p1, Point * p2, Point * p3);
  int getOrientation(Point * p, Point *q, Point * r );
  
  static bool compare(unsigned int pos1,unsigned int pos2);

  void findHull(Ensemble & e);
public:
  Graham(){};
  ~Graham(){};
  
  /*
   * @brief
   * Effectue le calcule d'une enveloppe convexe en utilisant l'alorithme de Graham
   * pour les points de l'ensemble.
   */
  virtual Ensemble traiter(std::vector<unsigned int> points);

  virtual Ensemble removePoint(Ensemble & e,unsigned int pos);


};

#endif // __GRAHAMS_HPP__
