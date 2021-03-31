/**\file species.h */
#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "fitness/fitnessHeaderList.h"
#include "core/generalFunctions.h"

struct SpeciesInfo
{
	std::vector<Creature> speciesMembers;
	int speciesID;
};

class Species
{
public:

	void createNewSpecies();
	void updateSpeciesMembership();
	void checkSpeciesDivergence();
private:

};