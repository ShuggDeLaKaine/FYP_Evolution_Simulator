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

	//cross over paired gene stacks into new gene stacks from offspring creatures.
	crossoverGeneStacks(pairedParents);

	//create these creatures and add to species.


	//clear up ... for next species.

}

void Crossover::getGeneStacks(std::vector<std::pair<float, std::vector<float>>> parents)
{
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
		if (parents.at(i).second != false)
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
		{
			std::cout << "WARNING - CROSSOVER - pairParents() - creature already paired up" << std::endl;
		}
	}
}

void Crossover::crossoverGeneStacks(std::vector<std::pair<std::vector<float>, std::vector<float>>> pairParents)
{
	//get a random uniform number from within the size of the geneStack vector.


	//have a temporary vector to contain the geneStack whilst it is being constructed.


	//loop through parent1 geneStack, start at the beginning to end at the random number, assigning each gene element to the new offspring geneStack.


	//loop through parent2 geneStack, start at the random number to end at the end, assigning each gene element to the new offsping geneStack.


	//ensure that each element of the newly created gene stack has a value.


}
