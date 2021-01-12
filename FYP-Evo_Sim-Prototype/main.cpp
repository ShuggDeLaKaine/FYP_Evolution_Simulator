/** \file main.cpp */

#include <iostream>
#include <vector>


struct Environment
{
	float energyAvailable;
	float idealTemp;
};

struct Creature
{
	//energy vars.
	float energyDemand;

	//ideal idealTemp vars.
	float idealTemp;
	float idealTempRange;
	float idealTempRangeMin;
	float idealTempRangeMax;

	//tolerated idealTemp vars.
	float tolTempRange;
	float tolTempRangeMin;
	float tolTempRangeMax;

	//bools for conditions.
	bool alive;
	bool tempIdeal;
	bool tempTol;

	int creatureNumber;
};

//declaring functions ***ALL NEED ABSTRACTING***
void creatureFitnessTests(Creature creature, Environment environment);
bool energyFitnessTest(float creature, float environment);
bool idealidealTempCheck(float idealMax, float idealMin, float envTemp);
bool toleratedidealTempCheck(float tolMax, float tolMin, float envTemp);
bool surviveidealTemp(bool ideal, bool tolerated);
int toleratedidealTempEnergyMultiplier(float creEnergy, bool ideal, bool tolerated);


int main()
{

	struct Environment envir[1];
	struct Creature creat[7];

	Environment * p_environments = envir;
	Creature * p_creatures = creat;
	//Environment * p_environments = &envir[0];
	//Creature * p_creatures = &creat[0];

	envir[0].energyAvailable = 500.0f;
	envir[0].idealTemp = 12.0f;


#pragma region TEST_ENERGY_AVAILABLE.
	//creature 0 - should SURVIVE ideally suited to environment 0.
	creat[0].energyDemand = 400.0f;		//in range of environ energy.
	creat[0].idealTemp = 12.0f;			//same as environ temp.
	creat[0].idealTempRange = 1.0f;
	creat[0].tolTempRange = 1.0f;

	creat[0].idealTempRangeMax = creat[0].idealTemp + creat[0].idealTempRange;
	creat[0].idealTempRangeMin = creat[0].idealTemp - creat[0].idealTempRange;
	creat[0].tolTempRangeMax = creat[0].idealTempRangeMax + creat[0].tolTempRange;
	creat[0].tolTempRangeMin = creat[0].idealTempRangeMin - creat[0].tolTempRange;

	creat[0].alive = true;
	creat[0].tempIdeal = true;
	creat[0].tempTol = true;

	creat[0].creatureNumber = 1;

	//creature 1 - should NOT SURVIVE be suited to environment 0.
	creat[1].energyDemand = 650.0f;		//over the range, not even environ energy.
	creat[1].idealTemp = 12.0f;			//same as environ temp.
	creat[1].idealTempRange = 1.0f;
	creat[1].tolTempRange = 1.0f;

	creat[1].idealTempRangeMax = creat[1].idealTemp + creat[1].idealTempRange;
	creat[1].idealTempRangeMin = creat[1].idealTemp - creat[1].idealTempRange;
	creat[1].tolTempRangeMax = creat[1].idealTempRangeMax + creat[1].tolTempRange;
	creat[1].tolTempRangeMin = creat[1].idealTempRangeMin - creat[1].tolTempRange;

	creat[1].alive = true;
	creat[1].tempIdeal = true;
	creat[1].tempTol = true;

	creat[1].creatureNumber = 2;
#pragma endregion

#pragma region TEST_idealTemp
	//creature 2 - should SURVIVE suited to environment 0.
	creat[2].energyDemand = 200.0f;		//over the range, not even environ energy.
	creat[2].idealTemp = 12.0f;			//same as environ temp.
	creat[2].idealTempRange = 1.0f;		//
	creat[2].tolTempRange = 1.0f;		//

	creat[2].idealTempRangeMax = creat[2].idealTemp + creat[2].idealTempRange;
	creat[2].idealTempRangeMin = creat[2].idealTemp - creat[2].idealTempRange;
	creat[2].tolTempRangeMax = creat[2].idealTempRangeMax + creat[2].tolTempRange;
	creat[2].tolTempRangeMin = creat[2].idealTempRangeMin - creat[2].tolTempRange;

	creat[2].alive = true;
	creat[2].tempIdeal = true;
	creat[2].tempTol = true;

	creat[2].creatureNumber = 3;

	//creature 3 - should NOT SURVIVE be suited to environment 0.
	creat[3].energyDemand = 200.0f;			//over the range, not even environ energy.
	creat[3].idealTemp = 20.0f;				//much higher than environ temp.
	creat[3].idealTempRange = 1.0f;
	creat[3].tolTempRange = 1.0f;

	creat[3].idealTempRangeMax = creat[3].idealTemp + creat[3].idealTempRange;
	creat[3].idealTempRangeMin = creat[3].idealTemp - creat[3].idealTempRange;
	creat[3].tolTempRangeMax = creat[3].idealTempRangeMax + creat[3].tolTempRange;
	creat[3].tolTempRangeMin = creat[3].idealTempRangeMin - creat[3].tolTempRange;

	creat[3].alive = true;
	creat[3].tempIdeal = true;
	creat[3].tempTol = true;

	creat[3].creatureNumber = 4;
#pragma endregion

#pragma region TEST_idealTemp_TOLERANCE_RANGES.
	//creature 4 - should SURVIVE, instead ideal idealTemp range.
	creat[4].energyDemand = 200.0f;		//in range of environ energy.
	creat[4].idealTemp = 11.5f;			//off environ temp.
	creat[4].idealTempRange = 1.0f;		//
	creat[4].tolTempRange = 2.0f;		//

	creat[4].idealTempRangeMax = creat[4].idealTemp + creat[4].idealTempRange;
	creat[4].idealTempRangeMin = creat[4].idealTemp - creat[4].idealTempRange;
	creat[4].tolTempRangeMax = creat[4].idealTempRangeMax + creat[4].tolTempRange;
	creat[4].tolTempRangeMin = creat[4].idealTempRangeMin - creat[4].tolTempRange;

	creat[4].alive = true;
	creat[4].tempIdeal = true;
	creat[4].tempTol = true;

	creat[4].creatureNumber = 5;

	//creature 5 - should SURVIVE, inside tolerated idealTemp range and still enough energy remaining after multiplier.
	creat[5].energyDemand = 200.0f;		//in range of environ energy.
	creat[5].idealTemp = 10.0f;			//off environ temp.
	creat[5].idealTempRange = 1.0f;		//
	creat[5].tolTempRange = 2.0f;		//

	creat[5].idealTempRangeMax = creat[5].idealTemp + creat[5].idealTempRange;
	creat[5].idealTempRangeMin = creat[5].idealTemp - creat[5].idealTempRange;
	creat[5].tolTempRangeMax = creat[5].idealTempRangeMax + creat[5].tolTempRange;
	creat[5].tolTempRangeMin = creat[5].idealTempRangeMin - creat[5].tolTempRange;

	creat[5].alive = true;
	creat[5].tempIdeal = true;
	creat[5].tempTol = true;

	creat[5].creatureNumber = 6;

	//creature 6 - should NOT SURVIVE, inside tolerated idealTemp range but NOT enough energy remaining after multiplier.
	creat[6].energyDemand = 450.0f;		//in range of environ energy.
	creat[6].idealTemp = 10.0f;			//a little off environ temp.
	creat[6].idealTempRange = 1.0f;		//
	creat[6].tolTempRange = 2.0f;		//

	creat[6].idealTempRangeMax = creat[6].idealTemp + creat[6].idealTempRange;
	creat[6].idealTempRangeMin = creat[6].idealTemp - creat[6].idealTempRange;
	creat[6].tolTempRangeMax = creat[6].idealTempRangeMax + creat[6].tolTempRange;
	creat[6].tolTempRangeMin = creat[6].idealTempRangeMin - creat[6].tolTempRange;

	creat[6].alive = true;
	creat[6].tempIdeal = true;
	creat[6].tempTol = true;

	creat[6].creatureNumber = 7;

#pragma endregion

	//TESTING - energy levels.
	creatureFitnessTests(creat[0], envir[0]);
	creatureFitnessTests(creat[1], envir[0]);

	//TESTING - idealTemp levels.
	creatureFitnessTests(creat[2], envir[0]);
	creatureFitnessTests(creat[3], envir[0]);

	//TESTING - idealTemp tolerance and energy demand multiplier.
	creatureFitnessTests(creat[4], envir[0]);
	creatureFitnessTests(creat[5], envir[0]);
	creatureFitnessTests(creat[6], envir[0]);
}





