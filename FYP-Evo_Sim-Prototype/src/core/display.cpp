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
		std::cout << "SPECIES " << species.speciesID << " has " << species.speciesMembership.size() << " current members. ";
}

void Display::displayGeneStackInfo(SpeciesInfo species, std::vector<float> geneStack)
{
	//display data for the seed gene stack.
	if(geneStack == species.seedGeneStack)
		std::cout << std::endl << "SPECIES " << species.speciesID << " -- SEED Gene Stack is as follows: " << std::endl;
	else if (geneStack == species.speciesGeneStack)
		std::cout << std::endl << "SPECIES " << species.speciesID << " -- AVERAGED CURRENT Gene Stack is as follows: " << std::endl;

	std::cout << "Current Members: " << species.speciesMembership.size() << std::endl;

	std::cout << "Energy Demand: " << geneStack.at(0) << std::endl;
	std::cout << "Ideal Temperature: " << geneStack.at(1) << std::endl;
	std::cout << "Ideal Temperature Range: " << geneStack.at(2) << std::endl;
	std::cout << "Tolerated Temperature Range: " << geneStack.at(3) << std::endl;
	std::cout << "Oxygen % Demand: " << geneStack.at(4) << std::endl;
	std::cout << "Oxygen % Range: " << geneStack.at(5) << std::endl;
	std::cout << "Litter Size: " << geneStack.at(6) << std::endl;
	std::cout << "Creature Weight: " << geneStack.at(7) << std::endl;
	std::cout << "Creature Size: ";

	int creatSize = static_cast<int>(geneStack.at(8));

	if (creatSize == 0)
		std::cout << "VERY SMALL" << std::endl;
	else if (creatSize == 1)
		std::cout << "SMALL" << std::endl;
	else if (creatSize == 2)
		std::cout << "MEDIUM" << std::endl;
	else if (creatSize == 3)
		std::cout << "LARGE" << std::endl;
	else if (creatSize == 4)
		std::cout << "VERY LARGE" << std::endl;
	else
		std::cout << "???" << std::endl;

	std::cout << "Life Span: " << geneStack.at(9) << std::endl;

}

void Display::displayGeneStackChange(SpeciesInfo species, std::vector<float> geneStackSeed, std::vector<float> geneStackCurrent)
{
	std::cout << std::endl << "SPECIES " << species.speciesID << " -- DIFFERENCE in SEED to END Gene Stacks:" << std::endl;

	int creatSize = static_cast<int>(geneStackCurrent.at(8));
	std::cout << "Creature Size: ";
	if (creatSize == 0)
		std::cout << "VERY SMALL" << std::endl;
	else if (creatSize == 1)
		std::cout << "SMALL" << std::endl;
	else if (creatSize == 2)
		std::cout << "MEDIUM" << std::endl;
	else if (creatSize == 3)
		std::cout << "LARGE" << std::endl;
	else if (creatSize == 4)
		std::cout << "VERY LARGE" << std::endl;
	else
		std::cout << "???" << std::endl;

	std::cout << "Energy Demand: " << genFunc->roundFloat(geneStackCurrent.at(0) - geneStackSeed.at(0)) << std::endl;
	std::cout << "Ideal Temperature: " << genFunc->roundFloat(geneStackCurrent.at(1) - geneStackSeed.at(1)) << std::endl;
	std::cout << "Ideal Temperature Range: " << genFunc->roundFloat(geneStackCurrent.at(2) - geneStackSeed.at(2)) << std::endl;
	std::cout << "Tolerated Temperature Range: " << genFunc->roundFloat(geneStackCurrent.at(3) - geneStackSeed.at(3)) << std::endl;
	std::cout << "Oxygen % Demand: " << genFunc->roundFloat(geneStackCurrent.at(4) - geneStackSeed.at(4)) << std::endl;
	std::cout << "Oxygen % Range: " << genFunc->roundFloat(geneStackCurrent.at(5) - geneStackSeed.at(5)) << std::endl;
}

