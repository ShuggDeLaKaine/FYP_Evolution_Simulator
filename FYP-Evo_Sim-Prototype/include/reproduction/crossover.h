/**\file crossover.h */
#pragma once
#include <vector>
#include <iostream>
#include "core/generalFunctions.h"
#include "creatures/creature.h"


/*	\class Crossover
*	\brief Class...
*/
class Crossover
{
public:
	Crossover();		//!< constructor.
	~Crossover();		//!< deconstructor.

	std::vector<Creature> fullCrossover(std::vector<std::pair<float, std::vector<float>>> parents);		//!< full crossover of the selected creatures from a species.
	
	void getGeneStacks(std::vector<std::pair<float, std::vector<float>>> parents);		//!< get the gene stacks (will be from selection.h/cpp) and store in toPairList.
	void pairParents(std::vector<std::pair<std::vector<float>, bool>>& parents);		//!< split chosen group into pair.
	void crossoverGeneStacks(std::pair<std::vector<float>, std::vector<float>> pairParents, uint32_t geneStackSize);	//!< combine gene stacks of chosen parents.
	uint32_t getOffspringNumber(std::pair<std::vector<float>, std::vector<float>> parents);		//!< calculate number of offspring from two parents.

private:
	std::vector<std::pair<std::vector<float>, bool>> geneStacksToPairVec;				//!< vector to take the gene stacks that will be crossed over.
	std::vector<std::pair<std::vector<float>, std::vector<float>>> pairedParents;		//!< vector of pairs, each a vector of floats, gene stack 1 and gene stack 2 from each parent.
	
	std::vector<float> tempNewGeneStack;		//!< temp gene stack to contain the core gene values whilst an offspring is under construction.
	std::vector<Creature> tempNewCreatures;		//!< object of temporary Creature, used in creature creation and species assignment.
	
	std::shared_ptr<GeneralFunctions> genFunc;	//!< pointer ref to general functions class.
	CreatureCreation cc;						//!< ref to Creature Creation class.
};
