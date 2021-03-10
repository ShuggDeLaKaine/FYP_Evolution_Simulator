/** \file creatures.h */
#pragma once
#include <iostream>
#include <vector>
#include "fitness/fitnessHeaderList.h"
#include "core/generalFunctions.h"


struct Creature
{
	//energy vars.
	float energyDemand;

	//oxygenation vars
	float oxygenDemand;
	float oxygenRange;
	float oxygenTolMin;
	float oxygenTolMax;

	//ideal temperature vars.
	float idealTemp;
	float idealTempRange;
	float idealTempRangeMin;
	float idealTempRangeMax;

	//tolerated temperature vars.
	float tolTempRange;
	float tolTempRangeMin;
	float tolTempRangeMax;

	//bools for conditions.
	bool isAlive;
	bool tempIdeal;
	bool tempTol;
	bool oxyIdeal;
	bool oxyTol;

	int creatureNumber;
};

struct CreatureSettings
{
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
};

/*	\class CreatureCreation
*	\brief Class...
*/
class CreatureCreation
{
public:
	CreatureCreation() {};					//!< default constructor.
	~CreatureCreation();					//!< default deconstructor.

	void creatureCreation(Creature &creature, float energyCentre, float energyGauss, float idealTempCentre, float idealTempGuass,
		float idealTempRangeMin, float idealTempRangeMax, float tolTempRangeMin, float tolTempRangeMax, float oxyCentre, float oxyGauss,
		float oxyRangeMin, float oxyRangeMax);

	void createInitialPopulation(Creature &creature, const uint32_t populationSize);

	void passCreatureElement(const Creature sourceArray[], int sourceElement, Creature destinationArray[], int destinationSize);
	void passCreatureArray(const Creature sourceArray[], Creature destinationArray[], int size);

	void printCreatureVariables(const Creature creature);
	float resetVariable(float minLow, float minHigh, float maxLow, float maxHigh);
private:
	std::shared_ptr<GeneralFunctions> genFunc;
	CreatureSettings cs;
	float newMin;
	float newMax;
};