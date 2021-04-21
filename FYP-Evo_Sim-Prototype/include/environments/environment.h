/** \file environment.h */
#pragma once
#include <iostream>
#include <vector>
#include "core/generalFunctions.h"

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
	float fCapacityMultiplier = 100.0f;	//!< multiplier for getting environmentalCapacity, multiple this my energyAvailable.
	float fWeightOffset = 100.0f;		//!< offset to +/- population weight to environmental capacity, to give status' of SUSTAINABLE and PRESSURED.

	inline float getEnergyAvailable() { return energyAvailable; }	//!< get energyAvailable.
	inline float getTemperature() { return temperature; }			//!< get temperature.
	inline float getOxygenRate() { return oxygenationRate; }		//!< get oxygenation rate.
	inline int   getEnvironmentID() { return ID; }					//!< get the environmental id.

	float fVSmall = 0.45f;			//!< % of very small creature size populations to have competition mechanics applied to.
	float fSmall  = 0.25f;			//!< % of small creature size populations to have competition mechanics applied to.
	float fMedium = 0.15f;			//!< % of medium creature size populations to have competition mechanics applied to.
	float fLarge  = 0.10f;			//!< % of large creature size populations to have competition mechanics applied to.
	float fVLarge = 0.05f;			//!< % of very large creature size populations to have competition mechanics applied to.
									
	float fPressuredState = 0.3f;	//!< % of overall populations to have competition mechanics applied to if environmental status is PRESSURED.
	float fCriticalState = 0.6f;	//!< % of overall populations to have competition mechanics applied to if environmental status is CRITICAL.
	float fFamineState = 1.0f;		//!< % of overall populations to have competition mechanics applied to if environmental status is FAMINE.

	float minRange;					//!< range of 
	float maxRange;					//!< range of 

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
	inline float setEnvironmentalCapacity(float energyAvail, float multiplier) {
		cap = energyAvail * multiplier;
		return cap; }							//!<

	std::shared_ptr<GeneralFunctions> genFunc;	//!< ref to General Functions class.
	float energy;								//!< holder for named var.
	float temp;									//!< holder for named var.
	float oxy;									//!< holder for named var.
	float cap;									//!< holder for named var.
	float id;									//!< holder for named var.
};