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
	creature.initialEnergyDemand = genFunc->normalFloatBetween(energyCentre, energyGauss);
	creature.initialEnergyDemand = genFunc->roundFloat(creature.initialEnergyDemand);
	if (creature.initialEnergyDemand <= 0.0f)
	{	//CHOICE!!!
		//do we remove the creature if their energy demand is less than 0...
			//add to remove and delete list.
		//or, do we randomly pick a constrained low number?
		creature.initialEnergyDemand = resetVariable(1.0f, 20.0f, 60.0f, 80.0f);
	}
	fillGeneElement(creature, creature.geneStack, creature.initialEnergyDemand);

	creature.idealTemp = genFunc->normalFloatBetween(idealTempCentre, idealTempGuass);
	creature.idealTemp = genFunc->roundFloat(creature.idealTemp);
	fillGeneElement(creature, creature.geneStack, creature.idealTemp);

	creature.idealTempRange = genFunc->uniformFloatBetween(idealTempRangeMin, idealTempRangeMax);
	fillGeneElement(creature, creature.geneStack, creature.idealTempRange);

	creature.tolTempRange = genFunc->uniformFloatBetween(tolTempRangeMin, tolTempRangeMax);
	fillGeneElement(creature, creature.geneStack, creature.tolTempRange);

	creature.oxygenDemand = genFunc->normalFloatBetween(oxyCentre, oxyGauss);
	creature.oxygenDemand = genFunc->roundFloat(creature.oxygenDemand);
	if (creature.oxygenDemand <= 0.0f)
	{	//CHOICE!!!
		//do we remove the creature if their oxygen demand is less than 0...
			//add to remove and delete list.
		//or, do we randomly pick a constrained low number?
		creature.oxygenDemand = resetVariable(1.0f, 5.0f, 15.0f, 20.0f);
	}
	fillGeneElement(creature, creature.geneStack, creature.oxygenDemand);

	creature.oxygenRange = genFunc->uniformFloatBetween(oxyRangeMin, oxyRangeMax);
	fillGeneElement(creature, creature.geneStack, creature.oxygenRange);

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

	creature.offspringNumber = genFunc->uniformFloatBetween(offspringMin, offspringMax);
	fillGeneElement(creature, creature.geneStack, creature.offspringNumber);

	creature.lifeSpan = genFunc->uniformIntBetween(lifeMin, lifeMax);
	fillGeneElement(creature, creature.geneStack, creature.lifeSpan);

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

	creature.offspringNumber = creature.geneStack.at (6);
	creature.lifeSpan = creature.geneStack.at(7);
	creature.creatureID = creature.geneStack.at(8);

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
	std::cout << "minimum offspring to have: " << static_cast<int>(creature.offspringNumber) << std::endl;
	std::cout << "lifeSpan: " << creature.lifeSpan << std::endl;
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
