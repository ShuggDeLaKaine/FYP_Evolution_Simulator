/** \file oxygenFitnessTest.cpp */
#include "fitness/oxygenFitnessTest.h"


bool OxygenFitnessTest::fitnessTest(float creatRequired, float envirProvided, bool tolerated)
{
	bool result = true;
	float demand = creatRequired;
	float provided = envirProvided;
	bool inTolerated = tolerated;

	if (demand > provided && !inTolerated)
		result = false;

	return result;
}

float OxygenFitnessTest::multiplier(float energy, bool tolerated)
{
	float result = energy;

	if (tolerated)
		result = result * 1.5f;

	return result;
}

bool OxygenFitnessTest::inRangeCheck(float max, float min, float env)
{
	bool result = true;

	float creatMax = max;
	float creatMin = min;
	float environ = env;

	if (environ <= max
		&& environ >= min)
		result = true;
	else
		result = false;

	return result;
}