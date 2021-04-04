#include "fitness\fullFitnessTest.h"

void FullFitnessTest::creatureFitnessTests(CREAT &creature, Environment& environment)
{
	//check that the creature is alive to do checks on in the first place.
	if (creature.isAlive)
	{
		//test one - oxygenation fitness test.
		creature.oxyIdeal = oxyFF.inRangeCheck(100.0f, creature.oxygenTolMax, environment.oxygenationRate);
		creature.oxyTol = oxyFF.inRangeCheck(creature.oxygenTolMax, creature.oxygenTolMin, environment.oxygenationRate);
		creature.isAlive = oxyFF.fitnessTest(creature.oxygenDemand, environment.oxygenationRate, creature.oxyTol);

		if (creature.isAlive)
		{
			//test two - temperature fitness test.
			creature.tempIdeal = tempFF.inRangeCheck(creature.idealTempRangeMax, creature.idealTempRangeMin, environment.temperature);
			creature.tempTol = tempFF.inRangeCheck(creature.tolTempRangeMax, creature.tolTempRangeMin, environment.temperature);
			creature.isAlive = tempFF.fitnessTest(creature.tempIdeal, creature.tempTol);

			if (creature.isAlive)
			{
				//test three - energy fitness test.
				creature.finalEnergyDemand = oxyFF.multiplier(creature.initialEnergyDemand, creature.oxyTol);
				creature.finalEnergyDemand = tempFF.multiplier(creature.initialEnergyDemand, creature.tempTol, creature.tempIdeal);
				creature.isAlive = energyFF.fitnessTest(creature.finalEnergyDemand, environment.energyAvailable);
			}
		}

		//give the creature its threshold score.
		if (creature.isAlive)
			creature.thresholdScore = genFunc->roundFloat(environment.energyAvailable - creature.finalEnergyDemand);
	}
}
