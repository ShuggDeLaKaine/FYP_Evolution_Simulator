/**\file crossover.cpp */
#include "reproduction/crossover.h"

Crossover::Crossover()
{

}

Crossover::~Crossover()
{

}

std::vector<Creature> Crossover::fullCrossover(std::vector<std::pair<float, std::vector<float>>> parents)
{
	//clear the temporary gene stack ready for use.
	tempGeneStack.clear();

	//get the relevant gene stacks from parents.
	getGeneStacks(parents);

	//pair these parents and their gene stacks up. 
	pairParents(geneStacksToPairVec);

	//loop through paired parents.
	for(int i = 0; i < pairedParents.size(); i++)
	{
		//cross over paired gene stacks into new gene stacks from offspring creatures.
		crossoverGeneStacks(pairedParents.at(i), pairedParents.at(i).first.size());

		getOffspringNumber(pairedParents.at(i));

		//loop through and repeat creature creation stage for the number of litter size of the pair of parents.
		for (int j = 0; j < 2; j++)
		{
			//have the new gene stack in tempGeneStack, use this to create offspring creatures and add to species.
			tempCreatures.push_back(cc.createCreatureFromGeneStack(tempGeneStack));
		}
	}

	//return the creature.
	return tempCreatures;
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
	std::rand();
	//int randNum = genFunc->uniformIntBetween(0, geneStackSize);
	int randNum = std::rand() % geneStackSize; 
	//loop through parent1 geneStack, start at the beginning to end at the random number, assigning each gene element to the new offspring geneStack.
	for (int i = 0; i < randNum; i++)
		tempGeneStack.push_back(pairParents.first.at(i));
	//loop through parent2 geneStack, start at the random number to end at the end, assigning each gene element to the new offsping geneStack.
	for (int i = randNum; i < geneStackSize; i++)
		tempGeneStack.push_back(pairParents.second.at(i));
}

uint32_t Crossover::getOffspringNumber(std::pair<std::vector<float>, std::vector<float>> parents)
{
	//initial local vars.
	uint32_t randNum = genFunc->uniformIntBetween(1, 100);
	uint32_t result = 0;
	uint32_t percent = 0.0f;
	float temp = 0.0f;

	//get the offspring litter size gene from parents genestacks, at element six as location of offspring litter size gene.
	float parent1 = parents.first.at(6);
	float parent2 = parents.second.at(6);

	//get average result between parents and cast to an uint32_t
	temp = (parent1 + parent2) * 0.5f;
	result = static_cast<uint32_t>(temp);
	
	//always gets round down, so get the .f left over from the round down and use that as a % to see if the litter size increases by 1.
	//if temp is more than result, ie result as been rounded down.
	if (temp > static_cast<float>(result))
	{
		//then get the .f value above the result.
		temp = temp - static_cast<float>(result);
		//now make percent an actual %, * 100.
		percent = static_cast<uint32_t>(temp * 100.0f);
		//check if this randNum is less an or equal to percent, if so then add 1 to the litter size.
		if (randNum <= percent)
			result += 1;
	}

	//return the result.
	return result;
}
