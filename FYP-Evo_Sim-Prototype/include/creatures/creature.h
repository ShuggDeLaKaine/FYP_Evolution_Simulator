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
	uint32_t creatureID;			//!< creature ID (basically name)
	std::vector<float> geneStack;	//!< vector containing the core gene values.
	
	float thresholdScore;			//!< score used to determine reproduction chances.

	//energy vars.
	float initialEnergyDemand;		//!< initial energy demand of creature.
	float finalEnergyDemand;		//!< final energy demand of creature, with mutlipliers applying to this.

	//oxygenation vars
	float oxygenDemand;				//!< oxygen demand value.
	float oxygenRange;				//!< range of oxygen to either side of the oxygen demand.
	float oxygenTolMin;				//!< oxygen toleration minimum, determined with oxygen demand and range.
	float oxygenTolMax;				//!< oxygen toleration maximum, determined with oxygen demand and range.

	//ideal temperature vars.		
	float idealTemp;				//!< ideal temperature value.
	float idealTempRange;			//!< ideal temperature range to either side of the ideal temperature.
	float idealTempRangeMin;		//!< ideal temperature minimum, determined with temperature demand and range.
	float idealTempRangeMax;		//!< ideal temperature maximum, determined with temperature demand and range.

	//tolerated temperature vars.	 
	float tolTempRange;				//!< tolerated temperature range value, to be added on top of the ideal temperature values (creature can survive here but with a modifier to energy demands).
	float tolTempRangeMin;			//!< tolerated temperature minimum, determined with ideal temperatures and tolerated range.
	float tolTempRangeMax;			//!< tolerated temperature maximum, determined with ideal temperatures and tolerated range.

	//bools for conditions.
	bool isAlive;					//!< determines whether creature is alive.
	bool tempIdeal;					//!< determines whether creature in ideal temperature range.
	bool tempTol;					//!< determines whether creature in tolerated temperature range.
	bool oxyIdeal;					//!< determines whether creature in ideal oxygen range.
	bool oxyTol;					//!< determines whether creature in tolerated oxygen range.
	bool paired = false;			//!< determines in reproduction stage whether creature has been paired up, initialised to false;

	uint32_t creatureNumber;		//!< creation number within species.
	uint32_t generationNumber = 1;	//!< initialise to 1, as the first lot of seed population that survive will be generation 1.
	uint32_t childNumber = 0;		//!< initialise to 0, as above, but 0 because not a child creature, an original seed one.
};

struct CreatureSettings
{
	float energyCentre = 300.0f;		//!< 
	float energyGauss = 100.0f;			//!< 
	float idealTempCentre = 15.0f;		//!< 
	float idealTempGuass = 5.0f;		//!< 
	float idealTempRangeMin = 0.25f;	//!< 
	float idealTempRangeMax = 2.0f;		//!< 
	float tolTempRangeMin = 0.5f;		//!< 
	float tolTempRangeMax = 4.0f;		//!< 
	float oxyCentre = 50.0f;			//!< 
	float oxyGauss = 25.0f;				//!< 
	float oxyRangeMin = 1.0f;			//!< 
	float oxyRangeMax = 25.0f;			//!< 
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
		float oxyRangeMin, float oxyRangeMax);				//!< create a creature, used in the seeding stage to randomly create creatures.

	void updateCreatureWithMutations(Creature &creature);	//!< update all the creatures variables with the new mutated values from the gene stack.

	void duplicateCreature(std::vector<Creature> &tempPopulationVec, Creature creatToDup);	//!< duplicate a creature.
	void duplicatePopulationVectors(std::vector<Creature> &toPopulation, std::vector<Creature> &fromPopulation);	//!< move the temp vector into the main vector.

	void passCreatureElement(const Creature sourceArray[], int sourceElement, Creature destinationArray[], int destinationSize);	//!< pass an arrays element.
	void passCreatureArray(const Creature sourceArray[], Creature destinationArray[], uint32_t size);	//!< pass the creatures array on.

	float resetVariable(float minLow, float minHigh, float maxLow, float maxHigh);		//!< reset a variable.
	void printCreatureVariables(const Creature creature);								//!< print the creatures variables to console.

private:
	void fillGeneElement(Creature &creature, std::vector<float> &gene, float value);	//!< fill a gene stack from variables. 

	CreatureSettings cs;						//!< ref to the creature settings.
	std::shared_ptr<GeneralFunctions> genFunc;	//!< ptr to the general functions.

	float newMin;								//!< used in reset variable, minimum range.
	float newMax;								//!< used in reset variable, maximum range.
};