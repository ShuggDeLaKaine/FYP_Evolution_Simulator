/** \file oxygenFitnessTest.h */
#pragma once
#include "fitnessFunctions.h"


/*	\class OxygenFitnessTest
*	\brief Class...
*/
class OxygenFitnessTest : public FitnessFunctions
{
public:
	bool fitnessTest(float creatRequired, float envirProvided, bool tolerated) override;		//oxygen
	float multiplier(float energy, bool tolerated) override;
	bool inRangeCheck(float max, float min, float env) override;
private:
	bool fitnessTest(float creatRequired, float envirProvided) { return false; };
	bool fitnessTest(bool ideal, bool tolerated) { return false; };
	float multiplier(float energy, bool tolerated, bool ideal) { return 0.0f; };
};