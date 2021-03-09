/** \file mutation.cpp */
#include "reproduction/mutation.h"


void Mutation::mutationChance(int percentageChance)
{
	int randomNumber = genFunc->uniformIntBetween(1, 100);

	if (randomNumber < percentageChance)
	{
		//mutation happens
		std::cout << "Mutation happened!!!" << std::endl;
	}
	else
	{
		std::cout << "No mutation for this creatures" /*<< creature id << variable*/ << "variable" << std::endl;
	}
}

void Mutation::mutationChance(int percentageChance, float & yesMut, float & noMut)
{
	int randomNumber = genFunc->uniformIntBetween(1, 100);

	if (randomNumber < percentageChance)
	{
		//mutation happens
		//std::cout << "Mutation happened!!!" << std::endl;
		yesMut++;
	}
	else
	{
		//std::cout << "No mutation for this creatures" /*<< creature id << variable*/ << "variable" << std::endl;
		noMut++;
	}
}
