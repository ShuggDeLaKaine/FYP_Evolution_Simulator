/** \file main.cpp */

#include <iostream>
#include <vector>
#include "core/headerList.h"

//display functions for purpose of debugging.
void displayCreatureVariables(Creature creat[], int element);
void displaySeedPopulationResult(int alive, int dead);
void displayFirstPopulation(Creature creat[], int pop);
void displaySurvivedPercentage(Environment envir, int alive, int popSize);

//reference to classes.
FullFitnessTest ft;
CreatureCreation cc;
EnvironmentCreation ec;
Mutation mut;
std::shared_ptr<GeneralFunctions> genFunc;

const int MAX_POP = 10000000;
Creature seedPopulation[MAX_POP / 1000];
Creature startPopulation[MAX_POP];
Environment envir[10];


int main()
{
	genFunc.reset(new GeneralFunctions);
	genFunc->start();

	//hard-set creature variables (for constrained-random creature creation). 
	float energyCentre = 300.0f;
	float energyGauss = 100.0f;
	float idealTempCentre = 15.0f;
	float idealTempGuass = 5.0f;
	float idealTempRangeMin = 0.25f;
	float idealTempRangeMax = 2.0f;
	float tolTempRangeMin = 0.5f; 
	float tolTempRangeMax = 4.0f;
	float oxyCentre = 50.0f;
	float oxyGauss = 25.0f;
	float oxyRangeMin = 1.0f;
	float oxyRangeMax = 25.0f;

#pragma region ENVIRONMENTS
	//'BAAAAAAD' Testing Environment.
	envir[0].energyAvailable = 100.0f;
	envir[0].temperature = 6.0f;
	envir[0].oxygenationRate = 20.0f;
	envir[0].ID = 1;
#pragma endregion

	int populationSize = (sizeof(seedPopulation) / sizeof(*seedPopulation));
	int environmentSize = (sizeof(envir) / sizeof(*envir));
	int firstPopulationList = 0;
	int deadList = 0;

	//loop through creature array and create creatures with constrained random variables.
	for (int i = 0; i < populationSize; i++)
	{
		cc.creatureCreation(seedPopulation[i], energyCentre, energyGauss, idealTempCentre, idealTempGuass, idealTempRangeMin, idealTempRangeMax,
			tolTempRangeMin, tolTempRangeMax, oxyCentre, oxyGauss, oxyRangeMin, oxyRangeMax);
		seedPopulation[i].creatureNumber = i + 1;
	}

	//loop through this population and run the fitness tests against them to determine which of the seed population will survive and populate the start population.
	for (int i = 0; i < populationSize; i++)
	{
		//run the fitness tests between the creature and the environment.
		ft.creatureFitnessTests(seedPopulation[i], envir[0]);

		//if the creature has survived and is alive.
		if (seedPopulation[i].isAlive == true)
		{
			//add this creature from seedPopulation[] to startPopulation[]
			startPopulation[firstPopulationList] = seedPopulation[i];			
			firstPopulationList++;

			//print surviving creature info to console.
			displayCreatureVariables(seedPopulation, i);
		}
		else if (seedPopulation[i].isAlive == false)
			deadList++;
		else
			std::cout << "ERROR: Creature " << seedPopulation[i].creatureNumber << " has NULL value to bool isAlive" << std::endl;
	}

	//display required information about survival and populations.
	displaySeedPopulationResult(firstPopulationList, deadList);
	displaySurvivedPercentage(envir[0], firstPopulationList, populationSize);
	displayFirstPopulation(startPopulation, firstPopulationList);


	//debugging/testing stuff for mutation functions.
	int MUT_CHANCE = 3;
	float yesMutation = 0;
	float noMutation = 0;
	for (int i = 0; i < 1000; i++)
		mut.mutationChance(MUT_CHANCE, yesMutation, noMutation);

	std::cout << std::endl << "Number of YES mutated: " << yesMutation << std::endl;
	std::cout << "Number of NO mutated: "  << noMutation << std::endl;
	float mutationChance = (yesMutation / (yesMutation + noMutation)) * 100;
	std::cout << "Percentage chance of mutation is: " << mutationChance << std::endl;
}





void displayCreatureVariables(Creature creat[], int element)
{
	std::cout << "CREATURE " << creat[element].creatureNumber << std::endl;
	cc.printCreatureVariables(creat[element]);
	std::cout << std::endl << std::endl;
}

void displaySeedPopulationResult(int alive, int dead)
{
	std::cout << "Population left alive is: " << alive << std::endl;
	std::cout << "Population number dead is: " << dead << std::endl;
}

void displaySurvivedPercentage(Environment envir, int alive, int popSize)
{
	float percentageSurvived = static_cast<float>(alive) / static_cast<float>(popSize) * 100;
	percentageSurvived = genFunc->roundFloat(percentageSurvived);
	std::cout << "Survival chance in Environment " << envir.ID << " is: " << percentageSurvived << "%" << std::endl;
}

void displayFirstPopulation(Creature creat[], int pop)
{
	std::cout << std::endl << "In the surviving start population is: " << std::endl;
	for (int i = 0; i < pop; i++)
		std::cout << "CREATURE " << creat[i].creatureNumber << std::endl;
}