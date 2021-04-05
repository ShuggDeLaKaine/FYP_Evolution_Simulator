/** \file main.cpp */
#include "core/main.h"


int main()
{
#pragma region ENVIRONMENTS
	//'BAAAAAAD' Testing Environment.
	envir[0].energyAvailable = 100.0f;
	envir[0].temperature = 6.0f;
	envir[0].oxygenationRate = 20.0f;
	envir[0].ID = 1;
#pragma endregion

	genFunc.reset(new GeneralFunctions);
	genFunc->start();

	uint32_t populationSize = (sizeof(seedPopulationPool) / sizeof(*seedPopulationPool));
	uint32_t speciesSize = (sizeof(speciesPool) / sizeof(*speciesPool));
	uint32_t environmentSize = (sizeof(envir) / sizeof(*envir));

	if (allSpeciesList[0].fullSpeciesList.size() != 0)
		bSuccessfulSeed = true;
	else
		bSuccessfulSeed = false;

#pragma region SEED_POPULATION_STAGE
	do {
	//                                 ************    SEED POPULATION STAGE    ************

		//loop through creature array and create creatures with constrained random variables.
		for (int i = 0; i < populationSize; i++)
		{
			cc.creatureCreation(seedPopulationPool[i], cs.energyCentre, cs.energyGauss, cs.idealTempCentre, cs.idealTempGuass, cs.idealTempRangeMin,
				cs.idealTempRangeMax, cs.tolTempRangeMin, cs.tolTempRangeMax, cs.oxyCentre, cs.oxyGauss, cs.oxyRangeMin, cs.oxyRangeMax, 
				cs.offspringMin, cs.offspringMax, cs.lifeMin, cs.lifeMax);
			seedPopulationPool[i].creatureNumber = i;
			seedPopulationPool[i].creatureID = genFunc->createNewCreatureID(seedPopulationPool[i].creatureNumber);
			cc.addToGeneStack(seedPopulationPool[i].geneStack, seedPopulationPool[i].creatureID);
		}

		std::cout << std::endl << "SEED POPULATION STAGE" << std::endl << std::endl;

		//loop through this population and run the fitness tests against them to determine which of the seed population will survive and populate the start population.
		for (int i = 0; i < populationSize; i++)
		{
			//run the FITNESS TESTS between the seed creature and the environment.
			ft.creatureFitnessTests(seedPopulationPool[i], envir[0]);

			//if the creature has survived and is alive.
			if (seedPopulationPool[i].isAlive == true)
			{
				//********************    SPECIES CREATION    ********************
				//loop through species to find first species element that is unused. 
				for (int j = 0; j < speciesSize; j++)
				{
					//check whether the species has an ID other an 0, it is has another value, loop around to the next element...
					//if it is == 0 then hasn't been assigned yet, so create and add a new species here and break out of loop.
					if (speciesPool[j].speciesID == 0)
					{
						//create a new species with the details creature of creature that passed fitness tests.
						sp.createNewSpecies(speciesPool[j], seedPopulationPool[i].geneStack, seedPopulationPool[i].creatureID);
						break;
					}
				}

				//add creature from seedPop to tempPop, change to STARTING_POP from the original 'Adam & Eve' method of 2 starting creatures per species.
				for (int j = 0; j < STARTING_POP; j++)
				{
					//add this creature from seedPopulationPool[] to tempPopulation[]
					vecTempPopulation.push_back(seedPopulationPool[i]);
					//loop through species...
					for (int k = 0; k < speciesSize; k++)
					{
						//check whether the creature and species IDs are the same.
						if (i == speciesPool[k].speciesID)
						{
							//need to create an initial first population from the initial single creature for this species.
							//they need to be different for one another for the crossover reproduction mechanic to have an effect.
							//therefore, iterate through their geneStacks 
							//-1 on the size below so it does NOT mutate the final element, which is a float containing the creature/species ID.
							for (int l = 0; l < (seedPopulationPool[i].geneStack.size() - 2); l++)
							{
								//and mutate each value in its gene stack slightly.
								mut.mutationIntensity(seedMutIntensity, seedPopulationPool[i].geneStack.at(l), envir[0].mutationModifier);
								//now update all the creatures variables with these new mutated values.
								cc.updateCreature(seedPopulationPool[i]);
							}
							//add this prepped creature to its species.
							sp.addCreatureToSpecies(seedPopulationPool[i], speciesPool[k]);
							tempPosition = k;
						}
						//otherwise check if speciesID == 0, if so break out as into the not yet used species elements.
						else if (speciesPool[k].speciesID == 0)
							break;
					}
				}
				//add this new species to the overall species list.
				sp.assignSpeciesToAllSpeciesVector(speciesPool[tempPosition], allSpeciesList->fullSpeciesList, allSpeciesList[0]);
				//update species data, such as species average gene stack.
				sp.updateSpeciesGeneStack(speciesPool[tempPosition]);

				//print surviving creature info to console.
				///ds.displayCreatureVariables(vecTempPopulation);
				//update isAlive.
				isAlive++;
			}
			else if (seedPopulationPool[i].isAlive == false)
				isDead++;
			else
				std::cout << "ERROR: Creature " << seedPopulationPool[i].creatureNumber << " has NULL value to bool isAlive" << std::endl;
		}

		if (allSpeciesList[0].fullSpeciesList.size() != 0)
			bSuccessfulSeed = true;
		else
			bSuccessfulSeed = false;
	} while (!bSuccessfulSeed);
#pragma endregion

#pragma region FIRST_POPULATION_STAGE
//			                           ************    FIRST POPULATION STAGE    ************
	//update the CURRENT population vector from the temporary population vector.
	cc.duplicatePopulationVectors(vecCurrentPopulation, vecTempPopulation);

	//display required information about survival and populations.
	ds.displaySurvivedPercentage(envir[0], isAlive, populationSize);
	//loop through species and match with species ID, 
	for (int i = 0; i < allSpeciesList[0].fullSpeciesList.size(); i++)
	{
		ds.displaySpeciesPopulationInfo(allSpeciesList[0].fullSpeciesList.at(i));
	}

	//clear the temp population vector, to refill again.
	vecTempPopulation.clear();

	//TESTING... duplication of temp population vec to the current population vec.
	std::cout << std::endl << "...END OF SEED STAGE: final CURRENT population size is: " << vecCurrentPopulation.size() << std::endl;

	//reset alive and dead counters.
	isAlive = 0;
	isDead = 0;
#pragma endregion


//                                 ************    MAIN PART - LIFE CYCLE STAGE    ************
	//iterate over life cycles...
	for (int i = 0; i < LIFE_CYCLES; i++)
	{
		//clear the temp population vector, to refill again.
		vecTempPopulation.clear();

		//TESTING --- keeping an eye on the which life cycle it is.
		std::cout << std::endl << "LIFE CYCLE: " << i + 1 << std::endl << std::endl;

#pragma region FITNESS_TESTS
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
				//update isAlive.
				isAlive++;
			}
			else if (seedPopulationPool[i].isAlive == false)
				isDead++;
			else
				std::cout << "ERROR: Creature " << vecTempPopulation[i].creatureNumber << " has NULL value to bool isAlive" << std::endl;
		}
