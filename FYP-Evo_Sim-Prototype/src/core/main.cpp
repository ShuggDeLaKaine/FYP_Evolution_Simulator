/** \file main.cpp */

#include <iostream>
#include <vector>
#include "core/headerList.h"


//declaring functions ***ALL NEED ABSTRACTING***
void creatureFitnessTests(Creature &creature, Environment &environment);


std::shared_ptr<GeneralFunctions> genFunc;
EnergyFitnessTest energyTests;
TemperatureFitnessTest tempTests;
OxygenFitnessTest oxygenTests;
CreatureCreation cc;


int main()
{
	Environment envir[6];
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
	//Energy testing environment.
	envir[0].energyAvailable = 500.0f;
	envir[0].temperature = 12.0f;
	envir[0].oxygenationRate = 100.0f;
	envir[0].environmentNumber = 1;

	//Temperature Testing Environment.
	envir[1].energyAvailable = 750.0f;
	envir[1].temperature = 13.0f;
	envir[1].oxygenationRate = 50.0f;
	envir[1].environmentNumber = 2;

	//Oxygen Testing Environment.
	envir[2].energyAvailable = 800.0f;
	envir[2].temperature = 11.0f;
	envir[2].oxygenationRate = 50.0f;
	envir[2].environmentNumber = 3;

	//'EDEN' Testing Environment.
	envir[3].energyAvailable = 1500.0f;
	envir[3].temperature = 14.0f;
	envir[3].oxygenationRate = 100.0f;
	envir[3].environmentNumber = 4;

	//'BAAAAAAD' Testing Environment.
	envir[4].energyAvailable = 100.0f;
	envir[4].temperature = 6.0f;
	envir[4].oxygenationRate = 20.0f;
	envir[4].environmentNumber = 5;

	//'So-So' Testing Environment.
	envir[5].energyAvailable = 750.0f;
	envir[5].temperature = 13.5f;
	envir[5].oxygenationRate = 65.0f;
	envir[5].environmentNumber = 6;
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
		creatureFitnessTests(creat[i], envir[4]);

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
	std::cout << "Survival Chance in environment " << envir[4].environmentNumber << " is: " << percentageSurvived << "%" << std::endl;

}



//function to take the creature and environment and then run all the relevant fitness tests on.
void creatureFitnessTests(Creature &creature, Environment &environment)
{
	//check that the creature is alive to do checks on in the first place.
	if(creature.isAlive)
	{
		//test one - oxygenation fitness test.
		creature.oxyIdeal = oxygenTests.inRangeCheck(100.0f, creature.oxygenTolMax, environment.oxygenationRate);
		creature.oxyTol = oxygenTests.inRangeCheck(creature.oxygenTolMax, creature.oxygenTolMin, environment.oxygenationRate);
		creature.isAlive = oxygenTests.fitnessTest(creature.oxygenDemand, environment.oxygenationRate, creature.oxyTol);

		if(creature.isAlive)
		{
			//test two - temperature fitness test.
			creature.tempIdeal = tempTests.inRangeCheck(creature.idealTempRangeMax, creature.idealTempRangeMin, environment.temperature);
			creature.tempTol = tempTests.inRangeCheck(creature.tolTempRangeMax, creature.tolTempRangeMin, environment.temperature);
			creature.isAlive = tempTests.fitnessTest(creature.tempIdeal, creature.tempTol);

			if (creature.isAlive)
			{
				//test three - energy fitness test.
				creature.energyDemand = oxygenTests.multiplier(creature.energyDemand, creature.oxyTol);
				creature.energyDemand = tempTests.multiplier(creature.energyDemand, creature.tempTol, creature.tempIdeal);
				creature.isAlive = energyTests.fitnessTest(creature.energyDemand, environment.energyAvailable);
			}
		}
	}
}