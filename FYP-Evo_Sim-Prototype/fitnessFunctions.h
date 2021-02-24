/** \file fitnessFunctions.h*/
#pragma once

#include <stdint.h>


/*	\class FitnessFunctions
*	\brief Class...
*/
class FitnessFunctions
{
public:
	virtual bool inRangeCheck(float max, float min, float env) = 0;
	virtual float multiplier(float energy, bool tolerated, bool ideal = NULL) = 0;
};