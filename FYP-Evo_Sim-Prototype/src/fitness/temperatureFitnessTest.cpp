/** \file temperatureFitnessTest.cpp */
#include "fitness/temperatureFitnessTest.h"


bool TemperatureFitnessTest::fitnessTest(bool ideal, bool tolerated)
{
	bool result = true;
	bool inIdeal = ideal;
	bool inTolerated = tolerated;

	if (!inIdeal && !inTolerated)
		result = false;

	return result;
}

float TemperatureFitnessTest::multiplier(float energy, bool tolerated, bool ideal)
{
	float result = energy;

	if(!ideal && tolerated)
		result = result * 1.5f;

	return result;
}

bool TemperatureFitnessTest::inRangeCheck(float max, float min, float env)
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