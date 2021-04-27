

/*
//ENVIRONMENT STATUS SETTING.
//compare population weight to environmental capacity and set environmental status accordingly.
if (envir[0].fPopulationWeight <= (envir[0].fEnvironmentCapacity * fAbundanceMultiplier))	//0.0f to 0.75f
{
	//set environment status to ABUNDANCE...
	signed int temp = ABUNDANCE;
	envir[0].currentStatus = EnvironmentalStatus(temp);
}
else if (envir[0].fPopulationWeight > (envir[0].fEnvironmentCapacity * fAbundanceMultiplier) &&	//0.75f
	envir[0].fPopulationWeight <= envir[0].fEnvironmentCapacity) //0.75f to 1.0f
{
	//set environment status to SUSTAINABLE...
	signed int temp = SUSTAINABLE;
	envir[0].currentStatus = EnvironmentalStatus(temp);
}
else if (envir[0].fPopulationWeight > envir[0].fEnvironmentCapacity &&
	envir[0].fPopulationWeight <= (envir[0].fEnvironmentCapacity * fPressuredMultiplier)) //1.0f to 1.25f
{
	//set environment status to PRESSURED...
	signed int temp = PRESSURED;
	envir[0].currentStatus = EnvironmentalStatus(temp);
}
else if (envir[0].fPopulationWeight > (envir[0].fEnvironmentCapacity * fPressuredMultiplier) &&
	envir[0].fPopulationWeight <= (envir[0].fEnvironmentCapacity * fCriticalMultiplier))	//1.25f to 1.5f
{
	//set environment status to CRITICAL...
	signed int temp = CRITICAL;
	envir[0].currentStatus = EnvironmentalStatus(temp);
}
else if (envir[0].fPopulationWeight > (envir[0].fEnvironmentCapacity * fPressuredMultiplier)) //1.5f>>>
{
	//set environment status to FAMINE...
	signed int temp = FAMINE;
	envir[0].currentStatus = EnvironmentalStatus(temp);
}
else
{
	//else default to sustainable.
	signed int temp = SUSTAINABLE;
	envir[0].currentStatus = EnvironmentalStatus(temp);
}
*/

/*
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
*/


/*
//clear individual species membership elements of alive species in preperation for new membership.
for (int i = 0; i < allSpecies.aliveSpeciesVec.size(); i++)
{
	allSpecies.aliveSpeciesVec.at(i).speciesMembership.clear();
}
*/
/*
//ADD CREATURE TO RELEVANT SPECIES.
//iterate through current population and assign to relevant species.
for (int i = 0; i < vecCurrentPopulation.size(); i++)
{
	//get creature ID
	uint32_t tempCreatID = vecCurrentPopulation.at(i).creatureID;

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
			sp.addCreatureToSpecies(vecCurrentPopulation.at(i), allSpecies.aliveSpeciesVec.at(j));
			//in it's right place, so break out of the loop looking for its right place.
			break;
		}
	}
}
*/

//MUTATION TESTING CONSOLE OUTPUT
/*
//TESTING --- display mutation success and number of mutations.
std::cout << std::endl << std::endl << "END OF LIFE CYCLES - RESULTS FOLLOWING" << std::endl << std::endl;
std::cout << std::endl << "Total number of mutation tests is: " << totalMutTests << std::endl;
std::cout << "Total number of mutations are: " << totalNumberMut << std::endl;
float percentMut = static_cast<float>(totalNumberMut) / static_cast<float>(totalMutTests);
std::cout << "Percentage of mutations is: " << percentMut << std::endl << std::endl;
*/
/*
//TESTING... duplication of temp population vec to the current population vec.
std::cout << "END OF CYCLE " << i + 1 << ": final CURRENT population size is: " << vecCurrentPopulation.size() << std::endl;
std::cout << "NUMBER OF MUTATION THIS CYCLE " << numMut << std::endl;
totalNumberMut += numMut;
numMut = 0;
std::cout << "Number of POSITIVE mutations is: " << mut.iPosMuts << " with a combined value of: " << mut.fPosMutsTally << std::endl;
std::cout << "Number of NEGATIVE mutations is: " << mut.iNegMuts << " with a combined value of: " << mut.fNegMutsTally << std::endl;
*/

