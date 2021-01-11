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



int main()
{

	struct Environment envir[1];
	struct Creature creat[8];

	envir[0].energy_available = 500.0f;
	envir[0].temperature = 12.0f;

#pragma region TEST_ENERGY_AVAILABLE.
	//creature 0 - should be ideally suited to environment 0.
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

	//creature 1 - should NOT be suited to environment 0.
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
	//creature 2 - should be suited to environment 0.
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

	//creature 3 - should NOT be suited to environment 0.
	creat[3].energy_demand = 200.0f;				//over the range, not even environ energy.
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
	//creature 4 - should survive, environ temp within tolerance range AND despite energy demand mulitplier, will still be enough energy available to survive.
	creat[4].energy_demand = 200.0f;		//in range of environ energy.
	creat[4].ideal_temp = 10.0f;			//off environ temp.
	creat[4].ideal_temp_range = 3.0f;		//
	creat[4].tol_temp_range = 0.0f;			//

	creat[4].ideal_temp_range_max = creat[4].ideal_temp + creat[4].ideal_temp_range;
	creat[4].ideal_temp_range_min = creat[4].ideal_temp - creat[4].ideal_temp_range;
	creat[4].tol_temp_range_max = creat[4].ideal_temp_range_max + creat[4].tol_temp_range;
	creat[4].tol_temp_range_min = creat[4].ideal_temp_range_min - creat[4].tol_temp_range;

	creat[4].alive = true;
	creat[4].temp_ideal = true;
	creat[4].temp_tol = true;

	//creature 5 - should NOT survive, environ temp not within the tolerance range.
	creat[5].energy_demand = 200.0f;		//in range of environ energy.
	creat[5].ideal_temp = 10.0f;			//off environ temp.
	creat[5].ideal_temp_range = 1.0f;		//
	creat[5].tol_temp_range = 0.0f;			//

	creat[5].ideal_temp_range_max = creat[5].ideal_temp + creat[5].ideal_temp_range;
	creat[5].ideal_temp_range_min = creat[5].ideal_temp - creat[5].ideal_temp_range;
	creat[5].tol_temp_range_max = creat[5].ideal_temp_range_max + creat[5].tol_temp_range;
	creat[5].tol_temp_range_min = creat[5].ideal_temp_range_min - creat[5].tol_temp_range;

	creat[5].alive = true;
	creat[5].temp_ideal = true;
	creat[5].temp_tol = true;

	//creature 6 - should NOT survive; inside tolerance range but multiplier to energy demand will take out of environmental energy limit.
	creat[6].energy_demand = 450.0f;		//in range of environ energy.
	creat[6].ideal_temp = 10.0f;			//a little off environ temp.
	creat[6].ideal_temp_range = 3.0f;		//
	creat[6].tol_temp_range = 0.0f;			//

	creat[6].ideal_temp_range_max = creat[6].ideal_temp + creat[6].ideal_temp_range;
	creat[6].ideal_temp_range_min = creat[6].ideal_temp - creat[6].ideal_temp_range;
	creat[6].tol_temp_range_max = creat[6].ideal_temp_range_max + creat[6].tol_temp_range;
	creat[6].tol_temp_range_min = creat[6].ideal_temp_range_min - creat[6].tol_temp_range;

	creat[6].alive = true;
	creat[6].temp_ideal = true;
	creat[6].temp_tol = true;

	//creature 7 - should NOT survive; inside tolerance range but multiplier to energy demand will take out of environmental energy limit.
	creat[7].energy_demand = 450.0f;		//in range of environ energy.
	creat[7].ideal_temp = 10.0f;			//a little off environ temp.
	creat[7].ideal_temp_range = 3.0f;		//
	creat[7].tol_temp_range = 0.0f;			//

	creat[7].ideal_temp_range_max = creat[7].ideal_temp + creat[7].ideal_temp_range;
	creat[7].ideal_temp_range_min = creat[7].ideal_temp - creat[7].ideal_temp_range;
	creat[7].tol_temp_range_max = creat[7].ideal_temp_range_max + creat[7].tol_temp_range;
	creat[7].tol_temp_range_min = creat[7].ideal_temp_range_min - creat[7].tol_temp_range;

	creat[7].alive = true;
	creat[7].temp_ideal = true;
	creat[7].temp_tol = true;
#pragma endregion

	std::cout << "Is Creature 0 alive? " << creat[0].alive << std::endl;
	std::cout << "Is Creature 1 alive? " << creat[1].alive << std::endl;

	creat[0].alive = energyFitnessTest(creat[0].energy_demand, envir[0].energy_available);
	creat[1].alive = energyFitnessTest(creat[1].energy_demand, envir[0].energy_available);

	std::cout << "Is Creature 0 alive? " << creat[0].alive << std::endl;
	std::cout << "Is Creature 1 alive? " << creat[1].alive << std::endl;

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
void temperatureFitnessTest(float creEnergy, float idealMax, float idealMin, float tolMax, float tolMin, float envTemp, bool ideal, bool tolerated)
{
	idealTemperatureCheck(idealMax, idealMin, envTemp);

	if(!ideal)
		toleratedTemperatureCheck(tolMax, tolMin, envTemp);

	if (tolerated)
		toleratedTemperatureEnergyMultiplier(creEnergy, tolerated);

	surviveTemperature(ideal, tolerated);
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

	float creatIdealTempMax = tolMax;
	float creatIdealTempMin = tolMin;
	float environTemp = envTemp;

	if (environTemp <= creatIdealTempMax
		&& environTemp >= creatIdealTempMin)
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
int toleratedTemperatureEnergyMultiplier(float creEnergy, bool tolerated)
{
	int result = creEnergy;

	if (tolerated)
	{
		result = result * 1.5;
	}

	return result;
}


