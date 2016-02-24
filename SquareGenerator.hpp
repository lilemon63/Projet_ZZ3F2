#ifndef __SQUAREGENERATOR_HPP__
#define __SQUAREGENERATOR_HPP__

#include <random>

class SquareGenerator{
	public:
		SquareGenerator(int seed);
		~SquareGenerator();
		void generateSquare(float centerX, float centerY, int size, int nbPoints);
	private:
		std::mt19937 rand;
};

#endif
