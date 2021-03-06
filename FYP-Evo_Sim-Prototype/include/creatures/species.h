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
	uint32_t currentMembers;					//!< number of current members that are alive in the species.
	uint32_t cycleOffspringCount;				//!< 
	uint32_t cycleTotalDeadCount;				//!< 
	uint32_t cycleFailedFitnessDeadCount;		//!< 
	uint32_t cycleOldAgeDeadCount;				//!< 
		
	uint32_t test = 0;					

	std::vector<float> seedGeneStack;			//!< the gene stack of the seed members of this species.
	std::vector<float> speciesGeneStack;		//!< the current averaged gene stack of all currently alive members of the species.
	
	bool speciesAlive = true;					//!< bool to determine whether species still has members, initalised to true;
	
	void speciesAliveCheck() {
		if (currentMembers == 0)
			speciesAlive = false;
		else
			speciesAlive = true;
	}		//!< check whether the species has current members, so still going.

	void addValueToUIVar(uint32_t& variableToAlter, uint32_t byValue) {
		variableToAlter += variableToAlter + byValue;
	}		//!< 
};

struct AllSpecies
{
	//std::vector<SpeciesInfo> fullSpeciesVec;	//!< a full list of all species.
	std::vector<SpeciesInfo> aliveSpeciesVec;	//!< all alive species.
	std::vector<SpeciesInfo> extinctSpeciesVec;	//!< all extinct species.

	uint32_t totalSpeciesCount;					//!< running count of all species.
	uint32_t aliveSpeciesCount;					//!< count of all alive species.
	uint32_t extinctSpeciesCount;				//!< count of all now dead species.
};

class Species
{
public:
	Species();							//!< default constructor.
	~Species() {};						//!< deconstructor.

	void createNewSpecies(SpeciesInfo& species, std::vector<float>& geneStack, uint32_t creatureID);	//!< create a new species, adding the relevant creatures to this species vector
	
	void assignSpeciesToAllSpeciesVector(SpeciesInfo species, std::vector<SpeciesInfo>& speciesVector, AllSpecies& allSpecies);	//!< assign a species to the species vector.
	void addCreatureToSpecies(Creature creature, SpeciesInfo& species);		//!< add a creature to a species.
	void checkSpeciesDivergence();//****TO-DO****	//!< check membership gene stacks against species gene stack to see if creature has diverged.

	void updateSpeciesMembershipCounts(SpeciesInfo& species);		//!< update species membership, adding new members and removing 'dead' ones.

	std::vector<float> getSeedGeneStack(SpeciesInfo species);		//!< get the species initial seed population gene stack.
	std::vector<float> getSpeciesGeneStack(SpeciesInfo species);	//!< get the species current populations gene stack.
	
	void updateSpeciesGeneStack(SpeciesInfo& species);		//!< get the average of the current species population gene stack and update/set the species current gene stack.
	void updateAllSpecies(AllSpecies& allSpecies);			//!< update the species vectors with full, alive and extinct.

	int32_t setVariable(int32_t valToSetToo) { int32_t result = valToSetToo; return result; }	//!< 
private:
	void updateAllSpeciesCounts(AllSpecies& allSpecies);	//!< updates the counts of the species vectors with the size of the vectors.

	SpeciesInfo si;					//!< reference to SpeciesInfo struct.
	AllSpecies as;					//!< reference to AllSpecies strcut.
	std::shared_ptr<GeneralFunctions> genFunc;	//!< pointer ref to general functions class.	
};