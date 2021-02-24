/** \file fitnessTests.cpp */
#include "fitnessTests.h"

//energy
bool FitnessTests::fitnessTest(float creatRequired, float envirProvided)
{
	bool result = true;
	float demand = creatRequired;
	float provided = envirProvided;

	if (demand > provided)
		result = false;

	return result;
}

//temperature
bool FitnessTests::fitnessTest(bool ideal, bool tolerated)
{
	bool result = true;
	bool inIdeal = ideal;
	bool inTolerated = tolerated;

	if (!inIdeal && !inTolerated)
		result = false;

	return result;
}

//oxygen
bool FitnessTests::fitnessTest(float creatRequired, float envirProvided, bool tolerated)
{
	bool result = true;
	float demand = creatRequired;
	float provided = envirProvided;
	bool inTolerated = tolerated;

	if (demand > provided && !inTolerated)
		result = false;

	return result;
}

bool FitnessTests::inRangeCheck(float max, float min, float env)
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


float FitnessTests::multiplier(float energy, bool tolerated, bool ideal)
{
	float result = energy;
	//check if there is a 2nd bool in the params, ideal. If so then do this...
	if (ideal != NULL)
	{
		if (!ideal && tolerated)
			result = result * 1.5f;
		return result;
	}
	else
	{
		if (tolerated)
			result = result * 1.5f;
		return result;
	}
}