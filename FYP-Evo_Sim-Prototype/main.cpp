/** \file main.cpp */

#include <iostream>
#include <vector>


struct Environment
{
	float energy_available;
	float temperature;
};

struct Creature
{
	//energy vars.
	float energy_demand;

	//ideal temperature vars.
	float ideal_temp;
	float ideal_temp_range;
	float ideal_temp_range_min;
	float ideal_temp_range_max;

	//tolerated temperature vars.
	float tol_temp_range;
	float tol_temp_range_min;
	float tol_temp_range_max;

	//bools for conditions.
	bool alive;
	bool temp_ideal;
	bool temp_tol;
};


bool energyFitnessTest(float creature, float environment);
bool temperatureFitnessTest(float creEnergy, float idealMax, float idealMin, float tolMax, float tolMin, float envTemp, bool ideal, bool tolerated);
bool idealTemperatureCheck(float idealMax, float idealMin, float envTemp);
bool toleratedTemperatureCheck(float tolMax, float tolMin, float envTemp);
bool surviveTemperature(bool ideal, bool tolerated);
int toleratedTemperatureEnergyMultiplier(float creEnergy, bool ideal, bool tolerated);


int main()
{

	struct Environment envir[1];
	struct Creature creat[7];

	envir[0].energy_available = 500.0f;
	envir[0].temperature = 12.0f;


#pragma region TEST_ENERGY_AVAILABLE.
	//creature 0 - should SURVIVE ideally suited to environment 0.
	creat[0].energy_demand = 400.0f;		//in range of environ energy.
	creat[0].ideal_temp = 12.0f;			//same as environ temp.
	creat[0].ideal_temp_range = 1.0f;
	creat[0].tol_temp_range = 1.0f;

	creat[0].ideal_temp_range_max = creat[0].ideal_temp + creat[0].ideal_temp_range;
	creat[0].ideal_temp_range_min = creat[0].ideal_temp - creat[0].ideal_temp_range;
	creat[0].tol_temp_range_max = creat[0].ideal_temp_range_max + creat[0].tol_temp_range;
	creat[0].tol_temp_range_min = creat[0].ideal_temp_range_min - creat[0].tol_temp_range;

	creat[0].alive = true;
	creat[0].temp_ideal = true;
	creat[0].temp_tol = true;

	//creature 1 - should NOT SURVIVE be suited to environment 0.
	creat[1].energy_demand = 650.0f;		//over the range, not even environ energy.
	creat[1].ideal_temp = 12.0f;			//same as environ temp.
	creat[1].ideal_temp_range = 1.0f;
	creat[1].tol_temp_range = 1.0f;

	creat[1].ideal_temp_range_max = creat[1].ideal_temp + creat[1].ideal_temp_range;
	creat[1].ideal_temp_range_min = creat[1].ideal_temp - creat[1].ideal_temp_range;
	creat[1].tol_temp_range_max = creat[1].ideal_temp_range_max + creat[1].tol_temp_range;
	creat[1].tol_temp_range_min = creat[1].ideal_temp_range_min - creat[1].tol_temp_range;

	creat[1].alive = true;
	creat[1].temp_ideal = true;
	creat[1].temp_tol = true;
#pragma endregion

#pragma region TEST_TEMPERATURE
	//creature 2 - should SURVIVE suited to environment 0.
	creat[2].energy_demand = 200.0f;		//over the range, not even environ energy.
	creat[2].ideal_temp = 12.0f;			//same as environ temp.
	creat[2].ideal_temp_range = 1.0f;		//
	creat[2].tol_temp_range = 1.0f;			//

	creat[2].ideal_temp_range_max = creat[2].ideal_temp + creat[2].ideal_temp_range;
	creat[2].ideal_temp_range_min = creat[2].ideal_temp - creat[2].ideal_temp_range;
	creat[2].tol_temp_range_max = creat[2].ideal_temp_range_max + creat[2].tol_temp_range;
	creat[2].tol_temp_range_min = creat[2].ideal_temp_range_min - creat[2].tol_temp_range;

	creat[2].alive = true;
	creat[2].temp_ideal = true;
	creat[2].temp_tol = true;

	//creature 3 - should NOT SURVIVE be suited to environment 0.
	creat[3].energy_demand = 200.0f;			//over the range, not even environ energy.
	creat[3].ideal_temp = 20.0f;				//much higher than environ temp.
	creat[3].ideal_temp_range = 1.0f;
	creat[3].tol_temp_range = 1.0f;

	creat[3].ideal_temp_range_max = creat[3].ideal_temp + creat[3].ideal_temp_range;
	creat[3].ideal_temp_range_min = creat[3].ideal_temp - creat[3].ideal_temp_range;
	creat[3].tol_temp_range_max = creat[3].ideal_temp_range_max + creat[3].tol_temp_range;
	creat[3].tol_temp_range_min = creat[3].ideal_temp_range_min - creat[3].tol_temp_range;

	creat[3].alive = true;
	creat[3].temp_ideal = true;
	creat[3].temp_tol = true;
#pragma endregion

#pragma region TEST_TEMPERATURE_TOLERANCE_RANGES.
	//creature 4 - should SURVIVE, instead ideal temperature range.
	creat[4].energy_demand = 200.0f;		//in range of environ energy.
	creat[4].ideal_temp = 11.5f;			//off environ temp.
	creat[4].ideal_temp_range = 1.0f;		//
	creat[4].tol_temp_range = 2.0f;			//

	creat[4].ideal_temp_range_max = creat[4].ideal_temp + creat[4].ideal_temp_range;
	creat[4].ideal_temp_range_min = creat[4].ideal_temp - creat[4].ideal_temp_range;
	creat[4].tol_temp_range_max = creat[4].ideal_temp_range_max + creat[4].tol_temp_range;
	creat[4].tol_temp_range_min = creat[4].ideal_temp_range_min - creat[4].tol_temp_range;

	creat[4].alive = true;
	creat[4].temp_ideal = true;
	creat[4].temp_tol = true;

	//creature 5 - should SURVIVE, inside tolerated temperature range and still enough energy remaining after multiplier.
	creat[5].energy_demand = 200.0f;		//in range of environ energy.
	creat[5].ideal_temp = 10.0f;			//off environ temp.
	creat[5].ideal_temp_range = 1.0f;		//
	creat[5].tol_temp_range = 2.0f;			//

	creat[5].ideal_temp_range_max = creat[5].ideal_temp + creat[5].ideal_temp_range;
	creat[5].ideal_temp_range_min = creat[5].ideal_temp - creat[5].ideal_temp_range;
	creat[5].tol_temp_range_max = creat[5].ideal_temp_range_max + creat[5].tol_temp_range;
	creat[5].tol_temp_range_min = creat[5].ideal_temp_range_min - creat[5].tol_temp_range;

	creat[5].alive = true;
	creat[5].temp_ideal = true;
	creat[5].temp_tol = true;

	//creature 6 - should NOT SURVIVE, inside tolerated temperature range but NOT enough energy remaining after multiplier.
	creat[6].energy_demand = 450.0f;		//in range of environ energy.
	creat[6].ideal_temp = 10.0f;			//a little off environ temp.
	creat[6].ideal_temp_range = 1.0f;		//
	creat[6].tol_temp_range = 2.0f;			//

	creat[6].ideal_temp_range_max = creat[6].ideal_temp + creat[6].ideal_temp_range;
	creat[6].ideal_temp_range_min = creat[6].ideal_temp - creat[6].ideal_temp_range;
	creat[6].tol_temp_range_max = creat[6].ideal_temp_range_max + creat[6].tol_temp_range;
	creat[6].tol_temp_range_min = creat[6].ideal_temp_range_min - creat[6].tol_temp_range;

	creat[6].alive = true;
	creat[6].temp_ideal = true;
	creat[6].temp_tol = true;

#pragma endregion

#pragma region TESTING 1 - TWO CREATURES ON ENERGY LEVELS.
	//TESTING - energy levels.
	creat[0].alive = energyFitnessTest(creat[0].energy_demand, envir[0].energy_available);
		std::cout << "Did Creature 0 survive?   "; 
	if(creat[0].alive)
		std::cout << "   YES! CREATURE 0 SURVIVED!" << std::endl;
	else
		std::cout << "   NO! CREATURE 0 IS DEAD!" << std::endl;

	creat[1].alive = energyFitnessTest(creat[1].energy_demand, envir[0].energy_available);
	std::cout << "Did Creature 1 survive?   ";
	if (creat[1].alive)
		std::cout << "   YES! CREATURE 1 SURVIVED!" << std::endl;
	else
		std::cout << "   NO! CREATURE 1 IS DEAD!" << std::endl;
#pragma endregion

#pragma region TESTING 2 - TWO CREATURES ON TEMPERATURE LEVELS
	//TESTING - temperature levels.
	creat[2].temp_ideal = idealTemperatureCheck(creat[2].ideal_temp_range_max, creat[2].ideal_temp_range_min, envir[0].temperature);
	creat[2].temp_tol = toleratedTemperatureCheck(creat[2].tol_temp_range_max, creat[2].tol_temp_range_min, envir[0].temperature);
	creat[2].alive = surviveTemperature(creat[2].temp_ideal, creat[2].temp_tol);
	if (creat[2].alive)
	{
		creat[2].energy_demand = toleratedTemperatureEnergyMultiplier(creat[2].energy_demand, creat[4].temp_ideal, creat[2].temp_tol);
		creat[2].alive = energyFitnessTest(creat[2].energy_demand, envir[0].energy_available);
	}
	std::cout << "Did Creature 2 survive?   "; 
	if(creat[2].alive)
		std::cout << "   YES! CREATURE 2 SURVIVED!" << std::endl;
	else
		std::cout << "   NO! CREATURE 2 IS DEAD!" << std::endl;
	

	creat[3].temp_ideal = idealTemperatureCheck(creat[3].ideal_temp_range_max, creat[3].ideal_temp_range_min, envir[0].temperature);
	creat[3].temp_tol = toleratedTemperatureCheck(creat[3].tol_temp_range_max, creat[3].tol_temp_range_min, envir[0].temperature);
	creat[3].alive = surviveTemperature(creat[3].temp_ideal, creat[3].temp_tol);
	if(creat[3].alive)
	{
		creat[3].energy_demand = toleratedTemperatureEnergyMultiplier(creat[3].energy_demand, creat[4].temp_ideal, creat[3].temp_tol);
		creat[3].alive = energyFitnessTest(creat[3].energy_demand, envir[0].energy_available);
	}
	std::cout << "Did Creature 3 survive?   ";
	if (creat[3].alive)
		std::cout << "   YES! CREATURE 3 SURVIVED!" << std::endl;
	else
		std::cout << "   NO! CREATURE 3 IS DEAD!" << std::endl;
#pragma endregion

#pragma region TESTING 3 - THREE CREATURES FOR TEMP TOLERANCE AND ENERGY DEMAND MODIFIERS
	//TESTING - temperature tolerance and energy demand multiplier.
	creat[4].temp_ideal = idealTemperatureCheck(creat[4].ideal_temp_range_max, creat[4].ideal_temp_range_min, envir[0].temperature);
	creat[4].temp_tol = toleratedTemperatureCheck(creat[4].tol_temp_range_max, creat[4].tol_temp_range_min, envir[0].temperature);
	creat[4].alive = surviveTemperature(creat[4].temp_ideal, creat[4].temp_tol);
	if (creat[4].alive)
	{
		creat[4].energy_demand = toleratedTemperatureEnergyMultiplier(creat[4].energy_demand, creat[4].temp_ideal, creat[4].temp_tol);
		creat[4].alive = energyFitnessTest(creat[4].energy_demand, envir[0].energy_available);
	}
	std::cout << "Did Creature 4 survive?   ";
	if (creat[4].alive)
		std::cout << "   YES! CREATURE 4 SURVIVED!" << std::endl;
	else
		std::cout << "   NO! CREATURE 4 IS DEAD!" << std::endl;

	creat[5].temp_ideal = idealTemperatureCheck(creat[5].ideal_temp_range_max, creat[5].ideal_temp_range_min, envir[0].temperature);
	creat[5].temp_tol = toleratedTemperatureCheck(creat[5].tol_temp_range_max, creat[5].tol_temp_range_min, envir[0].temperature);
	creat[5].alive = surviveTemperature(creat[5].temp_ideal, creat[5].temp_tol);
	if (creat[5].alive)
	{
		creat[5].energy_demand = toleratedTemperatureEnergyMultiplier(creat[5].energy_demand, creat[5].temp_ideal, creat[5].temp_tol);
		creat[5].alive = energyFitnessTest(creat[5].energy_demand, envir[0].energy_available);
	}
	std::cout << "Did Creature 5 survive?   ";
	if (creat[5].alive)
		std::cout << "   YES! CREATURE 5 SURVIVED!" << std::endl;
	else
		std::cout << "   NO! CREATURE 5 IS DEAD!" << std::endl;

	creat[6].temp_ideal = idealTemperatureCheck(creat[6].ideal_temp_range_max, creat[6].ideal_temp_range_min, envir[0].temperature);
	creat[6].temp_tol = toleratedTemperatureCheck(creat[6].tol_temp_range_max, creat[6].tol_temp_range_min, envir[0].temperature);
	creat[6].alive = surviveTemperature(creat[6].temp_ideal, creat[6].temp_tol);
	if (creat[6].alive)
	{
		creat[6].energy_demand = toleratedTemperatureEnergyMultiplier(creat[6].energy_demand, creat[6].temp_ideal, creat[6].temp_tol);
		creat[6].alive = energyFitnessTest(creat[6].energy_demand, envir[0].energy_available);
	}
	std::cout << "Did Creature 6 survive?   ";
	if (creat[6].alive)
		std::cout << "   YES! CREATURE 6 SURVIVED!" << std::endl;
	else
		std::cout << "   NO! CREATURE 6 IS DEAD!" << std::endl;
#pragma endregion


}

