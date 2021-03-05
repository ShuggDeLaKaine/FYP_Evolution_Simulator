/** \file fitnessFunctions.h*/
#pragma once
#include <stdint.h>


/*	\class FitnessFunctions
*	\brief Class...
*/
class FitnessFunctions
{
public:
	virtual bool fitnessTest(float creatRequired, float envirProvided) = 0;						//enery
	virtual bool fitnessTest(bool ideal, bool tolerated) = 0;									//temperature
	virtual bool fitnessTest(float creatRequired, float envirProvided, bool tolerated) = 0;		//oxygen

	virtual bool inRangeCheck(float max, float min, float env) = 0;

	virtual float multiplier(float energy, bool tolerated) = 0;
	virtual float multiplier(float energy, bool tolerated, bool ideal) = 0;
};