#pragma endregion

#pragma region REPRODUCTION_STAGE

		//********   SELECTION, CROSSOVER AND OFFSPRING CREATION STAGE   ********
		//loop through the different species. 
		for (int i = 0; i < allSpeciesList[0].fullSpeciesList.size(); i++)
		{
			//clear tempReproduce vec, fill with selected paired parents gene stacks.
			tempReproduce.clear();
			tempReproduce = sel.parentSelection(allSpeciesList[0].fullSpeciesList.at(i));

			//clear tempCreatsToAdd vec, fill with offspring of parents genestacks, 95% created, still need thresholdScore and finalEnergyDemand. 
			tempCreatsToAdd.clear();
			tempCreatsToAdd = cross.fullCrossover(tempReproduce);

			//get threshold score and final energy demand for creatures, run fitness tests against the environment for these creatures..
			for (int j = 0; j < tempCreatsToAdd.size(); j++)
				ft.creatureFitnessTests(tempCreatsToAdd.at(j), envir[0]);

			//iterate through the temp creatures vector, push into offspring vector.
			for (int j = 0; j < tempCreatsToAdd.size(); j++)
				vecOffspringPopulation.push_back(tempCreatsToAdd.at(j));
		}
#pragma endregion

		//CHECK LIFE SPANS OF EXISTING CREATURES AND REMOVE THOSE WHO HAVE DIED.
		//minus -1 to life span of all creatures
		for (int i = 0; i < vecTempPopulation.size(); i++)
		{
			//take a cycle off the life span.
			vecTempPopulation.at(i).lifeSpan -= 1;
			//check whether lifespan 0 or less, if so, remove from temp population.
			if (vecTempPopulation.at(i).lifeSpan <= 0)
			{
				vecTempPopulation.erase(vecTempPopulation.begin() + i);
				//vector skrank by 1, keep i at it's previous position by...
				i--;
			}
		}

		//clear temp pop, as offspring in current pop and these creatures would have died.
		//!!!NOTE!!! if creatures have more than 1 cycle life span, then will need to move this parent into the current population vec WITHOUT then mutation/crossovering them.
		//maybe need a third 'ParentsVec' for the parents that can be added to the current pop after children had their crossover/mutation stage.
		//vecTempPopulation.clear();

