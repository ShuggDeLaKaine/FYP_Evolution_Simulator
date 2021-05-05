/** \file environment.h */
#pragma once
#include <iostream>
#include <vector>
#include "core/generalFunctions.h"
//#include "creatures/species.h"

enum EnvironmentalStatus { ABUNDANCE, SUSTAINABLE, PRESSURED, CRITICAL, FAMINE };

struct Environment
{
	float energyAvailable;			//!< energy available in environment.
	float temperature;				//!< temperature of the environment.
	float oxygenationRate;			//!< oxygenation % of the environment.
	float mutationModifier = 1.0f;	//!< always initialised to 1 (no multiple effect), as initialisation considers environment 'clean', changes such a pollution will modify this.
	float pollution = 0.0f;			//!< at initalisation set to 0 as considered to be 'clean', pollution changes added later.
	uint32_t ID;					//!< environmental ID number.

	EnvironmentalStatus currentStatus;	//!< the current status the environment is in.
	float fEnvironmentCapacity = 0.0f;	//!< capacity for combined population mass.
	float fPopulationWeight = 0.0f;		//!< combined weight of all the creatures.
	float fCapacityMultiplier = 10.0f;	//!< multiplier for getting environmentalCapacity, multiple this my energyAvailable.
	float fWeightOffset = 100.0f;		//!< offset to +/- population weight to environmental capacity, to give status' of SUSTAINABLE and PRESSURED.

	inline float getEnergyAvailable() { return energyAvailable; }	//!< get energyAvailable.
	inline float getTemperature() { return temperature; }			//!< get temperature.
	inline float getOxygenRate() { return oxygenationRate; }		//!< get oxygenation rate.
	inline int   getEnvironmentID() { return ID; }					//!< get the environmental id.
};


class EnvironmentCreation
{
public:
	EnvironmentCreation();			//!< default constructor.
	~EnvironmentCreation();			//!< default deconstructor.

	void environmentCreation(Environment& envir, float energyMin, float energyMax, float tempMin, 
							 float tempMax, float oxygenMin, float oxygenMax);		//!< generates a randomised environment.

	uint32_t count = 0;							//!< count for environments.
private:
	inline float setEnergyAvailable(float min, float max) { 
		energy = genFunc->uniformFloatBetween(min, max);
		return energy; }						//!< sets energy, randomised between min and max.
	inline float setTemperature(float min, float max) { 
		temp = genFunc->uniformFloatBetween(min, max);
		return temp; }							//!< sets temperature, randomised between min and max.
	inline float setOxygenRate(float min, float max) { 
		oxy = genFunc->uniformFloatBetween(min, max);
		return oxy; }							//!< sets oxygen, randomised between min and max.
	inline int   setEnvironmentID() { 
		
		return id; }							//!< sets the environments id.
	inline float setEnvironmentalCapacity(float energyAvail, float multiplier) {
		cap = energyAvail * multiplier;
		return cap; }							//!< sets environmental capacity, multiplies energy by multiplier.

	std::shared_ptr<GeneralFunctions> genFunc;	//!< ref to General Functions class.
	float energy;								//!< holder for named var.
	float temp;									//!< holder for named var.
	float oxy;									//!< holder for named var.
	float cap;									//!< holder for named var.
	float id;									//!< holder for named var.
};