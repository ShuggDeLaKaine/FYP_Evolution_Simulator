/** \file main.cpp */

#include <iostream>
#include <vector>
#include "core/headerList.h"


//reference to classes.
FullFitnessTest ft;
CreatureCreation cc;
EnvironmentCreation ec;
Mutation mut;
std::shared_ptr<GeneralFunctions> genFunc;
Display ds;

//
const int SEED_POP = 10000;
const int LIFE_CYCLES = 3;
Creature seedPopulationPool[SEED_POP];
//std::vector<Creature> vecStartPopulation;
std::vector<Creature> vecCurrentPopulation;
std::vector<Creature> vecTempPopulation;
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

	int populationSize = (sizeof(seedPopulationPool) / sizeof(*seedPopulationPool));
	int environmentSize = (sizeof(envir) / sizeof(*envir));
	int isAlive = 0;
	int isDead = 0;

	//loop through creature array and create creatures with constrained random variables.
	for (int i = 0; i < populationSize; i++)
	{
		cc.creatureCreation(seedPopulationPool[i], energyCentre, energyGauss, idealTempCentre, idealTempGuass, idealTempRangeMin, idealTempRangeMax,
			tolTempRangeMin, tolTempRangeMax, oxyCentre, oxyGauss, oxyRangeMin, oxyRangeMax);
		seedPopulationPool[i].creatureNumber = i + 1;
		seedPopulationPool[i].creatureID = genFunc->createNewCreatureID(seedPopulationPool[i].creatureNumber, seedPopulationPool[i].generationNumber, 
																			seedPopulationPool[i].childNumber);
	}

	std::cout << std::endl << "SEED POPULATION STAGE" << std::endl << std::endl;

	//loop through this population and run the fitness tests against them to determine which of the seed population will survive and populate the start population.
	for (int i = 0; i < populationSize; i++)
	{
		//run the fitness tests between the creature and the environment.
		ft.creatureFitnessTests(seedPopulationPool[i], envir[0]);

		//if the creature has survived and is alive.
		if (seedPopulationPool[i].isAlive == true)
		{
			//add this creature from seedPopulationPool[] to startPopulationPool[]
			vecTempPopulation.push_back(seedPopulationPool[i]);

			//print surviving creature info to console.
			ds.displayCreatureVariables(vecTempPopulation);
			
			//update isAlive.
			isAlive++;
		}
		else if (seedPopulationPool[i].isAlive == false)
			isDead++;
		else
			std::cout << "ERROR: Creature " << seedPopulationPool[i].creatureNumber << " has NULL value to bool isAlive" << std::endl;
	}

	//update the CURRENT population vector from the temporary population vector.
	cc.duplicatePopulationVectors(vecCurrentPopulation, vecTempPopulation);

	//display required information about survival and populations.
	ds.displaySeedPopulationPoolResult(isAlive, isDead);
	ds.displaySurvivedPercentage(envir[0], isAlive, populationSize);
	ds.displayFirstPopulation(vecCurrentPopulation);

	//clear the temp population vector, to refill again.
	vecTempPopulation.clear();

	//TESTING... duplication of temp population vec to the current population vec.
	std::cout << std::endl << "...END OF SEED STAGE: final CURRENT population size is: " << vecCurrentPopulation.size() << std::endl;
	std::cout << std::endl << "...END OF SEED STAGE: final TEMP population size is: " << vecTempPopulation.size() << std::endl;

	//reset alive and dead counters.
	isAlive = 0;
	isDead = 0;

	//Iterate over life cycles...
	for (int i = 0; i < LIFE_CYCLES; i++)
	{
		//clear the temp population vector, to refill again.
		vecTempPopulation.clear();

		//TESTING... keeping an eye on the which life cycle it is.
		std::cout << std::endl << "LIFE CYCLE: " << i + 1 << std::endl << std::endl;


		//SURVIVAL TEST STAGE...
		//for each life cycle, iterate through the current population vector.
		for (int i = 0; i < vecCurrentPopulation.size(); i++)
		{
			//run the fitness tests between the creature and the environment.
			ft.creatureFitnessTests(vecCurrentPopulation[i], envir[0]);

			//if the creature has survived and is alive.
			if (vecCurrentPopulation[i].isAlive == true)
			{
				//creature has survived, pop it into the temp population vector.
				vecTempPopulation.push_back(vecCurrentPopulation[i]);

				//TESTING... print surviving creature info to console.
				ds.displayCreatureVariables(vecTempPopulation);

				//update isAlive.
				isAlive++;
			}
			else if (seedPopulationPool[i].isAlive == false)
				isDead++;
			else
				std::cout << "ERROR: Creature " << vecTempPopulation[i].creatureNumber << " has NULL value to bool isAlive" << std::endl;
		}
		//clear current pop, as all survivors now in the temp pop vec. 
		//will need to refill current pop vec with the offspring from the temp pop vector.
		vecCurrentPopulation.clear();

		//REPRODUCTION STAGE
		for (int i = 0; i < vecTempPopulation.size(); i++)
		{
			//as survived, DUPLICATE (think bacterial reproduction)
			//cc.duplicateCreature(vecTempPopulation, vecTempPopulation.at(i));
			cc.duplicateCreature(vecCurrentPopulation, vecTempPopulation.at(i));
		}

		//clear temp pop, as offspring in current pop and these creatures would have died.
		//!!!NOTE!!! if checks have more than 1 cycle life span, then will need to move this parent into the current population vec WITHOUT then mutation/crossovering them.
		//maybe need a third 'ParentsVec' for the parents that can be added to the current pop after children had their crossover/mutation stage.
		vecTempPopulation.clear();

		//TESTING... duplication of temp population vec to the current population vec.
		std::cout << "END OF CYCLE " << i + 1 << ": final CURRENT population size is: " << vecCurrentPopulation.size() << std::endl;
		std::cout << "END OF CYCLE " << i + 1 << ": final TEMP population size is: " << vecTempPopulation.size() << std::endl;
	}


	/*
	//TESTING... stuff for mutation functions.
	int MUT_CHANCE = 2;
	int TEST_NUM = 100000;
	float yesMutation = 0;
	float noMutation = 0;
	for (int i = 0; i < TEST_NUM; i++)
		mut.mutationChance(MUT_CHANCE, yesMutation, noMutation);
	//output to console testing info.
	std::cout << std::endl << std::endl << "MUTATION FUNCTION TESTING" << std::endl;
	std::cout << "Number of YES mutated: " << yesMutation << std::endl;
	std::cout << "Number of NO mutated: "  << noMutation << std::endl;
	float mutationChance = (yesMutation / (yesMutation + noMutation)) * 100;
	std::cout << "Percentage chance of mutation is: " << mutationChance << std::endl;
	*/
}