//function to determine energy fitness test.
bool energyFitnessTest(float creatEnergy, float envEnergy)
{
	bool survive = true;

	float cre_energy_demand = creatEnergy;
	float envir_energy_available = envEnergy;

	if (cre_energy_demand > envir_energy_available)
		survive = false;

	return survive;
}

//function combining the various parts of the temperature checks
bool temperatureFitnessTest(float creEnergy, float idealMax, float idealMin, float tolMax, float tolMin, float envTemp, bool ideal, bool tolerated)
{
	bool survive = true;

	bool inIdeal = ideal;
	bool inTolerated = tolerated;

	float environTemp = envTemp;
	float creatIdealTempMax = idealMax;
	float creatIdealTempMin = idealMin;
	float creatTolTempMax = tolMax;
	float creatTolTempMin = tolMin;

	//check whether in ideal temperature range.
	if (environTemp <= creatIdealTempMax
		&& environTemp >= creatIdealTempMin)
		inIdeal = true;
	else
		inIdeal = false;

	if (environTemp <= creatTolTempMax
		&& environTemp >= creatTolTempMin)
		tolerated = true;
	else
		tolerated = false;

	//check whether can survive in this temperature.
	if (!inIdeal && !inTolerated)
		survive = false;

	//return whether they survived.
	return survive;
}