void Display::cycleDisplay(uint32_t cycleNum, AllSpecies allspec, Environment envir)
{
	//
	std::cout << std::endl << "END OF CYCLE " << cycleNum + 1 << std::endl;

	//total number of species 
	std::cout << "Total Number of Alive Species: " << allspec.aliveSpeciesVec.size() << std::endl;
	std::cout << "Total Number of Extinct Species: " << allspec.extinctSpeciesVec.size() << std::endl;
	std::cout << std::endl;
	
	//total number of creatures, 
	int totalCreatures = 0;
	for (int i = 0; i < allspec.aliveSpeciesVec.size(); i++)
		totalCreatures += allspec.aliveSpeciesVec.at(i).currentMembers;

	std::cout << "Total Number of Creatures: " << totalCreatures << std::endl;

	int creatNumDiff = totalCreatures - lastCycleCreatureNumber;
	std::cout << "Total Creature Number Changed by: " << creatNumDiff << std::endl;
	lastCycleCreatureNumber = totalCreatures;
	std::cout << std::endl;


	//the current environmental status.
	std::cout << "Current Environmental Status was: ";
	if (envir.currentStatus == 0)
		std::cout << "ABUNDANCE" << std::endl;
	else if (envir.currentStatus == 1)
		std::cout << "SUSTAINABLE" << std::endl;
	else if (envir.currentStatus == 2)
		std::cout << "PRESSURED" << std::endl;
	else if (envir.currentStatus == 3)
		std::cout << "CRITICAL" << std::endl;
	else if (envir.currentStatus == 4)
		std::cout << "FAMINE" << std::endl;

	//numbers to press 
	std::cout << std::endl;
	std::cout << "Press 1 - for species information; creature numbers, births and deaths." << std::endl;
	std::cout << "Press 2 - for species gene stack information." << std::endl;
	std::cout << "Press 3 - for environment statistics, status, capacity and population weight" << std::endl;
	std::cout << "Press 4 - for extinct species details." << std::endl;
	std::cout << "Press 5 - TO CONTINUE..." << std::endl;

	int num;
	std::cin >> num;

	//do{
		if (num == 1)
		{
			for(int j = 0; j < allspec.aliveSpeciesVec.size(); j++)
			{
				displaySpeciesPopulationInfo(allspec.aliveSpeciesVec.at(j));
				std::cout << std::endl;
				std::cout << "          - ";
				displaySpeciesBirthDeathRates(allspec.aliveSpeciesVec.at(j));
				std::cout << std::endl;
			}
		}
		else if (num == 2)
		{
			for (int j = 0; j < allspec.aliveSpeciesVec.size(); j++)
				displayGeneStackInfo(allspec.aliveSpeciesVec.at(j), allspec.aliveSpeciesVec.at(j).speciesGeneStack);
		}
		else if (num == 3)
		{
			std::cout << "Environmental Statistics" << std::endl;
			std::cout << "Energy Available: " << envir.energyAvailable << "j"<< std::endl;
			std::cout << "Oxygenation: " << envir.oxygenationRate << "%" << std::endl;
			std::cout << "Temperature is: " << envir.temperature << "c" << std::endl;
			std::cout << "Capacity is: " << envir.fEnvironmentCapacity << std::endl;
			std::cout << "Combined Population Weight is in: " << envir.fPopulationWeight << std::endl;
			std::cout << "Current Environmental Status is: ";
			if (envir.currentStatus == 0)
				std::cout << "ABUNDANCE" << std::endl;
			else if (envir.currentStatus == 1)
				std::cout << "SUSTAINABLE" << std::endl;
			else if (envir.currentStatus == 2)
				std::cout << "PRESSURED" << std::endl;
			else if (envir.currentStatus == 3)
				std::cout << "CRITICAL" << std::endl;
			else if (envir.currentStatus == 4)
				std::cout << "FAMINE" << std::endl;

			std::cout << std::endl;
		}
		else if (num == 4)
		{
			if(allspec.extinctSpeciesVec.empty())
				std::cout << "Currently NO extinct species" << std::endl;
			else
			{
				for (int j = 0; j < allspec.extinctSpeciesVec.size(); j++)
				{
					displaySpeciesPopulationInfo(allspec.extinctSpeciesVec.at(j));
					displayGeneStackInfo(allspec.extinctSpeciesVec.at(j), allspec.extinctSpeciesVec.at(j).speciesGeneStack);
					std::cout << std::endl;
				}
			}
		}
		else if (num == 5)
		{
		}
		else
		{
			std::cout << "Did not press a number" << std::endl;
		}
	//} while (!std::cin.get());

	//press space bar to continue.
	std::cin.ignore();	//clear the buffer for the previously entered line.
	std::cout << "Please press ENTER to continue with next cycle..." << std::endl;
	std::cin.get();
}
