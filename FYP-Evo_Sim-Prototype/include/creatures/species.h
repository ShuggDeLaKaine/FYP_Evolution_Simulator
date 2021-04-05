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
	uint32_t speciesID = 0;						//!< ID of species, taken from the seed population member ID, initialised to 0 as an easy to tell to see if it has been assigned, ie. 0 means it hasn't been assigned.

	std::vector<Creature> speciesMembership;	//!< vector of all creatures that are members of this species.
	uint32_t currentMembers = 0;				//!< number of current members that are alive in the species.
	uint32_t totalMembers = 0;					//!< running total of species members since species inception. 

	std::vector<float> seedGeneStack;			//!< the gene stack of the seed members of this species.
	std::vector<float> speciesGeneStack;		//!< the current averaged gene stack of all currently alive members of the species.

	bool speciesAlive = true;					//!< bool to determine whether species still has members, initalised to true;
	
	void speciesAliveCheck() {
		if (currentMembers == 0)
			speciesAlive = false;
		else
			speciesAlive = true;
	}
};

struct AllSpecies
{
	std::vector<SpeciesInfo> fullSpeciesList;	//!< a full list of all species.
	std::vector<SpeciesInfo> aliveSpeciesList;	//!< all alive species.
	std::vector<SpeciesInfo> extinctSpeciesList;//!< all extinct species.

	uint32_t speciesCount;						//!< running count of all species.
	uint32_t aliveSpeciesCount;					//!< count of all alive species.
	uint32_t extinctSpeciesCount;				//!< count of all now dead species.

	//uint32_t const MAX_SPECIES = 10000;			//!< max number of species, used in initial creation of species list vector to reserve a portion of memory.
};

class Species
{
public:
	Species();							//!< default constructor.
	~Species() {};						//!< deconstructor.

	void createNewSpecies(SpeciesInfo& species, std::vector<float>& geneStack, uint32_t creatureID);	//!< create a new species, adding the relevant creatures to this species vector
	void assignSpeciesToAllSpeciesVector(SpeciesInfo species, std::vector<SpeciesInfo>& speciesVector, AllSpecies& allSpecies);	//!< assign a species to the species vector.
	void addCreatureToSpecies(Creature creature, SpeciesInfo& species);						//!< add a creature to a species.
	void updateSpeciesMembership(SpeciesInfo& species);		//!< update species membership, adding new members and removing 'dead' ones.
	void checkSpeciesDivergence();//****TO-DO****	//!< check membership gene stacks against species gene stack to see if creature has diverged.

	std::vector<float> getSeedGeneStack(SpeciesInfo species);		//!< get the species initial seed population gene stack.
	std::vector<float> getSpeciesGeneStack(SpeciesInfo species);	//!< get the species current populations gene stack.
	void updateSpeciesGeneStack(SpeciesInfo& species);		//!< get the average of the current species population gene stack and update/set the species current gene stack.
private:
	SpeciesInfo si;						//!< reference to SpeciesInfo struct.
	AllSpecies as;						//!< reference to AllSpecies strcut.
	std::shared_ptr<GeneralFunctions> genFunc;	//!< pointer ref to general functions class.	
};