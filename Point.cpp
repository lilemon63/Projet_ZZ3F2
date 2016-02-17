/**
 * @file Point.cpp
 * @brief Corps de la structure Point (points cartésiens d'un graphe)
 * @author Damien Morel et Maxime Mikotajewski
 */
#include "Point.hpp"

Point::Point(){}

Point::~Point(){} // On ne décrémente pas le "nombre de points" pour ne pas perturber les ID

Point::Point(float x,float y):x(x),y(y){} 

Point::Point(const Point & p): x(p.x), y(p.y){}

Point Point::operator+(const Point & p){
  this->x += p.x;
  this->y += p.y;
  return *this;
}

Point Point::operator=(const Point & p){
  this->x = p.x;
  this->y = p.y;
  return *this;
}


std::ostream & operator<<(std::ostream & o, Point p){
  return o << "(" << p.x << ";" << p.y << ")";
}
