/** \file main.cpp */
#include "core/main.h"


int main()
{
#pragma region ENVIRONMENTS
	//'Default' Testing Environment.
	envir[0].energyAvailable = 150.0f;
	envir[0].temperature = 12.0f;
	envir[0].oxygenationRate = 25.0f;
	envir[0].fEnvironmentCapacity = envir[0].energyAvailable * envir[0].fCapacityMultiplier;
	envir[0].ID = 1;
#pragma endregion

	genFunc.reset(new GeneralFunctions);
	genFunc->start();

	AllSpecies* allSpeciesPtr = &allSpecies;

	uint32_t populationSize = (sizeof(seedPopulationPool) / sizeof(*seedPopulationPool));
	uint32_t speciesSize = (sizeof(speciesPool) / sizeof(*speciesPool));
	uint32_t environmentSize = (sizeof(envir) / sizeof(*envir));

	if (allSpecies.aliveSpeciesVec.size() != 0)
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

		//std::cout << std::endl << "SEED POPULATION STAGE" << std::endl;

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
							//MUTATE SPECIES STARTING POPULATIONS TO GIVE SOME VARIETY 
							//-4 on the size below so it does NOT mutate the final 3 elements, which arem creature weight, creature size, lifespan and id.
							for (int l = 0; l < (seedPopulationPool[i].geneStack.size() - 4); l++)
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
				sp.assignSpeciesToAllSpeciesVector(speciesPool[tempPosition], allSpecies.aliveSpeciesVec, allSpecies);
				//update species data, such as species average gene stack.
				sp.updateSpeciesGeneStack(allSpecies.aliveSpeciesVec.at(tempPosition));
			}
		}
		//update the various species vectors.
		sp.updateAllSpecies(allSpecies);

		//loop through and update the membership counts of each species.
		//for (int i = 0; i < allSpecies.fullSpeciesVec.size(); i++)
		//	sp.updateSpeciesMembershipCounts(allSpecies.fullSpeciesVec.at(i));
		for (int i = 0; i < allSpecies.aliveSpeciesVec.size(); i++)
			sp.updateSpeciesMembershipCounts(allSpecies.aliveSpeciesVec.at(i));

		//check whether SEED STAGE was successful (ie there's surviving species), if no, do it again.
		if (allSpecies.aliveSpeciesVec.size() != 0)
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
	///ds.displaySurvivedPercentage(envir[0], isAlive, populationSize);

	/*
	//loop through species and match with species ID, 
	for (int i = 0; i < allSpecies.aliveSpeciesVec.size(); i++)
	{
		ds.displaySpeciesPopulationInfo(allSpecies.aliveSpeciesVec.at(i));
		std::cout << std::endl;
	}
	*/
	std::cout << std::endl;
#pragma endregion


