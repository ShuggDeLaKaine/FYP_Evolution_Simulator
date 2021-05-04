/**\file competition.cpp */
#include "mechanics/competition.h"


void Competition::setEnvironmentalStatus(Environment &environment)
{
	int temp = SUSTAINABLE;

	//compare population weight to environmental capacity and set environmental status accordingly.
	if (environment.fPopulationWeight <= (environment.fEnvironmentCapacity * fAbundanceMultiplier))	//0.0f to 0.75f
	{
		//set environment status to ABUNDANCE...
		temp = ABUNDANCE;
		environment.currentStatus = EnvironmentalStatus(temp);
	} 
	else if (environment.fPopulationWeight > (environment.fEnvironmentCapacity * fAbundanceMultiplier) &&	//0.75f
		environment.fPopulationWeight <= environment.fEnvironmentCapacity) //0.75f to 1.0f
	{
		//set environment status to SUSTAINABLE...
		temp = SUSTAINABLE;
		environment.currentStatus = EnvironmentalStatus(temp);
	} 
	else if (environment.fPopulationWeight > environment.fEnvironmentCapacity &&
		environment.fPopulationWeight <= (environment.fEnvironmentCapacity * fPressuredMultiplier)) //1.0f to 1.25f
	{
		//set environment status to PRESSURED...
		temp = PRESSURED;
		environment.currentStatus = EnvironmentalStatus(temp);
	} 
	else if (environment.fPopulationWeight > (environment.fEnvironmentCapacity * fPressuredMultiplier) &&
		environment.fPopulationWeight <= (environment.fEnvironmentCapacity * fCriticalMultiplier))	//1.25f to 1.5f
	{
		//set environment status to CRITICAL...
		temp = CRITICAL;
		environment.currentStatus = EnvironmentalStatus(temp);
	}
	else if (environment.fPopulationWeight > (environment.fEnvironmentCapacity * fPressuredMultiplier)) //1.5f>>>
	{
		//set environment status to FAMINE...
		temp = FAMINE;
		environment.currentStatus = EnvironmentalStatus(temp);
	} 
	else 
	{
		//else default to sustainable. 
		temp = SUSTAINABLE;
		environment.currentStatus = EnvironmentalStatus(temp);
	}
}

void Competition::getEnvironmentStatus(Environment &environment)
{
	fToCompetePercent = 1.0f;

	switch (environment.currentStatus)
	{
	case ABUNDANCE:
		//abundance == more resources available, but what is the effect? A reverse of the below with added energy? More offspring?
		fToCompetePercent = 0.0f;
		break;

	case SUSTAINABLE:
		//sustainable == no extra effects, good or bad.
		fToCompetePercent = 0.0f;
		break;

	case PRESSURED:
		//pressured == 30% of population experiences a reduction of available energy, as competing for food.
		fToCompetePercent *= fPressuredState;
		break;

	case CRITICAL:
		//critical == 60% of population experiences a reduction of available energy, as competing for food.
		fToCompetePercent *= fCriticalState;
		break;

	case FAMINE:
		//famine == 100% of population experiences a reduction in available energy, as competing for food.
		fToCompetePercent *= fFamineState;
		break;
	}
}

//void Competition::getCreatureSize(AllSpecies speciesList, int sizeGeneElement)
float Competition::getPopulationToCompete(int speciesMembershipSize, int sizeGeneElement)
{
	float tempPercent = fToCompetePercent;

	switch (sizeGeneElement)
	{
	case VERY_SMALL:
		//update 'competing' var to apply the relevant size % multiplier.
		tempPercent *= fVSmall;
		//get final population number to compete by multiplying membership size by percentage to compete value.
		iFinalPopToCompete = speciesMembershipSize * tempPercent;
		break;

	case SMALL:
		//update 'competing' var to apply the relevant size % multiplier.
		tempPercent *= fSmall;
		//get final population number to compete by multiplying membership size by percentage to compete value.
		iFinalPopToCompete = speciesMembershipSize * tempPercent;
		break;

	case MEDIUM:
		//update 'competing' var to apply the relevant size % multiplier.
		tempPercent *= fMedium;
		//get final population number to compete by multiplying membership size by percentage to compete value.
		iFinalPopToCompete = speciesMembershipSize * tempPercent;
		break;

	case LARGE:
		//update 'competing' var to apply the relevant size % multiplier.
		//fToCompetePercent *= fLarge;
		tempPercent *= fLarge;
		//get final population number to compete by multiplying membership size by percentage to compete value.
		iFinalPopToCompete = speciesMembershipSize * tempPercent;
		break;

	case VERY_LARGE:
		//update 'competing' var to apply the relevant size % multiplier.
		tempPercent *= fVLarge;
		//get final population number to compete by multiplying membership size by percentage to compete value.
		iFinalPopToCompete = speciesMembershipSize * tempPercent;
		break;
	}

	return iFinalPopToCompete;
}
