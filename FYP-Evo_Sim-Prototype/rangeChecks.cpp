/** \file rangeChecks.cpp */
#include "rangeChecks.h"

bool RangeChecks::inRangeCheck(float max, float min, float env)
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


/*
//function to check whether oxygen level of environment is in the tolerated range of a creature.
bool toleratedOxygenCheck(float minOxyTolerance, float idealMinOxy, float envirOxyProv)
{
	bool tolerated = false;

	float creatOxyTolMin = minOxyTolerance;
	float creatOxyIdealMin = idealMinOxy;
	float environOxyProvided = envirOxyProv;

	if (environOxyProvided >= creatOxyTolMin
		&& environOxyProvided <= creatOxyIdealMin)
		tolerated = true;

	return tolerated;
}
*/