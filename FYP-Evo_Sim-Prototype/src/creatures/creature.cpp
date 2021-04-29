/** \file creatures.cpp */
#include "creatures/creature.h"
#include "..\..\include\creatures\creature.h"


CreatureCreation::~CreatureCreation()
{
	//***NEED TO*** kill that shared pointer to the genFuncs 

}

void CreatureCreation::creatureCreation(Creature & creature, float energyCentre, float energyGauss, float idealTempCentre, float idealTempGuass, 
	float idealTempRangeMin, float idealTempRangeMax, float tolTempRangeMin, float tolTempRangeMax, float oxyCentre, float oxyGauss, 
	float oxyRangeMin, float oxyRangeMax, float offspringMin, float offspringMax, uint32_t lifeMin, uint32_t lifeMax)
{
	//pick creature size.
	signed int randNum = genFunc->uniformIntBetween(0, 9);
	if (randNum > 4)
		randNum = 4;
	creature.creatureSize = CreatureSize(randNum);

	float fStartEnergy = 1.0f;

	switch (creature.creatureSize)
	{
	case VERY_SMALL:
		//set creature weight, life span and litter size.
		creature.creatureWeight = multiplier(creature.creatureWeight, 0.2f);
		creature.lifeSpan = 1;	//As very small, hard set to 1, as that is all a very small creature should live for.
		creature.litterSize = multiplier(creature.litterSize, 2.0f);
		fStartEnergy = multiplier(fStartEnergy, 100.0f);	//CHANGE TO A RANDOM RANGE.
		break;
	case SMALL:
		//set creature weight, life span and litter size.
		creature.creatureWeight = multiplier(creature.creatureWeight, 0.6f);
		creature.lifeSpan = multiplier(creature.lifeSpan, 0.5f);
		creature.litterSize = multiplier(creature.litterSize, 1.5f);
		fStartEnergy = multiplier(fStartEnergy, 200.0f);	//CHANGE TO A RANDOM RANGE.
		break;
	case MEDIUM:
		//set creature life span and litter size; leave weight the initialised standard.
		plusMinusOne(creature.lifeSpan, creature.litterSize);
		fStartEnergy = multiplier(fStartEnergy, 300.0f);	//CHANGE TO A RANDOM RANGE.
		break;
	case LARGE:
		//set creature weight, life span and litter size.
		creature.creatureWeight = multiplier(creature.creatureWeight, 1.4f);
		creature.lifeSpan = multiplier(creature.lifeSpan, 1.5f);;
		creature.litterSize = multiplier(creature.litterSize, 0.5f);
		fStartEnergy = multiplier(fStartEnergy, 400.0f);	//CHANGE TO A RANDOM RANGE.
		break;
	case VERY_LARGE:
		//set creature weight, life span and litter size.
		creature.creatureWeight = multiplier(creature.creatureWeight, 1.8f);
		creature.lifeSpan = multiplier(creature.lifeSpan, 2.0f);	
		creature.litterSize = 1.0f;	//As very large, hard set to 1, as that is all avery large creatures litter size should be.
		fStartEnergy = multiplier(fStartEnergy, 500.0f);	//CHANGE TO A RANDOM RANGE.
		break;
	}

	creature.initialEnergyDemand = genFunc->normalFloatBetween(energyCentre, energyGauss);
	//creature.initialEnergyDemand = genFunc->normalFloatBetween(fStartEnergy, energyGauss);
	
	creature.initialEnergyDemand = genFunc->roundFloat(creature.initialEnergyDemand);
	if (creature.initialEnergyDemand <= 0.0f)
	{	//CHOICE!!!
		//do we remove the creature if their energy demand is less than 0...
			//add to remove and delete list.
		//or, do we randomly pick a constrained low number?
		creature.initialEnergyDemand = resetVariable(1.0f, 20.0f, 60.0f, 80.0f);
	}
	fillGeneElement(creature, creature.geneStack, creature.initialEnergyDemand);	//geneStack element (0) - initial energy demand

	creature.idealTemp = genFunc->normalFloatBetween(idealTempCentre, idealTempGuass);
	creature.idealTemp = genFunc->roundFloat(creature.idealTemp);
	fillGeneElement(creature, creature.geneStack, creature.idealTemp);				//geneStack element (1) - ideal temperature

	creature.idealTempRange = genFunc->uniformFloatBetween(idealTempRangeMin, idealTempRangeMax);
	fillGeneElement(creature, creature.geneStack, creature.idealTempRange);			//geneStack element (2) - ideal temperature range

	creature.tolTempRange = genFunc->uniformFloatBetween(tolTempRangeMin, tolTempRangeMax);
	fillGeneElement(creature, creature.geneStack, creature.tolTempRange);			//geneStack element (3) - tolerated temperature range.

	creature.oxygenDemand = genFunc->normalFloatBetween(oxyCentre, oxyGauss);
	creature.oxygenDemand = genFunc->roundFloat(creature.oxygenDemand);
	if (creature.oxygenDemand <= 0.0f)
	{	//CHOICE!!!
		//do we remove the creature if their oxygen demand is less than 0...
			//add to remove and delete list.
		//or, do we randomly pick a constrained low number?
		creature.oxygenDemand = resetVariable(1.0f, 5.0f, 15.0f, 20.0f);
	}
	fillGeneElement(creature, creature.geneStack, creature.oxygenDemand);			//geneStack element (4) - oxygen demand

	creature.oxygenRange = genFunc->uniformFloatBetween(oxyRangeMin, oxyRangeMax);
	fillGeneElement(creature, creature.geneStack, creature.oxygenRange);			//geneStack element (5) - oxygen range

	creature.idealTempRangeMax = creature.idealTemp + creature.idealTempRange;
	creature.idealTempRangeMin = creature.idealTemp - creature.idealTempRange;
	if (creature.idealTempRangeMin <= 0.0f)
		creature.idealTempRangeMin = resetVariable(0.05f, 1.0f, 3.0f, 6.0f);

	creature.tolTempRangeMax = creature.idealTempRangeMax + creature.tolTempRange;
	creature.tolTempRangeMin = creature.idealTempRangeMin - creature.tolTempRange;
	if (creature.tolTempRangeMin <= 0.0f)
		creature.tolTempRangeMin = resetVariable(0.05f, 1.0f, 3.0f, 6.0f);

	creature.oxygenTolMax = creature.oxygenDemand;
	creature.oxygenTolMin = creature.oxygenDemand - creature.oxygenRange;
	if (creature.oxygenTolMin <= 0.0f)
		creature.oxygenTolMin = resetVariable(0.05f, 1.0f, 3.0f, 6.0f);

	//add litterSize and creatureWeight to geneStack.
	fillGeneElement(creature, creature.geneStack, creature.litterSize);				//geneStack element (6) - litter size
	fillGeneElement(creature, creature.geneStack, creature.creatureWeight);			//geneStack element (7) - creature weight

	//then add creatureSize and lifeSpan to geneStack.
	fillGeneElement(creature, creature.geneStack, creature.creatureSize);			//geneStack element (8) - creature size
	fillGeneElement(creature, creature.geneStack, creature.lifeSpan);				//geneStack element (9) - life span

	creature.isAlive = true;
	creature.tempIdeal = true;
	creature.tempTol = true;
	creature.oxyIdeal = true;
	creature.oxyTol = true;
}

