/** \file display.cpp */
#include "core/display.h"


void Display::displayCreatureVariables(const std::vector<Creature> creat)
{
	std::cout << "CREATURE " << creat.back().creatureNumber << std::endl;
	cc.printCreatureVariables(creat.back());
	std::cout << std::endl;
}

void Display::displaySeedPopulationPoolResult(int alive, int dead)
{
	std::cout << "Population left alive is: " << alive << std::endl;
	std::cout << "Population number dead is: " << dead << std::endl;
}

void Display::displayFirstPopulation(const std::vector<Creature> creat)	
{
	std::cout << std::endl << "Creatures in the surviving start population are: " << std::endl;
	for (int i = 0; i < creat.size(); i++)
		std::cout << "CREATURE " << creat[i].creatureNumber << std::endl;
}

void Display::displaySurvivedPercentage(const Environment envir, int alive, int popSize)
{
	float percentageSurvived = static_cast<float>(alive) / static_cast<float>(popSize) * 100;
	percentageSurvived = genFunc->roundFloat(percentageSurvived);
	std::cout << "Survival chance in Environment " << envir.ID << " is: " << percentageSurvived << "%" << std::endl;
}

void Display::displaySpeciesPopulationInfo(SpeciesInfo species)
{
	//number of current alive members.
	std::cout << "SPECIES " << species.speciesID << " has " << species.currentMembers << " current members." << std::endl;
	//do a little check to see if the counter is working as expected...
	if (species.speciesMembership.size() != species.currentMembers)
		std::cout << "WARNING... Species " << species.speciesID << " currentMembers NOT equal to .size() of vector speciesMembership" << std::endl;
	//number of members overall.
	std::cout << "SPECIES " << species.speciesID << " has had " << species.totalMembers << " total members." << std::endl;
}

void Display::displayGeneStackInfo(SpeciesInfo species, std::vector<float> geneStack)
{
	//display data for the seed gene stack.
	std::cout << "SPECIES " << species.speciesID << " current gene stack is as follows: " << std::endl;
	std::cout << "Initial Energy Demand: " << geneStack.at(0) << std::endl;
	std::cout << "Ideal Temperature: " << geneStack.at(1) << std::endl;
	std::cout << "Ideal Temperature Range: " << geneStack.at(2) << std::endl;
	std::cout << "Tolerated Temperature Range: " << geneStack.at(3) << std::endl;
	std::cout << "Oxygen % Demand: " << geneStack.at(4) << std::endl;
	std::cout << "Oxygen % Range: " << geneStack.at(5) << std::endl << std::endl;
}
