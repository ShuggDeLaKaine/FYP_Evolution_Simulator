/** \file display.cpp */
#pragma once
#include "creatures/creature.h"
#include "creatures/species.h"
#include "core/generalFunctions.h"


/*	\class Display
*	\brief Class...
*/
class Display
{
public:
	void displayCreatureVariables(const std::vector<Creature> creat);				//!< will display last Creature element in a vector.
	void displaySeedPopulationPoolResult(int alive, int dead);						//!< display results of seed population post fitness tests.
	void displayFirstPopulation(const std::vector<Creature> creat);					//!< display first population after seed tests.
	void displaySurvivedPercentage(const Environment envir, int alive, int popSize);//!< display the percentage chance of survival.

	void displaySpeciesPopulationInfo(SpeciesInfo species);							//!< display species population information.
	void displayGeneStackInfo(SpeciesInfo species, std::vector<float> geneStack);	//!< display gene stack information.
	void displayGeneStackChange(SpeciesInfo species, std::vector<float> geneStackSeed, std::vector<float> geneStackCurrent);	//!< display difference value in gene stacks.

private:
	CreatureCreation cc;						//!< ref to creature creation.
	SpeciesInfo si;								//!< ref to species info.
	std::shared_ptr<GeneralFunctions> genFunc;	//!< ref to general functions.
};