Creature CreatureCreation::createCreatureFromGeneStack(std::vector<float> newGeneStack)
{
	//create a new creature object.
	Creature newCreature;

	//reserve its geneStack size to the newGeneStackSize, more efficient than resizing element by element.
	newCreature.geneStack.reserve(newGeneStack.size());

	//loop through and set creatures gene stack to the new gene stack.
	for (int i = 0; i < newGeneStack.size(); i++)
		newCreature.geneStack.push_back(newGeneStack.at(i));

	//create the rest of the creatures variables from this genestack.
	updateCreature(newCreature);

	//REMEMBER - in main run ft.creatureFitnessTests on these creatures to complete build, specifically threshold score and final energy demand, VERY IMPORTANT.	
	//return the newly created creature.
	return newCreature;
}

void CreatureCreation::updateCreature(Creature & creature)
{
	//Creature mutations have taken place, update the geneStack with these new values.
	//geneStack elements = e0-initialEnergyDemand / e1-idealTemp / e2-idealTempRange / e3-tolTempRange / e4-oxyenDemand / e5-oxygenRange / e6-numberOffspring / e7-lifeSpan / e8-species/creature id.
	creature.initialEnergyDemand = creature.geneStack.at(0);
	creature.idealTemp = creature.geneStack.at(1);
	creature.idealTempRange = creature.geneStack.at(2);
	creature.tolTempRange = creature.geneStack.at(3);
	creature.oxygenDemand = creature.geneStack.at(4);
	if (creature.oxygenDemand <= 0.0f)
	{	//CHOICE!!!
		//do we remove the creature if their oxygen demand is less than 0...
			//add to remove and delete list.
		//or, do we randomly pick a constrained low number?
		creature.oxygenDemand = resetVariable(1.0f, 5.0f, 15.0f, 20.0f);
	}
	creature.oxygenRange = creature.geneStack.at(5);

	//add litterSize, creatureWeight, creatureSize and lifeSpan to geneStack.
	creature.litterSize = creature.geneStack.at(6);
	creature.creatureWeight = creature.geneStack.at(7);
	//creature.creatureSize = CreatureSize(creature.geneStack.at(8));
	int tempInt = creature.geneStack.at(8);
	switch(tempInt)
	{
		case VERY_SMALL:
			creature.creatureSize = CreatureSize(VERY_SMALL);
			break;
		case SMALL:
			creature.creatureSize = CreatureSize(SMALL);
			break;
		case MEDIUM:
			creature.creatureSize = CreatureSize(MEDIUM);
			break;
		case LARGE:
			creature.creatureSize = CreatureSize(LARGE);
			break;
		case VERY_LARGE:
			creature.creatureSize = CreatureSize(VERY_LARGE);
			break;
	}
	creature.lifeSpan = creature.geneStack.at(9);

	//and finally the creature ID.
	creature.creatureID = creature.geneStack.at(10);

	creature.idealTempRangeMax = creature.idealTemp + creature.idealTempRange;
	creature.idealTempRangeMin = creature.idealTemp - creature.idealTempRange;
	if (creature.idealTempRangeMin <= 0.0f)
		creature.idealTempRangeMin = resetVariable(0.05f, 1.0f, 3.0f, 6.0f);

	creature.tolTempRangeMax = creature.idealTempRangeMax + creature.tolTempRange;
	creature.tolTempRangeMin = creature.idealTempRangeMin - creature.tolTempRange;
	if (creature.tolTempRangeMin <= 0.0f)
		creature.tolTempRangeMin = resetVariable(0.05f, 1.0f, 3.0f, 6.0f);

	creature.oxygenTolMax = creature.oxygenDemand;
	creature.oxygenTolMin = creature.oxygenDemand - creature.oxygenRange;
	if (creature.oxygenTolMin <= 0.0f)
		creature.oxygenTolMin = resetVariable(0.05f, 1.0f, 3.0f, 6.0f);
}

