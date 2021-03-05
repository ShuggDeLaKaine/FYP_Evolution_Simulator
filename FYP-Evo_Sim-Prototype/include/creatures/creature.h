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

class CreatureCreation
{
public:
	CreatureCreation() {};							//!< default constructor
	CreatureCreation(Creature &creature, float energyCentre, float energyGauss, float idealTempCentre, float idealTempGuass,
		float idealTempRangeMin, float idealTempRangeMax, float tolTempRangeMin, float tolTempRangeMax, float oxyCentre, float oxyGauss,
		float oxyRangeMin, float oxyRangeMax);		//!< 
	~CreatureCreation();

	void printCreatureVariables(Creature &creature);
	float resetVariable(float minLow, float minHigh, float maxLow, float maxHigh);
private:
	std::shared_ptr<GeneralFunctions> genFunc;
	float newMin;
	float newMax;
};