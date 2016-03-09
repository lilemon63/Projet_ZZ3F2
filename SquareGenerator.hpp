/**
 * @file SquareGenerator.hpp
 * @brief Prototypes des fonctions relative à la création aléatoire de points dans un carré
 * @author Damien Morel et Maxime Mikotajewski
 */
#ifndef __SQUAREGENERATOR_HPP__
#define __SQUAREGENERATOR_HPP__

#include <random>

/**
 * @class SquareGenerator
 * @brief Génère des points aléatoirement dans un carré
 */ 
class SquareGenerator{
	public:
		SquareGenerator(int seed);
		~SquareGenerator();
		void generateSquare(float centerX, float centerY, int size, int nbPoints);
	private:
		std::mt19937 rand;
};

#endif
