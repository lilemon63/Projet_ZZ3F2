/**
 * @file SquareGenerator.cpp
 * @brief Corps de la class SquareGenerator permettant la génération aléatoire à l'intérieur d'un carré 
 * @author Damien Morel et Maxime Mikotajewski
 */
#include "SquareGenerator.hpp"
#include "Ensemble.hpp"

SquareGenerator::SquareGenerator(int seed):rand(seed)
{
}

SquareGenerator::~SquareGenerator()
{

}

void SquareGenerator::generateSquare(float centerX, float centerY, int size, int nbPoints)
{
	double x,y;
	for (int i=0;i < nbPoints;++i)
	{
		x = ((double)rand()/(double)rand.max())* (double)size;
		y = ((double)rand()/(double)rand.max())* (double)size;
		x+=centerX-((double)size/2.0);
		y+=centerY-((double)size/2.0);
		Ensemble::addPoint(new Point(x,y));
	}
}
