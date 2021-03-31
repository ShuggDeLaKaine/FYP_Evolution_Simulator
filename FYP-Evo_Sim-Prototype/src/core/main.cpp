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
const int LIFE_CYCLES = 5;
Creature seedPopulationPool[SEED_POP];
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
			//as survived, DUPLICATE (think bacterial reproduction, atm just doing x2)
			cc.duplicateCreature(vecCurrentPopulation, vecTempPopulation.at(i));
		}

		//clear temp pop, as offspring in current pop and these creatures would have died.
		//!!!NOTE!!! if checks have more than 1 cycle life span, then will need to move this parent into the current population vec WITHOUT then mutation/crossovering them.
		//maybe need a third 'ParentsVec' for the parents that can be added to the current pop after children had their crossover/mutation stage.
		vecTempPopulation.clear();


		//MUTATION STAGE
		std::vector<float> tempGeneStack;
		float mutChance = 2.5f;
		float mutInten = 2.5f;

		for (int i = 0; i < vecCurrentPopulation.size(); i++)
		{
			//clear the temporary gene stack vector in preparation for use.
			tempGeneStack.clear();
			//reserve the size of the temporoary gene stack to the creatures gene stack size.
			tempGeneStack.reserve(vecCurrentPopulation.at(i).geneStack.size());
			//assign current creatures gene stack to a temporary gene stack.
			tempGeneStack.assign(vecCurrentPopulation.at(i).geneStack.begin(), vecCurrentPopulation.at(i).geneStack.end());

			//iterate through the tempGeneStack array.
			for(int j = 0; j < tempGeneStack.size(); j++)
			{
				//run a mutation chance test on each element in vector, if it comes back true
				if (mut.mutationTest(mutChance) == true)
				{
					//then run mutation intensity on the gene that will be mutating to determine the strength of that mutation.
					mut.mutationIntensity(mutInten, tempGeneStack.at(j), envir[0].mutationModifier);
				}
			}
			//assign the temp gene stack to the creatures gene stack. 
			vecCurrentPopulation.at(i).geneStack.assign(tempGeneStack.begin(), tempGeneStack.end());
		}

		//TESTING... duplication of temp population vec to the current population vec.
		std::cout << "END OF CYCLE " << i + 1 << ": final CURRENT population size is: " << vecCurrentPopulation.size() << std::endl;

	}



}




/* //ESPECIALLY USEFUL FOR COMPARING THE HIGHEST DIFFERENCE TO THE MUTATION INTENSITY.
	//testing mutation chance & intensity functions.
	float testRuns = 1000000;
	int yesMut = 0;
	int noMut = 0;
	float mutChance = 2.5f;
	float mutInten = 1.0f;
	float enMulti = 1.0f;


	if(mutInten > 0.05f)
	{
		//NOTE BELOW LINE ONLY REALLY WORKS IF mutInten is dividable by 0.05f.
		int timesToRun = mutInten / 0.05f;		//should be 20 if mutInten starts at 1.0f.

		for (int i = 0; i < timesToRun; i++)
		{
			float diff = 0.0f;
			float avDiff = 0.0f;
			float highDiff = diff;
			float largeMutList = 0;
			float largeMutPercent = 0.0f;

			for (int j = 0; j < testRuns; j++)
			{
				if (mut.mutationTest(mutChance) == true)
				{
					float element2Mutate = 100.0f;

					mut.mutationIntensity(mutInten, element2Mutate, enMulti);
					diff = element2Mutate - 100.0f;

					//set to a positive value if negative.
					if (diff < 0.0f)
						diff = diff * -1.0f;

					//check if a large change.
					if (diff >= 1.0f)
						largeMutList = largeMutList + 1.0f;

					//tally up the avDiff.
					avDiff += diff;

					//check if new diff is larger than highDiff, if so, set highDiff to the diff value.
					if (diff > highDiff)
						highDiff = diff;
					//std::cout << "new mutated element value is: " << element2Mutate << std::endl;
					yesMut++;
				}
				else
					noMut++;
			}
			std::cout << "MUTATION INTENSITY IS: " << mutInten << std::endl;
			std::cout << "highest difference is: " << highDiff << std::endl;

			avDiff = avDiff / testRuns;
			std::cout << "average difference is: " << avDiff << std::endl;

			largeMutPercent = largeMutList / testRuns;
			std::wcout << "percentage of mutations over 1% change is: " << largeMutPercent << std::endl << std::endl;

			mutInten = mutInten - 0.05f;
		}

		//std::cout << "Over " << testRuns << " tests, number of YES mutations is: " << yesMut << " and number of NO mutations is: " << noMut << std::endl;
	}
*/