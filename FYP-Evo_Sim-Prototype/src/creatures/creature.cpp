/** \file creatures.cpp */
#include "creatures/creature.h"
#include "..\..\include\creatures\creature.h"


CreatureCreation::~CreatureCreation()
{

}

void CreatureCreation::creatureCreation(Creature & creature, float energyCentre, float energyGauss, float idealTempCentre, float idealTempGuass, float idealTempRangeMin, float idealTempRangeMax, float tolTempRangeMin, float tolTempRangeMax, float oxyCentre, float oxyGauss, float oxyRangeMin, float oxyRangeMax)
{
	creature.energyDemand = genFunc->normalFloatBetween(energyCentre, energyGauss);
	creature.energyDemand = genFunc->roundFloat(creature.energyDemand);
	if (creature.energyDemand <= 0.0f)
	{	//CHOICE!!!
		//do we remove the creature if their energy demand is less than 0...
			//add to remove and delete list.
		//or, do we randomly pick a constrained low number?
		creature.energyDemand = resetVariable(1.0f, 20.0f, 60.0f, 80.0f);
	}

	creature.idealTemp = genFunc->normalFloatBetween(idealTempCentre, idealTempGuass);
	creature.idealTemp = genFunc->roundFloat(creature.idealTemp);
	creature.idealTempRange = genFunc->uniformFloatBetween(idealTempRangeMin, idealTempRangeMax);
	creature.tolTempRange = genFunc->uniformFloatBetween(tolTempRangeMin, tolTempRangeMax);
	creature.oxygenDemand = genFunc->normalFloatBetween(oxyCentre, oxyGauss);
	creature.oxygenDemand = genFunc->roundFloat(creature.oxygenDemand);
	if (creature.oxygenDemand <= 0.0f)
	{	//CHOICE!!!
		//do we remove the creature if their oxygen demand is less than 0...
			//add to remove and delete list.
		//or, do we randomly pick a constrained low number?
		creature.oxygenDemand = resetVariable(1.0f, 5.0f, 15.0f, 20.0f);
	}
	creature.oxygenRange = genFunc->uniformFloatBetween(oxyRangeMin, oxyRangeMax);

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

	creature.isAlive = true;
	creature.tempIdeal = true;
	creature.tempTol = true;
	creature.oxyIdeal = true;
	creature.oxyTol = true;
}

void CreatureCreation::createInitialPopulation(Creature &creature, const uint32_t populationSize)
{
	//struct Creature creat[10000];


}

void CreatureCreation::passCreatureElement(const Creature sourceArray[], int sourceElement, Creature destinationArray[], int destinationSize)
{
	destinationArray[destinationSize - 1] = sourceArray[sourceElement];
}

void CreatureCreation::passCreatureArray(const Creature sourceArray[], Creature destinationArray[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		destinationArray[i] = sourceArray[i];
	}
}

void CreatureCreation::printCreatureVariables(const Creature creature)
{
	std::cout << "energyDemand: " << creature.energyDemand << std::endl;
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
}

float CreatureCreation::resetVariable(float minLow, float minHigh, float maxLow, float maxHigh)
{
	newMin = genFunc->uniformFloatBetween(minLow, minHigh);
	newMax = genFunc->uniformFloatBetween(maxLow, maxHigh);
	float result = genFunc->uniformFloatBetween(newMin, newMax);
	return result;
}