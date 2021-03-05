/** \file main.cpp */

#include <iostream>
#include <vector>
#include "core/headerList.h"

FullFitnessTest ft;
CreatureCreation cc;
EnvironmentCreation ec;
std::shared_ptr<GeneralFunctions> genFunc;


int main()
{
	Environment envir[10];
	Creature creat[10000];

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

	uint32_t populationSize = (sizeof(creat) / sizeof(*creat));
	int environmentSize = (sizeof(envir) / sizeof(*envir));
	int aliveList = 0;
	int deadList = 0;

	//loop through creature array and create creatures with variables.
	for (int i = 0; i < populationSize; i++)
	{
		cc.creatureCreation(creat[i], energyCentre, energyGauss, idealTempCentre, idealTempGuass, idealTempRangeMin, idealTempRangeMax,
			tolTempRangeMin, tolTempRangeMax, oxyCentre, oxyGauss, oxyRangeMin, oxyRangeMax);
		creat[i].creatureNumber = i + 1;
	}

	//loop through this population and run the fitness tests against them.
	for (int i = 0; i < populationSize; i++)
	{
		ft.creatureFitnessTests(creat[i], envir[0]);

		if (creat[i].isAlive == true)
		{
			aliveList++;

			std::cout << "CREATURE " << creat[i].creatureNumber << std::endl;
			cc.printCreatureVariables(creat[i]);
			std::cout << std::endl << std::endl;
		}
		else if (creat[i].isAlive == false)
			deadList++;
		else
			std::cout << "ERROR: Creature " << creat[i].creatureNumber << " has NULL value to bool isAlive" << std::endl;
	}

	std::cout << "Population left alive is: " << aliveList << std::endl;
	std::cout << "Population number dead is: " << deadList << std::endl;

	float percentageSurvived = static_cast<float>(aliveList) / static_cast<float>(populationSize) * 100;
	percentageSurvived = genFunc->roundFloat(percentageSurvived);
	std::cout << "Survival Chance in environment " << envir[0].ID << " is: " << percentageSurvived << "%" << std::endl;


	//testing for automated environmental creation.
	/*
	for (int i = 1; i < environmentSize; i++)
	{
		std::cout << std::endl << std::endl;
		ec.environmentCreation(envir[i], 300.0f, 600.0f, 5.0f, 15.0f, 20.0f, 80.0f);
	}
	*/
}