//FITNESS FUNCTION TESTS FOR THE currentPopVec and tempPopVec way of doing it.
/*
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
*/

//BACTERIA METHOD, 1 parent divides into 2 offspring.
//cc.duplicateCreature(vecCurrentPopulation, vecTempPopulation.at(i));


//bacteria reproduction method, 1 creature divides into 2.
/*
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
	*/

//testing for automated environmental creation.
/*
for (int i = 1; i < environmentSize; i++)
{
	std::cout << std::endl << std::endl;
	ec.environmentCreation(envir[i], 300.0f, 600.0f, 5.0f, 15.0f, 20.0f, 80.0f);
}
*/

//hand-built testing environments.
/*
#pragma region ENVIRONMENTS
	//Energy testing environment.
	envir[0].energyAvailable = 500.0f;
	envir[0].temperature = 12.0f;
	envir[0].oxygenationRate = 100.0f;
	envir[0].ID = 1;

	//Temperature Testing Environment.
	envir[1].energyAvailable = 750.0f;
	envir[1].temperature = 13.0f;
	envir[1].oxygenationRate = 50.0f;
	envir[1].ID = 2;

	//Oxygen Testing Environment.
	envir[2].energyAvailable = 800.0f;
	envir[2].temperature = 11.0f;
	envir[2].oxygenationRate = 50.0f;
	envir[2].ID = 3;

	//'EDEN' Testing Environment.
	envir[3].energyAvailable = 1500.0f;
	envir[3].temperature = 14.0f;
	envir[3].oxygenationRate = 100.0f;
	envir[3].ID = 4;

	//'BAAAAAAD' Testing Environment.
	envir[4].energyAvailable = 100.0f;
	envir[4].temperature = 6.0f;
	envir[4].oxygenationRate = 20.0f;
	envir[4].ID = 5;

	//'So-So' Testing Environment.
	envir[5].energyAvailable = 750.0f;
	envir[5].temperature = 13.5f;
	envir[5].oxygenationRate = 65.0f;
	envir[5].ID = 6;
#pragma endregion
*/