void CreatureCreation::addToGeneStack(std::vector<float>& geneStack, float newElement)
{
	//adds an element to the end of the gene stack.
	geneStack.insert(geneStack.end(), newElement);
}

void CreatureCreation::duplicateCreature(std::vector<Creature> &tempPopulationVec, Creature creatToDup)
{
	//BELOW FOR BACTERIA REPRODUCTION, ie 1 parent, divides into 2 parents.
	//add first child creature.
	tempPopulationVec.push_back(creatToDup);
	//do it all again for the second child creature.
	tempPopulationVec.push_back(creatToDup);
}

void CreatureCreation::duplicatePopulationVectors(std::vector<Creature> &toPopulation, std::vector<Creature> &fromPopulation)
{
	//empty the main population vector as going to refilled.
	toPopulation.clear();
	//know the size it is going to be, so reserve this size, saves having to do the whole vector 'create a new array' everytime it expands, which it potentially do A LOT here.
	toPopulation.reserve(fromPopulation.size());
	//assign() used rather than copy(), as happy for it to be set exactly the same.
	toPopulation.assign(fromPopulation.begin(), fromPopulation.end());
}

void CreatureCreation::passCreatureElement(const Creature sourceArray[], int sourceElement, Creature destinationArray[], int destinationSize)
{
	destinationArray[destinationSize - 1] = sourceArray[sourceElement];
}

