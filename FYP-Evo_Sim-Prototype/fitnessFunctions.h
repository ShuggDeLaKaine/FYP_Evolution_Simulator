/** \file fitnessFunctions.h*/
#pragma once

#include <stdint.h>


/*	\class FitnessFunctions
*	\brief Class...
*/
class FitnessFunctions
{
public:
	//virtual bool fitnessTest(float creature, float environment) = 0;
	//virtual bool fitnessTest(float required, float available, bool tolerated) = 0;
	//virtual bool fitnessTest(bool ideal, bool tolerated) = 0;
	
	virtual bool inRangeCheck(float max, float min, float env) = 0;

	virtual float multiplier(float energy, bool tolerated, bool ideal = NULL) = 0;
};


//int toleratedTempEnergyMultiplier(float creEnergy, bool ideal, bool tolerated)
//int toleratedOxygenEnergyMultiplier(float creEnergy, bool oxygenTolerated)