/** \file fullFitnessTest.h */
#pragma once
#include "creatures/creature.h"
#include "environments/environment.h"
#include "fitness/energyFitnessTest.h"
#include "fitness/temperatureFitnessTest.h"
#include "fitness/oxygenFitnessTest.h"

typedef struct Creature CREAT;

class FullFitnessTest
{
public:
	void creatureFitnessTests(CREAT &creature, Environment &environment);
private:
	EnergyFitnessTest energyFF;
	TemperatureFitnessTest tempFF;
	OxygenFitnessTest oxyFF;
};