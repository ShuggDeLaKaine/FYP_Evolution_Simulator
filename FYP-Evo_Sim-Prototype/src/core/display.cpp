/** \file display.cpp */
#include "core/display.h"

void Display::displayCreatureVariables(Creature creat[], int element)
{
	std::cout << "CREATURE " << creat[element].creatureNumber << std::endl;
	cc.printCreatureVariables(creat[element]);
	std::cout << std::endl;
}

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

void Display::displayFirstPopulation(const Creature creat[], int pop)
{
	std::cout << std::endl << "Creatures in the surviving start population are: " << std::endl;
	for (int i = 0; i < pop; i++)
		std::cout << "CREATURE " << creat[i].creatureNumber << std::endl;
}

void Display::displayFirstPopulation(const std::vector<Creature> creat)			//not & as just reading values, not changing anything.
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
