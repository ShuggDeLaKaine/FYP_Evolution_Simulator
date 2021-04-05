/** \file environment.h */
#pragma once
#include <iostream>
#include <vector>
#include "core/generalFunctions.h"

struct Environment
{
	float energyAvailable;			//!< energy available in environment.
	float fWeightCapacity;			//!< how much collective creature weight the environment can take before resource availability starts to drop. 
	float temperature;				//!< temperature of the environment.
	float oxygenationRate;			//!< oxygenation % of the environment.
	float mutationModifier = 1.0f;	//!< always initialised to 1 (no multiple effect), as initialisation considers environment 'clean', changes such a pollution will modify this.
	float pollution = 0.0f;			//!< at initalisation set to 0 as considered to be 'clean', pollution changes added later.
	uint32_t ID;					//!< environmental ID number.

	inline float getEnergyAvailable() { return energyAvailable; }	//!< get energyAvailable.
	inline float getTemperature() { return temperature; }			//!< get temperature.
	inline float getOxygenRate() { return oxygenationRate; }		//!< get oxygenation rate.
	inline int   getEnvironmentID() { return ID; }					//!< get the environmental id.
};

/*	\class EnvironmentCreation
*	\brief Class...
*/
class EnvironmentCreation
{
public:
	EnvironmentCreation();			//!< default constructor.
	~EnvironmentCreation();			//!< default deconstructor.

	void environmentCreation(Environment& envir, float energyMin, float energyMax, float tempMin, 
							 float tempMax, float oxygenMin, float oxygenMax);		//!< 

	uint32_t count = 0;							//!< 
private:
	inline float setEnergyAvailable(float min, float max) { 
		energy = genFunc->uniformFloatBetween(min, max);
		return energy; }						//!< 
	inline float setTemperature(float min, float max) { 
		temp = genFunc->uniformFloatBetween(min, max);
		return temp; }							//!< 
	inline float setOxygenRate(float min, float max) { 
		oxy = genFunc->uniformFloatBetween(min, max);
		return oxy; }							//!< 
	inline int   setEnvironmentID() { 
		
		return id; }							//!< 

	std::shared_ptr<GeneralFunctions> genFunc;	//!< ref to General Functions class.
	float energy;								//!< holder for named var, used in set...()
	float temp;									//!< holder for named var, used in set...()
	float oxy;									//!< holder for named var, used in set...()
	float id;									//!< holder for named var, used in set...()
};