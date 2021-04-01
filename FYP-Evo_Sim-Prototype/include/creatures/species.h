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
	std::vector<Creature> speciesMembers;		//!< vector of all creatures that are members of this species.
	std::vector<float> seedGeneStack;			//!< the gene stack of the seed members of this species.
	std::vector<float> speciesGeneStack;		//!< the current averaged gene stack of all currently alive members of the species.
	uint32_t speciesID;								//!< ID of species, taken from the seed population member ID.
	uint32_t currentMembers;							//!< number of current members that are alive in the species.
	uint32_t totalMembers;							//!< running total of species members since species inception. 
};

class Species
{
public:
	Species() {};						//!< default constructor.
	~Species() {};						//!< deconstructor.

	void createNewSpecies();			 //!< create a new species, adding the relevant creatures to this species vector
	void updateSpeciesMembership();		 //!< update species membership, adding new members and removing 'dead' ones.
	void checkSpeciesDivergence();		 //!< check membership gene stacks against species gene stack to see if creature has diverged.

	void getSeedGeneStack();			 //!< get the species initial seed population gene stack.
	void getSpeciesGeneStack();			 //!< get the species current populations gene stack.
	void updateSpeciesGeneStack();		 //!< get the average of the current species population gene stack and update/set the species current gene stack.
private:

};