//function to determine whether in ideal temperature range fitness check.
bool idealTemperatureCheck(float idealMax, float idealMin, float envTemp)
{
	bool ideal = true;

	float creatIdealTempMax = idealMax;
	float creatIdealTempMin = idealMin;
	float environTemp = envTemp;

	if (environTemp <= creatIdealTempMax
		&& environTemp >= creatIdealTempMin)
		ideal = true;
	else
		ideal = false;

	return ideal;
}

//function to determine whether in tolerated temperature range fitness check.
bool toleratedTemperatureCheck(float tolMax, float tolMin, float envTemp)
{
	bool tolerated = true;

	float creatTolTempMax = tolMax;
	float creatTolTempMin = tolMin;
	float environTemp = envTemp;

	if (environTemp <= creatTolTempMax
		&& environTemp >= creatTolTempMin)
		tolerated = true;
	else
		tolerated = false;

	return tolerated;
}

//function to determine whether creature can survive temperature.
bool surviveTemperature(bool ideal, bool tolerated)
{
	bool survive = true;
	bool inIdeal = ideal;
	bool inTolerated = tolerated;

	if (!inIdeal && !inTolerated)
		survive = false;

	return survive;
}

//function to apply multiplier to energy demand if in temperature tolerance range. 
int toleratedTemperatureEnergyMultiplier(float creEnergy, bool ideal, bool tolerated)
{
	int result = creEnergy;

	if (!ideal && tolerated)
	{
		result = result * 1.5;
	}

	return result;
}