#pragma region MUTATION_STAGE
		//MUTATION STAGE - ran on the offspring population as they are the only ones who need to be mutation checks ran on them.
		float mutChance = 2.5f;
		float mutInten = 2.5f;
		float numMut = 0;

		for (int i = 0; i < vecOffspringPopulation.size(); i++)
		{
			//clear the temporary gene stack vector in preparation for use.
			tempGeneStack.clear();
			//reserve the size of the temporoary gene stack to the creatures gene stack size.
			tempGeneStack.reserve(vecOffspringPopulation.at(i).geneStack.size());
			//assign current creatures gene stack to a temporary gene stack.
			tempGeneStack.assign(vecOffspringPopulation.at(i).geneStack.begin(), vecOffspringPopulation.at(i).geneStack.end());

			//iterate through the tempGeneStack array.
			//-1 on size as don't want to mutate the final element which is the species id, need that kept the same.
			for(int j = 0; j < (tempGeneStack.size() - 2); j++)
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
			vecOffspringPopulation.at(i).geneStack.assign(tempGeneStack.begin(), tempGeneStack.end());
			//update all the creatures variables with these new mutated values.
			cc.updateCreature(vecOffspringPopulation.at(i));
		}


		//TESTING... duplication of temp population vec to the current population vec.
		std::cout << "END OF CYCLE " << i + 1 << ": final CURRENT population size is: " << vecCurrentPopulation.size() << std::endl;
		std::cout << "NUMBER OF MUTATION THIS CYCLE " << numMut << std::endl;
		totalNumberMut += numMut;
		numMut = 0;
		std::cout << "Number of POSITIVE mutations is: " << mut.iPosMuts << " with a combined value of: " << mut.fPosMutsTally << std::endl;
		std::cout << "Number of NEGATIVE mutations is: " << mut.iNegMuts << " with a combined value of: " << mut.fNegMutsTally << std::endl;

		//FITNESS TEST NEWLY MUTATED OFFSPRING CREATURES.
		for (int i = 0; i < vecOffspringPopulation.size(); i++)
		{
			//run the fitness tests on the newly fully completed offspring.
			ft.creatureFitnessTests(vecOffspringPopulation.at(i), envir[0]);

			//check whether is has died.
			if (vecOffspringPopulation[i].isAlive == false)
			{
				//erase the dead creature.
				vecOffspringPopulation.erase(vecOffspringPopulation.begin() + i);
				//vector would have skrunk, begin i back down with it.
				i--;
			}
		}
