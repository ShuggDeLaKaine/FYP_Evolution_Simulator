/** \file environment.h */
#pragma once
#include <iostream>
#include <vector>
#include "core/generalFunctions.h"

struct Environment
{
	float energyAvailable;
	float temperature;
	float oxygenationRate;
	int ID;

	inline float getEnergyAvailable() { return energyAvailable; }
	inline float getTemperature() { return temperature; }
	inline float getOxygenRate() { return oxygenationRate; }
	inline int   getEnvironmentID() { return ID; }
};

/*	\class EnvironmentCreation
*	\brief Class...
*/
class EnvironmentCreation
{
public:
	EnvironmentCreation() {};					//!< default constructor.
	~EnvironmentCreation();						//!< default deconstructor.

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