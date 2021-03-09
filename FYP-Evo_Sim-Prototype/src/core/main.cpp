/** \file main.cpp */

#include <iostream>
#include <vector>
#include "core/headerList.h"

FullFitnessTest ft;
CreatureCreation cc;
EnvironmentCreation ec;
std::shared_ptr<GeneralFunctions> genFunc;

const int MAX_POP = 10000000;
Creature seedPopulation[MAX_POP / 1000];
Creature startPopulation[MAX_POP];
Environment envir[10];


int main()
{
	genFunc.reset(new GeneralFunctions);
	genFunc->start();

	//setting 
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

	uint32_t populationSize = (sizeof(seedPopulation) / sizeof(*seedPopulation));
	int environmentSize = (sizeof(envir) / sizeof(*envir));
	bool tempArrayInUse = false;
	int firstPopulationList = 0;
	int deadList = 0;

	//loop through creature array and create creatures with variables.
	for (int i = 0; i < populationSize; i++)
	{
		cc.creatureCreation(seedPopulation[i], energyCentre, energyGauss, idealTempCentre, idealTempGuass, idealTempRangeMin, idealTempRangeMax,
			tolTempRangeMin, tolTempRangeMax, oxyCentre, oxyGauss, oxyRangeMin, oxyRangeMax);
		seedPopulation[i].creatureNumber = i + 1;
	}

	//loop through this population and run the fitness tests against them.
	for (int i = 0; i < populationSize; i++)
	{
		ft.creatureFitnessTests(seedPopulation[i], envir[0]);

		if (seedPopulation[i].isAlive == true)
		{
			//add this creature from seedPopulation[] to startPopulation[]
			startPopulation[firstPopulationList] = seedPopulation[i];			
			firstPopulationList++;

			//print surviving creature info to console.
			std::cout << "CREATURE " << seedPopulation[i].creatureNumber << std::endl;
			cc.printCreatureVariables(seedPopulation[i]);
			std::cout << std::endl << std::endl;
		}
		else if (seedPopulation[i].isAlive == false)
			deadList++;
		else
			std::cout << "ERROR: Creature " << seedPopulation[i].creatureNumber << " has NULL value to bool isAlive" << std::endl;
	}

	std::cout << "Population left alive is: " << firstPopulationList << std::endl;
	std::cout << "Population number dead is: " << deadList << std::endl;

	float percentageSurvived = static_cast<float>(firstPopulationList) / static_cast<float>(populationSize) * 100;
	percentageSurvived = genFunc->roundFloat(percentageSurvived);
	std::cout << "Survival chance in Environment " << envir[0].ID << " is: " << percentageSurvived << "%" << std::endl;

	//print to console the creatures within the surviving list.
	uint32_t firstPopulation = firstPopulationList;
	std::cout << std::endl << "In the surviving start population is: " << std::endl;
	for (int i = 0; i < firstPopulation; i++)
	{
		std::cout << "CREATURE " << startPopulation[i].creatureNumber << std::endl;
	}
}