//                                 ************    MAIN PART - LIFE CYCLE STAGE    ************
	//iterate over life cycles...
	for (int i = 0; i < LIFE_CYCLES; i++)
	{
		//clear the temp population vector, to refill again.
		vecTempPopulation.clear();

		//update the start of cycle species numbers.
		sp.startCycleMemberships(allSpecies);
		//reset the species cycle counts.
		sp.resetCycleCounts(allSpecies);

		if (i == 0)
		{
			std::cout << std::endl << "THE FIRST POPULATION" << std::endl;
			//total number of species 
			std::cout << "Total Number of Alive Species: " << allSpecies.aliveSpeciesVec.size() << std::endl;

			int totalCreatures = 0;
			for (int i = 0; i < allSpecies.aliveSpeciesVec.size(); i++)
				totalCreatures += allSpecies.aliveSpeciesVec.at(i).currentMembers;

			ds.setLastCreatureNumber(totalCreatures);

			std::cout << "Total Number of Creatures: " << totalCreatures << std::endl;
		}
		

		//***NEW CYCLE*** - take a 1 off life spans.
		for (int i = 0; i < allSpecies.aliveSpeciesVec.size(); i++)
		{
			//iterate through creatures within the species
			for (int j = 0; j < allSpecies.aliveSpeciesVec.at(i).speciesMembership.size(); j++)
			{
				//check whether lifespan 0 or less, if so, remove from temp population.
				if (allSpecies.aliveSpeciesVec.at(i).speciesMembership.at(j).lifeSpan <= 0)
				{
					//then remove from species membership...
					allSpecies.aliveSpeciesVec.at(i).speciesMembership.erase(allSpecies.aliveSpeciesVec.at(i).speciesMembership.begin() + j);
					j--;
					allSpecies.aliveSpeciesVec.at(i).cycleTotalDeadCount++;
					allSpecies.aliveSpeciesVec.at(i).cycleOldAgeDeadCount++;
				}
			}
		}

#pragma region FITNESS_TESTS
		//SURVIVAL TEST STAGE...
		//run fitness tests species by species.
		for(int i = 0; i < allSpecies.aliveSpeciesVec.size(); i++)
		{
			//iterate through species membership, looking at each creature.
			for(int j = 0; j < allSpecies.aliveSpeciesVec.at(i).speciesMembership.size(); j++)
			{
				//run the fitness tests between that creature and the environment.
				ft.creatureFitnessTests(allSpecies.aliveSpeciesVec.at(i).speciesMembership.at(j), envir[0]);
			
				//if the creature has NOT survived and is NOT alive.
				if (allSpecies.aliveSpeciesVec.at(i).speciesMembership.at(j).isAlive == false)
				{
					//then remove from species membership...
					allSpecies.aliveSpeciesVec.at(i).speciesMembership.erase(allSpecies.aliveSpeciesVec.at(i).speciesMembership.begin() + j);
					j--;
					//allSpecies.aliveSpeciesVec.at(i).cycleTotalDeadCount++;
					allSpeciesPtr->aliveSpeciesVec.at(i).cycleTotalDeadCount++;
					allSpecies.aliveSpeciesVec.at(i).cycleFailedFitnessDeadCount++;
				}
				//good time to reduce life spans by 1 as before the offspring and won't risk preemptively reducing offsprings life spans.
				//need a check to make sure species membership has a value to begin with, if none will throw of of bounds.
				if(allSpecies.aliveSpeciesVec.at(i).speciesMembership.size() > 0)
				{
					//need a check to see if j is -1, can throw things out of range here, if so change to hardcode to element 0, otherwise keep at j.
					if (j < 0)					
						allSpecies.aliveSpeciesVec.at(i).speciesMembership.at(0).lifeSpan -= 1;
					else
						allSpecies.aliveSpeciesVec.at(i).speciesMembership.at(j).lifeSpan -= 1;
				}
			}
			//update the species membership count.
			sp.updateSpeciesMembershipCounts(allSpecies.aliveSpeciesVec.at(i));
		}
#pragma endregion

#pragma region WEIGHT_CALCULATIONS_&_ENVIRONMENTAL_STATUS_SETTING
		//POPULATION WEIGHT CALCULATIONS.
		//reset the population weight, ready to be weighed again.
		envir[0].fPopulationWeight = 0.0f;

		if(allSpecies.aliveSpeciesVec.size() != 0)
		{
			//iterate through per species.
			for (int i = 0; i < allSpecies.aliveSpeciesVec.size(); i++)
			{
				float fSpeciesWeight = allSpecies.aliveSpeciesVec.at(i).speciesGeneStack.at(7); //element 7 of gene stack is species creature weight.
				int iSpeciesSize = allSpecies.aliveSpeciesVec.at(i).speciesMembership.size();
				float fTotalSpeciesWeight = iSpeciesSize * fSpeciesWeight;
				//add to the total combined population weight.
				envir[0].fPopulationWeight += fTotalSpeciesWeight;
			}
		} 
		//ENVIRONMENT STATUS SETTING.
		comp.setEnvironmentalStatus(envir[0]);
		
		//std::cout << "Total Creature Weight is: " << envir[0].fPopulationWeight << std::endl;

#pragma endregion

#pragma region COMPETITION_STAGE
		//get the environmental status that currently in.
		comp.getEnvironmentStatus(envir[0]);

		//iterate through the species.
		for (int i = 0; i < allSpecies.aliveSpeciesVec.size(); i++)
		{
			//get the population to compete, factoring creature size.
			int iPopToCompete = comp.getPopulationToCompete(allSpecies.aliveSpeciesVec.at(i).speciesMembership.size(), allSpecies.aliveSpeciesVec.at(i).seedGeneStack.at(8));

			//loop through the popToCompete size of the population, run fitness tests with the reduced environmental energy available.
			for (int j = (allSpecies.aliveSpeciesVec.at(i).speciesMembership.size() - iPopToCompete);
				j < allSpecies.aliveSpeciesVec.at(i).speciesMembership.size(); j++)
			{
				//generate a value of energy to remove from availability.
				//float fEnergyLost = 50.0f;		//hard set FOR NOOOOOOOOOOOWWWWWWWW
				float fEnergyLost = allSpecies.aliveSpeciesVec.at(i).speciesMembership.at(j).finalEnergyDemand;
				if (envir[0].currentStatus != FAMINE)
				{
					fEnergyLost = fEnergyLost * 2.0f;		//a 200% penalty of creatures energy demand.
				}
				else
				{
					float fFamineMulti = genFunc->uniformFloatBetween(4.0f, 8.0f);	//much larger penalty between 400-800% for famine conditions.
					fEnergyLost = fEnergyLost * fFamineMulti;
				}
				//fitness test with this environmental energy reduction.
				ft.creatureFitnessTests(allSpecies.aliveSpeciesVec.at(i).speciesMembership.at(j), envir[0], fEnergyLost);

				//if the creature has NOT survived and is NOT alive.
				if (allSpecies.aliveSpeciesVec.at(i).speciesMembership.at(j).isAlive == false)
				{
					//then remove from species membership...
					allSpecies.aliveSpeciesVec.at(i).speciesMembership.erase(allSpecies.aliveSpeciesVec.at(i).speciesMembership.begin() + j);
					j--;
					//allSpecies.aliveSpeciesVec.at(i).cycleTotalDeadCount++;
					allSpeciesPtr->aliveSpeciesVec.at(i).cycleTotalDeadCount++;
					allSpecies.aliveSpeciesVec.at(i).cycleFailedFitnessDeadCount++;
				}
			}
		}
#pragma endregion

#pragma region REPRODUCTION_STAGE

		//********   SELECTION, CROSSOVER AND OFFSPRING CREATION STAGE   ********
		//loop through the different species. 
		for (int i = 0; i < allSpecies.aliveSpeciesVec.size(); i++)
		{
			//FIRST get the % of species population to reproduce.
			//check if in environmental status... 
			if (envir[0].currentStatus == FAMINE)
				sel.selectionPercentage = sel.selectionPercentage * 0.2f;	//FAMINE state reduce parent seletion by 80%.
			else if(envir[0].currentStatus == CRITICAL)
				sel.selectionPercentage = sel.selectionPercentage * 0.5f;	//CRITICAL state reduce parent seletion by 50%.
			else if (envir[0].currentStatus == PRESSURED)
				sel.selectionPercentage = sel.selectionPercentage * 0.8f;	//PRESSURED state reduce parent seletion by 20%.
			else
				sel.selectionPercentage = 30.0f;

			//clear tempReproduce vec, fill with selected paired parents gene stacks.
			tempReproduce.clear();
			tempReproduce = sel.parentSelection(allSpecies.aliveSpeciesVec.at(i));

			//clear tempCreatsToAdd vec, fill with offspring of parents genestacks, 95% created, still need thresholdScore and finalEnergyDemand. 
			tempCreatsToAdd.clear();
			tempCreatsToAdd = cross.fullCrossover(tempReproduce);
			allSpecies.aliveSpeciesVec.at(i).cycleOffspringCount = tempCreatsToAdd.size();

			//get threshold score and final energy demand for creatures, run fitness tests against the environment for these creatures..
			for (int j = 0; j < tempCreatsToAdd.size(); j++)
				ft.creatureFitnessTests(tempCreatsToAdd.at(j), envir[0]);

			//iterate through the temp creatures vector, push into offspring vector.
			for (int j = 0; j < tempCreatsToAdd.size(); j++)
				vecOffspringPopulation.push_back(tempCreatsToAdd.at(j));
		}
#pragma endregion

#pragma region MUTATION_STAGE
		//MUTATION STAGE - ran on the offspring population as they are the only ones who need to be mutation checks ran on them.
		for (int i = 0; i < vecOffspringPopulation.size(); i++)
		{
			//clear, reserve size and assign current creatures gene stack to a temporary gene stack.
			tempGeneStack.clear();
			tempGeneStack.reserve(vecOffspringPopulation.at(i).geneStack.size());
			tempGeneStack.assign(vecOffspringPopulation.at(i).geneStack.begin(), vecOffspringPopulation.at(i).geneStack.end());

			//iterate through the tempGeneStack array. -4 on the size below so it does NOT mutate the final 4 elements, which are creature weight, creature size, lifespan and id.
			for(int j = 0; j < (tempGeneStack.size() - 4); j++)
			{
				//run a mutation chance test on each element in vector, if it comes back true
				if (mut.mutationTest(mutChance) == true)
					//then run mutation intensity on the gene that will be mutating to determine the strength of that mutation.
					mut.mutationIntensity(mutInten, tempGeneStack.at(j), envir[0].mutationModifier);
			}

			//assign the temp gene stack to the creatures gene stack. 
			vecOffspringPopulation.at(i).geneStack.assign(tempGeneStack.begin(), tempGeneStack.end());

			//update all the creatures variables with these new mutated values.
			cc.updateCreature(vecOffspringPopulation.at(i));			
		}

		//FITNESS TEST NEWLY MUTATED OFFSPRING CREATURES.
		for (int i = 0; i < vecOffspringPopulation.size(); i++)
		{
			//run the fitness tests on the newly fully completed offspring.
			ft.creatureFitnessTests(vecOffspringPopulation.at(i), envir[0]);

			//check whether is has died.
			if (vecOffspringPopulation.at(i).isAlive == false)
			{
				//erase the dead creature.
				vecOffspringPopulation.erase(vecOffspringPopulation.begin() + i);
				//vector would have skrunk, begin i back down with it.
				i--;
			}
		}

		//add these offspring to their relevant species.
		///ABSTRACT THE BELOW FUNCTION TO SOMETHING TO SO WITH SPECIES.
		//ADD CREATURE TO RELEVANT SPECIES.
		//iterate through current population and assign to relevant species.
		for (int i = 0; i < vecOffspringPopulation.size(); i++)
		{
			//get creature ID
			uint32_t tempCreatID = vecOffspringPopulation.at(i).creatureID;

			//loop through species and match with species ID, 
			for (int j = 0; j < allSpecies.aliveSpeciesVec.size(); j++)
			{
				//get the species ID
				uint32_t tempSpeciesID = allSpecies.aliveSpeciesVec.at(j).speciesID;

				//if species ID is 0 then stop iterating through as unassigned species.
				if (tempSpeciesID == 0)
					break;

				//check if species ID and creature ID match
				if (tempCreatID == tempSpeciesID)
				{
					//a match, so this creature needs to be added to this species. 
					sp.addCreatureToSpecies(vecOffspringPopulation.at(i), allSpecies.aliveSpeciesVec.at(j));
					//in it's right place, so break out of the loop looking for its right place.
					break;
				}
			}
		}
		//clear the offspring population vector as done with for this cycle.
		vecOffspringPopulation.clear();

#pragma endregion
		//update the end of cycle species numbers.
		sp.endCycleMemberships(allSpecies);
		//update all the full, alive and extinct species lists.
		sp.updateAllSpecies(allSpecies);

#pragma region SPECIES_UPDATES
		//UPDATE AND DISPLAY SPECIES DATA
		//loop through species and match with the species ID, 
		for (int i = 0; i < allSpecies.aliveSpeciesVec.size(); i++)
		{
			//get the species ID
			uint32_t tempSpecID = allSpecies.aliveSpeciesVec.at(i).speciesID;

			//if species ID is 0 then stop iterating through as at the unassigned species.
			if (tempSpecID == 0)
				break;

			//update species data, such as species average gene stack.
			sp.updateSpeciesGeneStack(allSpecies.aliveSpeciesVec.at(i));
			sp.updateSpeciesMembershipCounts(allSpecies.aliveSpeciesVec.at(i));

			//display species data.
			//ds.displaySpeciesPopulationInfo(allSpecies.aliveSpeciesVec.at(i));
			//ds.displaySpeciesBirthDeathRates(allSpecies.aliveSpeciesVec.at(i));
			//ds.displayGeneStackInfo(allSpecies.aliveSpeciesVec.at(i), allSpecies.aliveSpeciesVec.at(i).speciesGeneStack);
		}
#pragma endregion

		//update species membership counts
		for (int i = 0; i < allSpecies.aliveSpeciesVec.size(); i++)
			sp.updateSpeciesMembershipCounts(allSpecies.aliveSpeciesVec.at(i));


		ds.cycleDisplay(i, allSpecies, envir[0]);
		//********    END OF CYCLE - ABOUT TO REPEAT    ********
	}

	
	std::cout << std::endl << std::endl << std::endl << "                            CYCLES OVER" << std::endl;
	//TESTING --- display each species seed and end gene stacks.
	for (int i = 0; i < allSpecies.aliveSpeciesVec.size(); i++)
	{
		ds.displayGeneStackChange(allSpecies.aliveSpeciesVec.at(i), allSpecies.aliveSpeciesVec.at(i).seedGeneStack,
			allSpecies.aliveSpeciesVec.at(i).speciesGeneStack);
		//display species data.
		ds.displaySpeciesPopulationInfo(allSpecies.aliveSpeciesVec.at(i));	
		std::cout << std::endl;
	}
	
	std::cout << std::endl << std::endl << "                    ********    SIMULATION ENDED    ********" << std::endl;
	genFunc->stop();
}


