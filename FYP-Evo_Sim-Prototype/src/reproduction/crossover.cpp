/**\file crossover.cpp */
#include "reproduction/crossover.h"

Crossover::Crossover()
{

}

Crossover::~Crossover()
{

}

void Crossover::getGeneStacks(std::vector<std::pair<float, std::vector<float>>>& parents)
{
	//loop through and get gene stacks from to reproduce table from selection.h/cpp that'll be in the params.
	for (int i = 0; i < parents.size(); i++)
		geneStacksToPairVec.push_back(std::make_pair(parents.at(i).second, false));
}

void Crossover::pairParents(std::vector<std::pair<float, std::vector<float>>>& parents)
{
	
}

void Crossover::crossoverGeneStacks(std::vector<float> geneStack1, std::vector<float> geneStack2)
{

}
