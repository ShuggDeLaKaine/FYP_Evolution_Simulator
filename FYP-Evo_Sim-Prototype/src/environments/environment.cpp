/** \file environment.cpp */
#include "environments/environment.h"


EnvironmentCreation::EnvironmentCreation()
{

}

EnvironmentCreation::~EnvironmentCreation()
{

}

void EnvironmentCreation::environmentCreation(Environment& envir, float energyMin, float energyMax, float tempMin, float tempMax, float oxygenMin, float oxygenMax)
{
	//set energy level.
	envir.energyAvailable = setEnergyAvailable(energyMin, energyMax);
	std::cout << "set environments energy level to: " << envir.energyAvailable << std::endl;

	//set temperature level.
	envir.temperature = setEnergyAvailable(tempMin, tempMax);
	std::cout << "set environments temperature level to: " << envir.temperature << std::endl;

	//set oxygen level.
	envir.oxygenationRate = setEnergyAvailable(oxygenMin, oxygenMax);
	std::cout << "set environments oxygen level to: " << envir.oxygenationRate << std::endl;

	//set weight capacity.
	envir.fEnvironmentCapacity = setEnvironmentalCapacity(envir.energyAvailable, envir.fCapacityMultiplier);

	//need to set an environment ID too... maybe?
	count++;
	envir.ID = count;
	std::cout << "set environments ID to: " << envir.ID << std::endl;
}


void Environment::updatePopulationWeight(AllSpecies allSpecies)
{
	for (int i = 0; i < allSpecies.aliveSpeciesVec.size(); i++)
	{
		//iterate through creatures within the species
		for (int j = 0; j < allSpecies.aliveSpeciesVec.at(i).speciesMembership.size(); j++)
		{
			fPopulationWeight += allSpecies.aliveSpeciesVec.at(i).speciesMembership.at(j).creatureWeight;
		}
	}
}
