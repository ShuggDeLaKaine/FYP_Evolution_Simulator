/** \file competition.h */
#pragma once

#include <iostream>
#include <vector>
#include "core/generalFunctions.h"
#include "environments/environment.h"
#include "fitness/fullFitnessTest.h"
#include "creatures/species.h"


/*	\class Competition
*	\brief Class...
*/
class Competition
{
public:
	void setEnvironmentalStatus(Environment &environment);
	void getEnvironmentStatus(Environment &environment);
	float getPopulationToCompete(int speciesMembershipSize, int sizeGeneElement);

private:
	float fToCompetePercent = 1.0f;			//!< 
	int iCreatureSIZE = 0;					//!< 
	int iFinalPopToCompete = 0;				//!< 

	float fCriticalMultiplier  = 1.5f;		//!< multiplier for environment capacity/creature weight comparisons.
	float fPressuredMultiplier = 1.25f;		//!< multiplier for environment capacity/creature weight comparisons.
	float fAbundanceMultiplier = 0.75f;		//!< multiplier for environment capacity/creature weight comparisons.

	float fVSmall = 0.95f;					//!< % of very small creature size populations to have competition mechanics applied to.
	float fSmall  = 0.90f;					//!< % of small creature size populations to have competition mechanics applied to.
	float fMedium = 0.80f;					//!< % of medium creature size populations to have competition mechanics applied to.
	float fLarge  = 0.70f;					//!< % of large creature size populations to have competition mechanics applied to.
	float fVLarge = 0.60f;					//!< % of very large creature size populations to have competition mechanics applied to.

	float fPressuredState = 0.3f;			//!< % of overall populations to have competition mechanics applied to if environmental status is PRESSURED.
	float fCriticalState  = 0.6f;			//!< % of overall populations to have competition mechanics applied to if environmental status is CRITICAL.
	float fFamineState    = 0.99f;			//!< % of overall populations to have competition mechanics applied to if environmental status is FAMINE.
};