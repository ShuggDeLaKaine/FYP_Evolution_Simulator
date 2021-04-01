/**\file species.h */
#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "fitness/fitnessHeaderList.h"
#include "core/generalFunctions.h"

struct AllSpecies
{
	std::vector<SpeciesInfo> fullSpeciesList;	//!< a full list of all species.
	std::vector<SpeciesInfo> aliveSpeciesList;	//!< all alive species.
	std::vector<SpeciesInfo> extinctSpeciesList;//!< all extinct species.

	uint32_t speciesCount;						//!< running count of all species.
	uint32_t aliveSpeciesCount;					//!< count of all alive species.
	uint32_t extinctSpeciesCount;				//!< count of all now dead species.

	uint32_t const MAX_SPECIES = 10000;			//!< max number of species, used in initial creation of species list vector to reserve a portion of memory.
};

struct SpeciesInfo
{
	std::vector<Creature> speciesMembership;	//!< vector of all creatures that are members of this species.
	std::vector<float> seedGeneStack;			//!< the gene stack of the seed members of this species.
	std::vector<float> speciesGeneStack;		//!< the current averaged gene stack of all currently alive members of the species.

	uint32_t speciesID = 0;						//!< ID of species, taken from the seed population member ID, initialised to 0 as an easy to tell to see if it has been assigned, ie. 0 means it hasn't been assigned.
	uint32_t currentMembers = 0;				//!< number of current members that are alive in the species.
	uint32_t totalMembers = 0;					//!< running total of species members since species inception. 

	bool speciesAssigned = false;				//!< bool to take whether this Species has been assigned to an acutal species yet.
};

class Species
{
public:
	Species();							//!< default constructor.
	~Species() {};						//!< deconstructor.

	void createNewSpecies(SpeciesInfo species, std::vector<float> geneStack, uint32_t creatureID);			//!< create a new species, adding the relevant creatures to this species vector
	void updateSpeciesMembership();		//!< update species membership, adding new members and removing 'dead' ones.
	void checkSpeciesDivergence();		//!< check membership gene stacks against species gene stack to see if creature has diverged.

	std::vector<float> getSeedGeneStack(SpeciesInfo species);		//!< get the species initial seed population gene stack.
	std::vector<float> getSpeciesGeneStack(SpeciesInfo species);	//!< get the species current populations gene stack.
	void updateSpeciesGeneStack(std::vector<float>& geneStack);		//!< get the average of the current species population gene stack and update/set the species current gene stack.
private:
	SpeciesInfo si;						//!< reference to SpeciesInfo struct.
	AllSpecies as;						//!< reference to AllSpecies strcut.
};