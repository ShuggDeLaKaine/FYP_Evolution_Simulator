/** \file creatures.h */
#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "fitness/fitnessHeaderList.h"
#include "core/generalFunctions.h"


struct Creature
{
	uint32_t creatureID;
	std::vector<float> geneStack;

	//energy vars.
	float initialEnergyDemand;		//!< initial energy demand of creature.
	float finalEnergyDemand;		//!< final energy demand of creature, with mutlipliers applying to this.

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

	uint32_t creatureNumber;
	uint32_t generationNumber = 1;		//!< initialise to 1, as the first lot of seed population that survive will be generation 1.
	uint32_t childNumber = 0;			//!< initialise to 0, as above, but 0 because not a child creature, an original seed one.
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

	void updateCreatureWithMutations(Creature &creature);

	void duplicateCreature(std::vector<Creature> &tempPopulationVec, Creature creatToDup);
	void duplicatePopulationVectors(std::vector<Creature> &toPopulation, std::vector<Creature> &fromPopulation);		//!< move the temp vector into the main vector.

	void passCreatureElement(const Creature sourceArray[], int sourceElement, Creature destinationArray[], int destinationSize);
	void passCreatureArray(const Creature sourceArray[], Creature destinationArray[], uint32_t size);

	void printCreatureVariables(const Creature creature);
	float resetVariable(float minLow, float minHigh, float maxLow, float maxHigh);
private:
	CreatureSettings cs;
	std::shared_ptr<GeneralFunctions> genFunc;
	void fillGeneElement(Creature &creature, std::vector<float> &gene, float value);
	float newMin;
	float newMax;
};