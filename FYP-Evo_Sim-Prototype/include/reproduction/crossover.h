/**\file crossover.h */
#pragma once
#include "reproduction/selection.h"


class Crossover
{
public:
	Crossover();		//!< constructor.
	~Crossover();		//!< deconstructor.

	void getGeneStacks(std::vector<std::pair<float, std::vector<float>>>& parents);			//!< get the gene stacks (will be from selection.h/cpp) and store in toPairList.
	void pairParents(std::vector<std::pair<float, std::vector<float>>>& parents);			//!< split chosen group into pair.
	void crossoverGeneStacks(std::vector<float> geneStack1, std::vector<float> geneStack2);	//!< combine gene stacks of chosen parents.

private:
	//std::vector<std::vector<float>> geneStacksToPairVec;						//!< vector to take the gene stacks that will be crossed over.
	std::vector<std::pair<std::vector<float>, bool>> geneStacksToPairVec;				//!< vector to take the gene stacks that will be crossed over.
	std::vector<std::pair<std::vector<float>, std::vector<float>>> pairedCreatures;		//!< vector of pairs, each a vector of floats, gene stack 1 and gene stack 2 from each parent.
};
