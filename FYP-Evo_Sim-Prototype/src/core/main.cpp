/** \file main.cpp */
#include "core/main.h"



int main()
{
	genFunc.reset(new GeneralFunctions);
	genFunc->start();

#pragma region ENVIRONMENTS
	//'BAAAAAAD' Testing Environment.
	envir[0].energyAvailable = 100.0f;
	envir[0].temperature = 6.0f;
	envir[0].oxygenationRate = 20.0f;
	envir[0].ID = 1;
#pragma endregion

	uint32_t populationSize  = (sizeof(seedPopulationPool) / sizeof(*seedPopulationPool));
	uint32_t speciesSize     = (sizeof(speciesPool) / sizeof(*speciesPool));
	uint32_t environmentSize = (sizeof(envir) / sizeof(*envir));



//                                 ************    SEED POPULATION STAGE    ************

	//loop through creature array and create creatures with constrained random variables.
	for (int i = 0; i < populationSize; i++)
	{
		cc.creatureCreation(seedPopulationPool[i], cs.energyCentre, cs.energyGauss, cs.idealTempCentre, cs.idealTempGuass, cs.idealTempRangeMin, 
			cs.idealTempRangeMax, cs.tolTempRangeMin, cs.tolTempRangeMax, cs.oxyCentre, cs.oxyGauss, cs.oxyRangeMin, cs.oxyRangeMax);
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
			//********************    SPECIES CREATION    ********************
			//loop through species to find first species element that is unused. 
			for(int j = 0; j < speciesSize; j++)
			{
				//check whether the species has an ID other an 0, it is has another value, loop around to the next element...
				//if it is == 0 then hasn't been assigned yet, so create and add a new species to here and break out of loop.
				if (speciesPool[j].speciesID == 0)
				{
					//create a new species with the details creature of creature that passed fitness tests.
					sp.createNewSpecies(speciesPool[j], seedPopulationPool[i].geneStack, i + 1);
					break;
				}
			}
			//add this creature from seedPopulationPool[] to tempPopulation[]
			vecTempPopulation.push_back(seedPopulationPool[i]);
			//add another of these creatures to the tempPopulation to create an 'Adam & Eve' of this species.
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


	//                                 ************    FIRST POPULATION STAGE    ************

	//each creature species now has two identicial members in the tempPopulation vector. 
	//to encourage diversification of species, seed parents should be slightly different otherwise the crossover stage has no effect. 
	//so, loop through vector of creatures and mutate each element of their geneStack vectors with an initial smaller mutation intensity.
	for (int i = 0; i < vecTempPopulation.size(); i++)
	{
		//clear the temporary gene stack vector in preparation for use.
		tempGeneStack.clear();
		//reserve the size of the temporoary gene stack to the creatures gene stack size.
		tempGeneStack.reserve(vecTempPopulation.at(i).geneStack.size());
		//assign current creatures gene stack to a temporary gene stack.
		tempGeneStack.assign(vecTempPopulation.at(i).geneStack.begin(), vecTempPopulation.at(i).geneStack.end());

		//iterate through the tempGeneStack array and run a mutation on each element.
		for (int j = 0; j < tempGeneStack.size(); j++)
			mut.mutationIntensity(seedMutIntensity, tempGeneStack.at(j), envir[0].mutationModifier);

		//assign the temp gene stack to the creatures gene stack. 
		vecTempPopulation.at(i).geneStack.assign(tempGeneStack.begin(), tempGeneStack.end());
		//update all the creatures variables with these new mutated values.
		cc.updateCreatureWithMutations(vecTempPopulation.at(i));
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


	//                                 ************    LIFE CYCLE STAGE    ************

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
		float mutChance = 2.5f;
		float mutInten = 2.5f;
		float numMut = 0;

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
				totalMutTests++;
				//run a mutation chance test on each element in vector, if it comes back true
				if (mut.mutationTest(mutChance) == true)
				{
					//then run mutation intensity on the gene that will be mutating to determine the strength of that mutation.
					mut.mutationIntensity(mutInten, tempGeneStack.at(j), envir[0].mutationModifier);
					numMut++;
				}
			}
			//assign the temp gene stack to the creatures gene stack. 
			vecCurrentPopulation.at(i).geneStack.assign(tempGeneStack.begin(), tempGeneStack.end());
			//update all the creatures variables with these new mutated values.
			cc.updateCreatureWithMutations(vecCurrentPopulation.at(i));
		}

		//TESTING... duplication of temp population vec to the current population vec.
		std::cout << "END OF CYCLE " << i + 1 << ": final CURRENT population size is: " << vecCurrentPopulation.size() << std::endl;
		std::cout << "NUMBER OF MUTATION THIS CYCLE " << numMut << std::endl;
		totalNumberMut += numMut;
		numMut = 0;
	}

	//testing mutation success and number of mutations. 
	std::cout << "Total number of mutation tests is: " << totalMutTests << std::endl;
	std::cout << "Total number of mutations are: " << totalNumberMut << std::endl;
	float percentMut = static_cast<float>(totalNumberMut) / static_cast<float>(totalMutTests);
	std::cout << "Percentage of mutations is: " << percentMut << std::endl;


	genFunc->stop();
}
