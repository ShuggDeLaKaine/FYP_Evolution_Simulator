/** \file mutation.cpp */
#include "reproduction/mutation.h"


Mutation::Mutation()
{
	//grab the environmental mutation modifier value;
	float modifier = envir.mutationModifier;
	//get the local environmental modifier to the value from the one from class environment.
	setEnvironModifier(modifier);
}

Mutation::~Mutation()
{
	//***NEED TO*** kill that shared pointer to the genFuncs 

}

bool Mutation::mutationTest(float mutationChance)
{
	float fURandomNumber = genFunc->uniformFloatBetween(0.0f, 1.0f);	//float 0-1, uniform produces an even random spread within the range.
	float fMutChance = mutationChance;

	//mutation chance should be between 0-1, therefore a 5% chance should be 0.05f.
	//this checks if it has been put in as 5% and reduces to the required value range.
	if (fMutChance > 1.0f)
	{
		//std::cout << "WARNING - mutationChance in mutationTest() is above 1.0f, therefore above 100% chance" << std::endl;
		fMutChance = fMutChance * 0.01f;
	}
	//this is a precautionary test, in chance user enters 0.5f wanting a 0.5% of mutation, this will result in a 50% chance of mutation.
	else if (fMutChance <= 1.0f && fMutChance >= 0.25f)
	{
		std::cout << "WARNING - mutationChance is very high, between 25% and 100%; have you entered this correctly?" << std::endl;
	}

	if (fURandomNumber <= fMutChance)
	{
		//mutation happens
		//std::cout << "Mutation happened!!!" << std::endl;
		return true;
	}
	else
	{
		//std::cout << "No mutation for this creatures" /*<< creature id << variable*/ << "variable" << std::endl;
		return false;
	}
}

void Mutation::mutationIntensity(float mutPercent, float &eleToMut, float envirMulti)
{
	//get the value of the mutPercent of the elementToMutate so 10 intensity of element 5, gives a result of 0.5
	float mutPercentValue = (eleToMut * 0.01f) * mutPercent;

	//get a random float using a gaussian function, the element to mutate being the centre and the sigma (range) being the mutation intensity.
	float fMutElement = genFunc->normalFloatBetween(eleToMut, mutPercentValue);

	//get the difference between the original element to mutate.
	float fDiff = eleToMut - fMutElement;

	//apply environmental multipliers to the mutation element. 
	float fMultiDiff = fDiff * envirMulti;
	
	eleToMut = eleToMut + fMultiDiff;
}
