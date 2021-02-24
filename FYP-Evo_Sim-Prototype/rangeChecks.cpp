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


float RangeChecks::multiplier(float energy, bool tolerated, bool ideal)
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

