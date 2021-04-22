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

void Display::displaySpeciesBirthDeathRates(SpeciesInfo species)
{
	int result = species.endCycleMembers - species.startCycleMembers;
	species.currentMembers = species.speciesMembership.size();
	std::cout << "Change: " << result;
	std::cout << ". Offspring: " << species.cycleOffspringCount;
	std::cout << ". Total Deaths: " << species.cycleTotalDeadCount;
	std::cout << ". Fitness Failed: " << species.cycleFailedFitnessDeadCount;
	std::cout << ". Old Age: " << species.cycleOldAgeDeadCount << std::endl;
}

void Display::displaySpeciesPopulationInfo(SpeciesInfo species)
{
	//do a little check to see if the counter is working as expected...
	if (species.speciesMembership.size() != species.currentMembers)
		std::cout << "WARNING... Species " << species.speciesID << " currentMembers NOT equal to .size() of vector speciesMembership";
	else
		//number of current alive members and members overall.
		//std::cout << "SPECIES " << species.speciesID << " has " << species.currentMembers << " current members. " << std::endl;
		std::cout << "SPECIES " << species.speciesID << " has " << species.speciesMembership.size() << " current members. ";
}

void Display::displayGeneStackInfo(SpeciesInfo species, std::vector<float> geneStack)
{
	//display data for the seed gene stack.
	if(geneStack == species.seedGeneStack)
		std::cout << std::endl << "SPECIES " << species.speciesID << " -- SEED Gene Stack is as follows: " << std::endl;
	else if (geneStack == species.speciesGeneStack)
		std::cout << std::endl << "SPECIES " << species.speciesID << " -- AVERAGED CURRENT Gene Stack is as follows: " << std::endl;
	std::cout << "Energy Demand: " << geneStack.at(0) << std::endl;
	std::cout << "Ideal Temperature: " << geneStack.at(1) << std::endl;
	std::cout << "Ideal Temperature Range: " << geneStack.at(2) << std::endl;
	std::cout << "Tolerated Temperature Range: " << geneStack.at(3) << std::endl;
	std::cout << "Oxygen % Demand: " << geneStack.at(4) << std::endl;
	std::cout << "Oxygen % Range: " << geneStack.at(5) << std::endl;
}

void Display::displayGeneStackChange(SpeciesInfo species, std::vector<float> geneStackSeed, std::vector<float> geneStackCurrent)
{
	std::cout << std::endl << "SPECIES " << species.speciesID << " -- DIFFERENCE in SEED to END Gene Stacks:" << std::endl;
	std::cout << "Energy Demand: " << genFunc->roundFloat(geneStackCurrent.at(0) - geneStackSeed.at(0)) << std::endl;
	std::cout << "Ideal Temperature: " << genFunc->roundFloat(geneStackCurrent.at(1) - geneStackSeed.at(1)) << std::endl;
	std::cout << "Ideal Temperature Range: " << genFunc->roundFloat(geneStackCurrent.at(2) - geneStackSeed.at(2)) << std::endl;
	std::cout << "Tolerated Temperature Range: " << genFunc->roundFloat(geneStackCurrent.at(3) - geneStackSeed.at(3)) << std::endl;
	std::cout << "Oxygen % Demand: " << genFunc->roundFloat(geneStackCurrent.at(4) - geneStackSeed.at(4)) << std::endl;
	std::cout << "Oxygen % Range: " << genFunc->roundFloat(geneStackCurrent.at(5) - geneStackSeed.at(5)) << std::endl;
}