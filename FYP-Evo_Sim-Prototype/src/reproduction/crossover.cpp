/**\file crossover.cpp */
#include "reproduction/crossover.h"

Crossover::Crossover()
{

}

Crossover::~Crossover()
{

}

void Crossover::fullCrossover(std::vector<std::pair<float, std::vector<float>>> parents)
{
	//get the relevant gene stacks from parents.
	getGeneStacks(parents);

	//pair these parents and their gene stacks up. 
	pairParents(geneStacksToPairVec);

	//loop through paired parents.
	for(int i = 0; i < pairedParents.size(); i++)
	{
		//cross over paired gene stacks into new gene stacks from offspring creatures.
		crossoverGeneStacks(pairedParents.at(i), pairedParents.at(i).first.size());

		//have the new gene stack in tempGeneStack, use this to create offspring creatures and add to species.
		tempCreature = cc.createCreatureFromGeneStack(tempGeneStack);

		//clear the tempGeneStack for the next creature to be made.
		tempGeneStack.clear();

		//assign this Creature to the relevant species.

	}

	


	//clear up ... for next species.

}

void Crossover::getGeneStacks(std::vector<std::pair<float, std::vector<float>>> parents)
{
	//clear out geneStacksToPairVec in prep for a new species set of geneStacks.
	geneStacksToPairVec.clear();
	//loop through and get gene stacks from to reproduce table from selection.h/cpp that'll be in the params.
	for (int i = 0; i < parents.size(); i++)
		geneStacksToPairVec.push_back(std::make_pair(parents.at(i).second, false));
}

void Crossover::pairParents(std::vector<std::pair<std::vector<float>, bool>>& parents)
{
	//NOTE - how to pair parents? 
	//iterate down through the list and match that way? 
	//or randomly select them from the list? May take too long randomly picking numbers until it gets the correct last one.
	for (int i = 0; i < parents.size(); i++)
	{
		//check that the creature hasn't already been assigned, if their second pair is false.
		if (parents.at(i).second == false)
		{
			//pair creature at i and i+1
			pairedParents.push_back(std::make_pair(parents.at(i).first, parents.at(i + 1).first));
			//set the bool to true for both of these parents, as saying that they are assigned.
			parents.at(i).second = true;
			parents.at(i + 1).second = true;
			//i++ as skipping a creature as it is assigned.
			i++;
		}
		else
			std::cout << "WARNING - CROSSOVER - pairParents() - creature already paired up" << std::endl;
	}
}

void Crossover::crossoverGeneStacks(std::pair<std::vector<float>, std::vector<float>> pairParents, uint32_t geneStackSize)
{
	//clear the temp geneStack, then reserve size.
	tempGeneStack.clear();
	tempGeneStack.reserve(geneStackSize);
	//get a random uniform number from within the size of the geneStack vector.
	int randNum = genFunc->uniformIntBetween(0, geneStackSize);
	//loop through parent1 geneStack, start at the beginning to end at the random number, assigning each gene element to the new offspring geneStack.
	for (int i = 0; i < randNum; i++)
		tempGeneStack.push_back(pairParents.first.at(i));
	//loop through parent2 geneStack, start at the random number to end at the end, assigning each gene element to the new offsping geneStack.
	for (int i = randNum; i < geneStackSize; i++)
		tempGeneStack.push_back(pairParents.second.at(i));
}
