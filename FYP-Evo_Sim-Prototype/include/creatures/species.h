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
	std::vector<float> seedGeneStack;
	std::vector<float> speciesGeneStack;
	int speciesID;
};

class Species
{
public:
	Species() {};					//!< default constructor.
	~Species() {};					//!< deconstructor.
	void createNewSpecies();
	void updateSpeciesMembership();
	void checkSpeciesDivergence();

	void getSeedGeneStack();
	void getSpeciesGeneStack();
	void updateSpeciesGeneStack();
private:

};