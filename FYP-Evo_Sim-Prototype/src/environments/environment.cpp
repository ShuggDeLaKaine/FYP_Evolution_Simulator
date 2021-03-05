/** \file environment.cpp */
#include "environments/environment.h"


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

	//need to set an environment ID too... maybe?
	count++;
	envir.ID = count;
	std::cout << "set environments ID to: " << envir.ID << std::endl;
}
