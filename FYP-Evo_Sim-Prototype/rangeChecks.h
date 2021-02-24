/** \file rangeChecks.h*/
#pragma once
#include "fitnessFunctions.h"


class RangeChecks : public FitnessFunctions
{
public:
	bool inRangeCheck(float max, float min, float env) override;
	float multiplier(float energy, bool tolerated, bool ideal = NULL);

private:


};