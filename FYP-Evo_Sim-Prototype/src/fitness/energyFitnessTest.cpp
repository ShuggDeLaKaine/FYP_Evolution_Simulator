/** \file energyFitnessTest.cpp */
#include "fitness/energyFitnessTest.h"

//energy
bool EnergyFitnessTest::fitnessTest(float creatRequired, float envirProvided)
{
	bool result = true;
	float demand = creatRequired;
	float provided = envirProvided;

	if (demand > provided)
		result = false;

	return result;
}