//hand-built creatures for testing.
	/*
#pragma region TEST_ENERGY_AVAILABLE.

	//extra creature 13 to test the new creature creation functions.
	setCreatureVariables(creat[12], energyCentre, energyGauss, idealTempCentre, idealTempGuass, idealTempRangeMin, idealTempRangeMax,
		tolTempRangeMin, tolTempRangeMax, oxyCentre, oxyGauss, oxyRangeMin, oxyRangeMax);
	creat[12].creatureNumber = 13;


	//creature 0 - should SURVIVE ideally suited to environment 0.
	creat[0].energyDemand = 400.0f;		//in range of environ energy.
	creat[0].idealTemp = 12.0f;			//same as environ temp.
	creat[0].idealTempRange = 1.0f;
	creat[0].tolTempRange = 1.0f;
	creat[0].oxygenDemand = 30.0f;
	creat[0].oxygenRange = 15.0f;

	creat[0].idealTempRangeMax = creat[0].idealTemp + creat[0].idealTempRange;
	creat[0].idealTempRangeMin = creat[0].idealTemp - creat[0].idealTempRange;
	creat[0].tolTempRangeMax = creat[0].idealTempRangeMax + creat[0].tolTempRange;
	creat[0].tolTempRangeMin = creat[0].idealTempRangeMin - creat[0].tolTempRange;
	creat[0].oxygenTolMin = creat[0].oxygenDemand - creat[0].oxygenRange;

	creat[0].isAlive = true;
	creat[0].tempIdeal = true;
	creat[0].tempTol = true;
	creat[0].tolOxygen = true;

	creat[0].creatureNumber = 1;

	//creature 1 - should NOT SURVIVE be suited to environment 0.
	creat[1].energyDemand = 650.0f;		//over the range, not even environ energy.
	creat[1].idealTemp = 12.0f;			//same as environ temp.
	creat[1].idealTempRange = 1.0f;
	creat[1].tolTempRange = 1.0f;
	creat[1].oxygenDemand = 72.0f;
	creat[1].oxygenRange = 5.0f;

	creat[1].idealTempRangeMax = creat[1].idealTemp + creat[1].idealTempRange;
	creat[1].idealTempRangeMin = creat[1].idealTemp - creat[1].idealTempRange;
	creat[1].tolTempRangeMax = creat[1].idealTempRangeMax + creat[1].tolTempRange;
	creat[1].tolTempRangeMin = creat[1].idealTempRangeMin - creat[1].tolTempRange;
	creat[1].oxygenTolMin = creat[1].oxygenDemand - creat[1].oxygenRange;

	creat[1].isAlive = true;
	creat[1].tempIdeal = true;
	creat[1].tempTol = true;
	creat[1].tolOxygen = true;

	creat[1].creatureNumber = 2;
#pragma endregion

#pragma region TEST_TEMPERATURE_IDEAL
	//creature 2 - should SURVIVE suited to environment 0.
	creat[2].energyDemand = 200.0f;		//over the range, not even environ energy.
	creat[2].idealTemp = 12.0f;			//same as environ temp.
	creat[2].idealTempRange = 2.0f;		//
	creat[2].tolTempRange = 1.0f;		//
	creat[2].oxygenDemand = 40.0f;
	creat[2].oxygenRange = 5.0f;

	creat[2].idealTempRangeMax = creat[2].idealTemp + creat[2].idealTempRange;
	creat[2].idealTempRangeMin = creat[2].idealTemp - creat[2].idealTempRange;
	creat[2].tolTempRangeMax = creat[2].idealTempRangeMax + creat[2].tolTempRange;
	creat[2].tolTempRangeMin = creat[2].idealTempRangeMin - creat[2].tolTempRange;
	creat[2].oxygenTolMin = creat[2].oxygenDemand - creat[2].oxygenRange;

	creat[2].isAlive = true;
	creat[2].tempIdeal = true;
	creat[2].tempTol = true;
	creat[2].tolOxygen = true;

	creat[2].creatureNumber = 3;

	//creature 3 - should NOT SURVIVE be suited to environment 0.
	creat[3].energyDemand = 200.0f;			//over the range, not even environ energy.
	creat[3].idealTemp = 20.0f;				//much higher than environ temp.
	creat[3].idealTempRange = 1.0f;
	creat[3].tolTempRange = 1.0f;
	creat[3].oxygenDemand = 85.0f;
	creat[3].oxygenRange = 20.0f;

	creat[3].idealTempRangeMax = creat[3].idealTemp + creat[3].idealTempRange;
	creat[3].idealTempRangeMin = creat[3].idealTemp - creat[3].idealTempRange;
	creat[3].tolTempRangeMax = creat[3].idealTempRangeMax + creat[3].tolTempRange;
	creat[3].tolTempRangeMin = creat[3].idealTempRangeMin - creat[3].tolTempRange;
	creat[3].oxygenTolMin = creat[3].oxygenDemand - creat[3].oxygenRange;

	creat[3].isAlive = true;
	creat[3].tempIdeal = true;
	creat[3].tempTol = true;
	creat[3].tolOxygen = true;

	creat[3].creatureNumber = 4;
#pragma endregion

#pragma region TEST_TEMPERATURE_TOLERANCE_RANGES
	//creature 4 - should SURVIVE, inside ideal idealTemp range.
	creat[4].energyDemand = 200.0f;
	creat[4].idealTemp = 11.5f;
	creat[4].idealTempRange = 1.0f;
	creat[4].tolTempRange = 2.0f;
	creat[4].oxygenDemand = 20.0f;
	creat[4].oxygenRange = 10.0f;

	creat[4].idealTempRangeMax = creat[4].idealTemp + creat[4].idealTempRange;
	creat[4].idealTempRangeMin = creat[4].idealTemp - creat[4].idealTempRange;
	creat[4].tolTempRangeMax = creat[4].idealTempRangeMax + creat[4].tolTempRange;
	creat[4].tolTempRangeMin = creat[4].idealTempRangeMin - creat[4].tolTempRange;
	creat[4].oxygenTolMin = creat[4].oxygenDemand - creat[4].oxygenRange;

	creat[4].isAlive = true;
	creat[4].tempIdeal = true;
	creat[4].tempTol = true;
	creat[4].tolOxygen = true;

	creat[4].creatureNumber = 5;

	//creature 5 - should SURVIVE, inside tolerated idealTemp range and still enough energy remaining after multiplier.
	creat[5].energyDemand = 200.0f;
	creat[5].idealTemp = 10.0f;
	creat[5].idealTempRange = 1.0f;
	creat[5].tolTempRange = 2.0f;
	creat[5].oxygenDemand = 90.0f;
	creat[5].oxygenRange = 25.0f;

	creat[5].idealTempRangeMax = creat[5].idealTemp + creat[5].idealTempRange;
	creat[5].idealTempRangeMin = creat[5].idealTemp - creat[5].idealTempRange;
	creat[5].tolTempRangeMax = creat[5].idealTempRangeMax + creat[5].tolTempRange;
	creat[5].tolTempRangeMin = creat[5].idealTempRangeMin - creat[5].tolTempRange;
	creat[5].oxygenTolMin = creat[5].oxygenDemand - creat[5].oxygenRange;

	creat[5].isAlive = true;
	creat[5].tempIdeal = true;
	creat[5].tempTol = true;
	creat[5].tolOxygen = true;

	creat[5].creatureNumber = 6;

	//creature 6 - should NOT SURVIVE, inside tolerated idealTemp range but NOT enough energy remaining after multiplier.
	creat[6].energyDemand = 600.0f;
	creat[6].idealTemp = 10.0f;
	creat[6].idealTempRange = 1.0f;
	creat[6].tolTempRange = 2.0f;
	creat[6].oxygenDemand = 60.0f;
	creat[6].oxygenRange = 50.0f;

	creat[6].idealTempRangeMax = creat[6].idealTemp + creat[6].idealTempRange;
	creat[6].idealTempRangeMin = creat[6].idealTemp - creat[6].idealTempRange;
	creat[6].tolTempRangeMax = creat[6].idealTempRangeMax + creat[6].tolTempRange;
	creat[6].tolTempRangeMin = creat[6].idealTempRangeMin - creat[6].tolTempRange;
	creat[6].oxygenTolMin = creat[6].oxygenDemand - creat[6].oxygenRange;

	creat[6].isAlive = true;
	creat[6].tempIdeal = true;
	creat[6].tempTol = true;
	creat[6].tolOxygen = true;

	creat[6].creatureNumber = 7;

#pragma endregion

#pragma region OXYGENATION_TESTING
	//creature 8 - should SURVIVE - tested again Envir[2], provides 50.0f oxygen, creature demands just 40.0f.
	creat[7].energyDemand = 450.0f;
	creat[7].idealTemp = 16.0f;
	creat[7].idealTempRange = 1.0f;
	creat[7].tolTempRange = 2.0f;
	creat[7].oxygenDemand = 40.0f;
	creat[7].oxygenRange = 0.0f;

	creat[7].idealTempRangeMax = creat[7].idealTemp + creat[7].idealTempRange;
	creat[7].idealTempRangeMin = creat[7].idealTemp - creat[7].idealTempRange;
	creat[7].tolTempRangeMax = creat[7].idealTempRangeMax + creat[7].tolTempRange;
	creat[7].tolTempRangeMin = creat[7].idealTempRangeMin - creat[7].tolTempRange;
	creat[7].oxygenTolMin = creat[7].oxygenDemand - creat[7].oxygenRange;

	creat[7].isAlive = true;
	creat[7].tempIdeal = true;
	creat[7].tempTol = true;
	creat[7].tolOxygen = true;

	creat[7].creatureNumber = 8;

	//creature 9- should NOT SURVIVE - tested again Envir[2], provides 50.0f oxygen, creature demands 60.0f.
	creat[8].energyDemand = 450.0f;
	creat[8].idealTemp = 16.0f;
	creat[8].idealTempRange = 1.0f;
	creat[8].tolTempRange = 2.0f;
	creat[8].oxygenDemand = 60.0f;
	creat[8].oxygenRange = 0.0f;

	creat[8].idealTempRangeMax = creat[8].idealTemp + creat[8].idealTempRange;
	creat[8].idealTempRangeMin = creat[8].idealTemp - creat[8].idealTempRange;
	creat[8].tolTempRangeMax = creat[8].idealTempRangeMax + creat[8].tolTempRange;
	creat[8].tolTempRangeMin = creat[8].idealTempRangeMin - creat[8].tolTempRange;
	creat[8].oxygenTolMin = creat[8].oxygenDemand - creat[8].oxygenRange;

	creat[8].isAlive = true;
	creat[8].tempIdeal = true;
	creat[8].tempTol = true;
	creat[8].tolOxygen = true;

	creat[8].creatureNumber = 9;
#pragma endregion

#pragma region TESTING_OXYGENATION_RANGES
	//creature 10 - should SURVIVE - within oxygenation tolerance range, will get multiplier, will still have enough energy to survive
	creat[9].energyDemand = 300.0f;
	creat[9].idealTemp = 16.0f;
	creat[9].idealTempRange = 1.0f;
	creat[9].tolTempRange = 2.0f;
	creat[9].oxygenDemand = 55.0f;
	creat[9].oxygenRange = 10.0f;

	creat[9].idealTempRangeMax = creat[9].idealTemp + creat[9].idealTempRange;
	creat[9].idealTempRangeMin = creat[9].idealTemp - creat[9].idealTempRange;
	creat[9].tolTempRangeMax = creat[9].idealTempRangeMax + creat[9].tolTempRange;
	creat[9].tolTempRangeMin = creat[9].idealTempRangeMin - creat[9].tolTempRange;
	creat[9].oxygenTolMin = creat[9].oxygenDemand - creat[9].oxygenRange;

	creat[9].isAlive = true;
	creat[9].tempIdeal = true;
	creat[9].tempTol = true;
	creat[9].tolOxygen = true;

	creat[9].creatureNumber = 10;

	//creature 11 - should NOT SURVIVE - outside of oxygenation range even with tolerance.
	creat[10].energyDemand = 450.0f;
	creat[10].idealTemp = 16.0f;
	creat[10].idealTempRange = 1.0f;
	creat[10].tolTempRange = 2.0f;
	creat[10].oxygenDemand = 60.0f;
	creat[10].oxygenRange = 5.0f;

	creat[10].idealTempRangeMax = creat[10].idealTemp + creat[10].idealTempRange;
	creat[10].idealTempRangeMin = creat[10].idealTemp - creat[10].idealTempRange;
	creat[10].tolTempRangeMax = creat[10].idealTempRangeMax + creat[10].tolTempRange;
	creat[10].tolTempRangeMin = creat[10].idealTempRangeMin - creat[10].tolTempRange;
	creat[10].oxygenTolMin = creat[10].oxygenDemand - creat[10].oxygenRange;

	creat[10].isAlive = true;
	creat[10].tempIdeal = true;
	creat[10].tempTol = true;
	creat[10].tolOxygen = true;

	creat[10].creatureNumber = 11;

	//creature 11 - should NOT SURVIVE - inside oxygen tolerance range BUT energy multiplier will take outside of energy provided by environment.
	creat[11].energyDemand = 800.0f;
	creat[11].idealTemp = 16.0f;
	creat[11].idealTempRange = 1.0f;
	creat[11].tolTempRange = 2.0f;
	creat[11].oxygenDemand = 60.0f;
	creat[11].oxygenRange = 15.0f;

	creat[11].idealTempRangeMax = creat[11].idealTemp + creat[11].idealTempRange;
	creat[11].idealTempRangeMin = creat[11].idealTemp - creat[11].idealTempRange;
	creat[11].tolTempRangeMax = creat[11].idealTempRangeMax + creat[11].tolTempRange;
	creat[11].tolTempRangeMin = creat[11].idealTempRangeMin - creat[11].tolTempRange;
	creat[11].oxygenTolMin = creat[11].oxygenDemand - creat[11].oxygenRange;

	creat[11].isAlive = true;
	creat[11].tempIdeal = true;
	creat[11].tempTol = true;
	creat[11].tolOxygen = true;

	creat[11].creatureNumber = 12;
#pragma endregion
*/