void CreatureCreation::passCreatureArray(const Creature sourceArray[], Creature destinationArray[], uint32_t size)
{
	for (uint32_t i = 0; i < size; i++)
		destinationArray[i] = sourceArray[i];
}

void CreatureCreation::printCreatureVariables(const Creature creature)
{
	std::cout << "initialEnergyDemand: " << creature.initialEnergyDemand << std::endl;
	std::cout << "finalEnergyDemand: " << creature.finalEnergyDemand << std::endl;
	if(creature.initialEnergyDemand != creature.finalEnergyDemand)
		std::cout << "multipliers have been applied == TRUE" << std::endl;
	else
		std::cout << "multipliers have been applied == FALSE" << std::endl;
	std::cout << "thresholdScore" << creature.thresholdScore << std::endl;
	std::cout << "idealTemp: " << creature.idealTemp << std::endl;
	std::cout << "idealTempRange: " << creature.idealTempRange << std::endl;
	std::cout << "tolTempRange: " << creature.tolTempRange << std::endl;
	std::cout << "oxygenDemand: " << creature.oxygenDemand << std::endl;
	std::cout << "oxygenRange: " << creature.oxygenRange << std::endl;
	std::cout << "idealTempRangeMax: " << creature.idealTempRangeMax << std::endl;
	std::cout << "idealTempRangeMin: " << creature.idealTempRangeMin << std::endl;
	std::cout << "tolTempRangeMax: " << creature.tolTempRangeMax << std::endl;
	std::cout << "tolTempRangeMin: " << creature.tolTempRangeMin << std::endl;
	std::cout << "oxygenTolMin: " << creature.oxygenTolMin << std::endl;
	std::cout << "min litterSize: " << static_cast<int>(creature.litterSize) << std::endl;
	std::cout << "lifeSpan: " << creature.lifeSpan << std::endl;
	std::cout << "creatureSize: " << creature.creatureSize << std::endl;
	std::cout << "creatureWeight: " << creature.creatureWeight << std::endl;
}

float CreatureCreation::resetVariable(float minLow, float minHigh, float maxLow, float maxHigh)
{
	newMin = genFunc->uniformFloatBetween(minLow, minHigh);
	newMax = genFunc->uniformFloatBetween(maxLow, maxHigh);
	float result = genFunc->uniformFloatBetween(newMin, newMax);
	return result;
}

void CreatureCreation::fillGeneElement(Creature & creature, std::vector<float>& gene, float value)
{
	creature.geneStack.push_back(value);
}

float CreatureCreation::multiplier(float varToMulti, float multiBy)
{
	float result = varToMulti * multiBy;
	return result;
}

void CreatureCreation::plusMinusOne(int & iToChange, float & fToChange)
{
	int randNum = genFunc->uniformIntBetween(0, 5);

	if (randNum == 0) {
		iToChange = iToChange + 1;
		fToChange = fToChange - 1.0f;
	} else if(randNum == 1) {
		iToChange = iToChange - 1;
		fToChange = fToChange + 1.0f;
	} else {
		//no change, keep things the same.
	}
}

