/** \file fitnessTests.h */
#pragma once
#include "fitnessFunctions.h"


class FitnessTests : public FitnessFunctions
{
public:

	bool fitnessTest(float creatRequired, float envirProvided);						//enery
	bool fitnessTest(bool ideal, bool tolerated);									//temperature
	bool fitnessTest(float creatRequired, float envirProvided, bool tolerated);		//oxygen

	bool inRangeCheck(float max, float min, float env) override;
	float multiplier(float energy, bool tolerated, bool ideal = NULL) override;
private:

};