/** \file energyFitnessTest.h */
#pragma once
#include "fitnessFunctions.h"


/*	\class EnergyFitnessTest
*	\brief Class...
*/
class EnergyFitnessTest : public FitnessFunctions
{
public:
	bool fitnessTest(float creatRequired, float envirProvided) override;						//enery
private:
	bool fitnessTest(bool ideal, bool tolerated) { return false; };
	bool fitnessTest(float creatRequired, float envirProvided, bool tolerated) { return false; };
	float multiplier(float energy, bool tolerated) { return 0.0f; };
	float multiplier(float energy, bool tolerated, bool ideal) { return 0.0f; };
	bool inRangeCheck(float max, float min, float env) { return false; };
};