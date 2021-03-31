/** \file mutation.cpp */
#include "reproduction/mutation.h"


bool Mutation::mutationTest(int percentageChance)
{
	int randomNumber = genFunc->uniformIntBetween(1, 100);

	if (randomNumber < percentageChance)
	{
		//mutation happens

		return true;
		std::cout << "Mutation happened!!!" << std::endl;
	}
	else
	{
		std::cout << "No mutation for this creatures" /*<< creature id << variable*/ << "variable" << std::endl;
		return false;
	}
}

float Mutation::mutationIntensity()
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