//function to take the creature and environment and then run all the relevant fitness tests on.
void creatureFitnessTests(Creature creature, Environment environment)
{
	creature.tempIdeal = idealidealTempCheck(creature.idealTempRangeMax, creature.idealTempRangeMin, environment.idealTemp);
	creature.tempTol = toleratedidealTempCheck(creature.tolTempRangeMax, creature.tolTempRangeMin, environment.idealTemp);
	creature.alive = surviveidealTemp(creature.tempIdeal, creature.tempTol);

	if (creature.alive)
	{
		creature.energyDemand = toleratedidealTempEnergyMultiplier(creature.energyDemand, creature.tempIdeal, creature.tempTol);
		creature.alive = energyFitnessTest(creature.energyDemand, environment.energyAvailable);
	}
	
	std::cout << "Did Creature " << creature.creatureNumber << " survive?   ";
	if (creature.alive)
		std::cout << "   YES! CREATURE " << creature.creatureNumber << " SURVIVED!" << std::endl;
	else
		std::cout << "   NO! CREATURE " << creature.creatureNumber << " IS DEAD!" << std::endl;
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

//function to determine whether in ideal idealTemp range fitness check.
bool idealidealTempCheck(float idealMax, float idealMin, float envTemp)
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

//function to determine whether in tolerated idealTemp range fitness check.
bool toleratedidealTempCheck(float tolMax, float tolMin, float envTemp)
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

//function to determine whether creature can survive idealTemp.
bool surviveidealTemp(bool ideal, bool tolerated)
{
	bool survive = true;
	bool inIdeal = ideal;
	bool inTolerated = tolerated;

	if (!inIdeal && !inTolerated)
		survive = false;

	return survive;
}

//function to apply multiplier to energy demand if in idealTemp tolerance range. 
int toleratedidealTempEnergyMultiplier(float creEnergy, bool ideal, bool tolerated)
{
	int result = creEnergy;

	if (!ideal && tolerated)
	{
		result = result * 1.5;
	}

	return result;
}
