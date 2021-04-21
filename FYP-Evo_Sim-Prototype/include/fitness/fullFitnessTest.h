/** \file fullFitnessTest.h */
#pragma once
#include "creatures/creature.h"
#include "environments/environment.h"
#include "fitness/energyFitnessTest.h"
#include "fitness/temperatureFitnessTest.h"
#include "fitness/oxygenFitnessTest.h"
#include "core/generalFunctions.h"


typedef struct Creature CREAT;

/*	\class FullFitnessTest
*	\brief Class...
*/
class FullFitnessTest
{
public:
	void creatureFitnessTests(CREAT &creature, Environment &environment);	//!< function to run a full run of all fitness tests between a creature and an environment.
	void creatureFitnessTests(CREAT &creature, Environment &environment, float energyReduction);	//!< function to run a full run of all fitness tests between a creature and an environment, takes an energy reduction value, used in competition fitness tests.
private:
	EnergyFitnessTest energyFF;			//!< ref to energy fitness tests.
	TemperatureFitnessTest tempFF;		//!< ref to temperature fitness tests.
	OxygenFitnessTest oxyFF;			//!< ref to oxygen fitness tests.
	std::shared_ptr<GeneralFunctions> genFunc;	//!< pointer ref to general functions class.
};