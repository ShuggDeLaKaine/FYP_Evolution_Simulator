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

float Mutation::strengthOfMutation()
{
	float result = 0.0f;
	int randomNumber = genFunc->uniformIntBetween(1, 100);

	if (randomNumber <= 60)
	{
		//low strength mutation.
		result = 1.0f;
	}
	else if (randomNumber > 60 && randomNumber <= 90)
	{
		//medium strength
		result = 2.5f;
	}
	else if (randomNumber > 90 && randomNumber <= 100)
	{
		//high strength
		result = 5.0f;
	}
	else
	{
		std::cout << "ERROR: issue with strengthOfMutation(), randomNumber generated is out of range" << std::endl;
		result = 0.0f;
	}

	return result;
}