//testing stuff.
	/*
	//TESTING --- pre-created creature, seeing if setCreatureVariables changes these initial values and how.
	std::cout << "PRE AUTOMATED CHANGED" << std::endl;
	printCreatureVariables(creat[12]);
	std::cout << std::endl;

	setCreatureVariables(creat[12], energyCentre, energyGauss, idealTempCentre, idealTempGuass, idealTempRangeMin, idealTempRangeMax,
		tolTempRangeMin, tolTempRangeMax, oxyCentre, oxyGauss, oxyRangeMin, oxyRangeMax);

	std::cout <<  "POST AUTOMATED CHANGED" << std::endl;
	printCreatureVariables(creat[12]);
	*/
	/*
	//TESTING --- passing by reference functions working as required.
	std::cout << "PRE-FITNESS TESTS --- Creature 2 is alive = ";
	if (creat[1].isAlive == true)
		std::cout << "TRUE" << std::endl;
	else if (creat[1].isAlive == false)
		std::cout << "FALSE" << std::endl;
	else
		std::cout << "ERROR --- no value" << std::endl;

	creatureFitnessTests(creat[1], envir[0]);

	std::cout << "POST-FITNESS TESTS --- Creature 2 is alive = ";
	if (creat[1].isAlive == true)
		std::cout << "TRUE" << std::endl;
	else if (creat[1].isAlive == false)
		std::cout << "FALSE" << std::endl;
	else
		std::cout << "ERROR --- no value" << std::endl;
	*/

	/*
	std::cout << "Testing of energy, temperature & oxygenation levels." << std::endl;
	//TESTING - energy levels.
	creatureFitnessTests(creat[0], envir[0]);
	creatureFitnessTests(creat[1], envir[0]);

	//TESTING - idealTemp levels.
	creatureFitnessTests(creat[2], envir[0]);
	creatureFitnessTests(creat[3], envir[0]);

	//TESTING - idealTemp tolerance and energy demand multiplier.
	creatureFitnessTests(creat[4], envir[0]);
	creatureFitnessTests(creat[5], envir[0]);
	creatureFitnessTests(creat[6], envir[0]);

	//TESTING - oxygenation levels, just in or out.
	creatureFitnessTests(creat[7], envir[1]);
	creatureFitnessTests(creat[8], envir[1]);

	//TESTING - oxygenation tolerance and energy demand multiplier
	creatureFitnessTests(creat[9], envir[1]);
	creatureFitnessTests(creat[10], envir[1]);
	creatureFitnessTests(creat[11], envir[1]);
	*/
	/*
	//EDEN environment testing
	int i = 0;
	std::cout << std::endl;
	std::cout << "'EDEN' testing environment." << std::endl;
	//int arraySize = sizeof(creat);	//NOT WORKING - getting 624??? rather than 12 expected...???
	for (i = 0; i <= 11; i++)
	{
		creatureFitnessTests(creat[i], envir[3]);
	}

	//BAAAAAAD environment testing
	i = 0;
	std::cout << std::endl;
	std::cout << "'BAAAAAAAAAD' testing environment." << std::endl;
	for (i = 0; i <= 11; i++)
	{
		creatureFitnessTests(creat[i], envir[4]);
	}

	//So-So environment testing
	i = 0;
	std::cout << std::endl;
	std::cout << "'So-So' testing environment." << std::endl;
	for (i = 0; i <= 11; i++)
	{
		creatureFitnessTests(creat[i], envir[5]);
	}
	*/

//output code.
	/*
	//console output.
	std::cout << "Did Creature " << creature.creatureNumber << " survive?   ";
	if (creature.isAlive)
		std::cout << "   YES! CREATURE " << creature.creatureNumber << " SURVIVED!" << std::endl;
	else
		std::cout << "   NO! CREATURE " << creature.creatureNumber << " IS DEAD!" << std::endl;
	*/