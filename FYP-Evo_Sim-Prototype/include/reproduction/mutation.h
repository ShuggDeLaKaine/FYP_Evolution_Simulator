/** \file mutation.h */
#pragma once
#include <iostream>
#include "core/generalFunctions.h"


/*	\class Mutation
*	\brief Class...
*/
class Mutation
{
public:
	bool mutationTest(int percentageChance);
	float mutationIntensity();			//!< function to result strength of mutation...

private:
	std::shared_ptr<GeneralFunctions> genFunc;
};