#pragma endregion

		//********   COMBINE POPULATIONS   ********
		//clear current population in prep.
		vecCurrentPopulation.clear();

		//combine the temp population vector with the current population vector of surviving creatures.
		for (int i = 0; i < vecTempPopulation.size(); i++)
			vecCurrentPopulation.push_back(vecTempPopulation.at(i));

		//combine the offspring population with the current population vector of surviving creatures.
		for (int i = 0; i < vecOffspringPopulation.size(); i++)
			vecCurrentPopulation.push_back(vecOffspringPopulation.at(i));

		//clear temp and offspring population for use in the future.
		vecTempPopulation.clear();
		vecOffspringPopulation.clear();



		//********   UPDATE SPECIES   ********
		//clear the species membership list in prep for new membership.
		for (int i = 0; i < allSpeciesList[0].fullSpeciesList.size(); i++)
		{
			allSpeciesList[0].fullSpeciesList.at(i).speciesMembership.clear();
		}

		//iterate through current population and assign to relevant species.
		for (int i = 0; i < vecCurrentPopulation.size(); i++)
		{
			//get creature ID
			uint32_t tempCreatID = vecCurrentPopulation.at(i).creatureID;

			//loop through species and match with species ID, 
			for (int j = 0; j < allSpeciesList[0].fullSpeciesList.size(); j++)
			{
				//get the species ID
				uint32_t tempSpeciesID = allSpeciesList[0].fullSpeciesList.at(j).speciesID;

				//if species ID is 0 then stop iterating through as unassigned species.
				if (tempSpeciesID == 0)
					break;

				//check if species ID and creature ID match
				if (tempCreatID == tempSpeciesID)
				{
					//a match, so this creature needs to be added to this species. 
					sp.addCreatureToSpecies(vecCurrentPopulation.at(i), allSpeciesList[0].fullSpeciesList.at(j));
					//in it's right place, so break out of the loop looking for its right place.
					break;
				}
			}
		}

		//UPDATE AND DISPLAY SPECIES DATA
		//loop through species and match with species ID, 
		for (int i = 0; i < allSpeciesList[0].fullSpeciesList.size(); i++)
		{
			//get the species ID
			uint32_t tempSpecID = allSpeciesList[0].fullSpeciesList.at(i).speciesID;

			//if species ID is 0 then stop iterating through as at the unassigned species.
			if (tempSpecID == 0)
				break;

			//update species data, such as species average gene stack.
			sp.updateSpeciesGeneStack(allSpeciesList[0].fullSpeciesList.at(i));

			//display species data.
			ds.displaySpeciesPopulationInfo(allSpeciesList[0].fullSpeciesList.at(i));

			//display changes in gene stack.
			ds.displayGeneStackChange(allSpeciesList[0].fullSpeciesList.at(i), allSpeciesList[0].fullSpeciesList.at(i).seedGeneStack,
				allSpeciesList[0].fullSpeciesList.at(i).speciesGeneStack);
		}
	}


	//TESTING --- display mutation success and number of mutations. 
	std::cout << std::endl << std::endl << "END OF LIFE CYCLES - RESULTS FOLLOWING" << std::endl << std::endl;
	std::cout << std::endl << "Total number of mutation tests is: " << totalMutTests << std::endl;
	std::cout << "Total number of mutations are: " << totalNumberMut << std::endl;
	float percentMut = static_cast<float>(totalNumberMut) / static_cast<float>(totalMutTests);
	std::cout << "Percentage of mutations is: " << percentMut << std::endl << std::endl;


	//TESTING --- display each species seed and end gene stacks.
	for (int i = 0; i < allSpeciesList[0].fullSpeciesList.size(); i++)
		ds.displayGeneStackChange(allSpeciesList[0].fullSpeciesList.at(i), allSpeciesList[0].fullSpeciesList.at(i).seedGeneStack,
			allSpeciesList[0].fullSpeciesList.at(i).speciesGeneStack);


	genFunc->stop();
}

