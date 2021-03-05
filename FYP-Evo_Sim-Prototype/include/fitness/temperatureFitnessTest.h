/** \file temperatureFitnessTest.h */
#pragma once
#include "fitnessFunctions.h"


/*	\class TemperatureFitnessTest
*	\brief Class...
*/
class TemperatureFitnessTest : public FitnessFunctions
{
public:
	bool fitnessTest(bool ideal, bool tolerated) override;							//temperature
	float multiplier(float energy, bool tolerated, bool ideal) override;
	bool inRangeCheck(float max, float min, float env) override;
private:
	bool fitnessTest(float creatRequired, float envirProvided) { return false; };
	bool fitnessTest(float creatRequired, float envirProvided, bool tolerated) { return false; };
	float multiplier(float energy, bool tolerated) { return 0.0f; };
	
};