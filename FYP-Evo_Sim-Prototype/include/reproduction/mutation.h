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
	void mutationChance(int percentageChance);
	void mutationChance(int percentageChance, float &yesMut, float &noMut);

private:
	std::shared_ptr<GeneralFunctions> genFunc;
};