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
	//iCreatureSIZE = sizeGeneElement;

	//switch (iCreatureSIZE)
	switch (sizeGeneElement)
	{
	case VERY_SMALL:
		//update 'competing' var to apply the relevant size % multiplier.
		fToCompetePercent *= fVSmall;
		//get final population number to compete by multiplying membership size by percentage to compete value.
		iFinalPopToCompete = speciesMembershipSize * static_cast<int>(fToCompetePercent);
	case SMALL:
		//update 'competing' var to apply the relevant size % multiplier.
		fToCompetePercent *= fSmall;
		//get final population number to compete by multiplying membership size by percentage to compete value.
		iFinalPopToCompete = speciesMembershipSize * static_cast<int>(fToCompetePercent);
	case MEDIUM:
		//update 'competing' var to apply the relevant size % multiplier.
		fToCompetePercent *= fMedium;
		//get final population number to compete by multiplying membership size by percentage to compete value.
		iFinalPopToCompete = speciesMembershipSize * static_cast<int>(fToCompetePercent);
	case LARGE:
		//update 'competing' var to apply the relevant size % multiplier.
		fToCompetePercent *= fLarge;
		//get final population number to compete by multiplying membership size by percentage to compete value.
		iFinalPopToCompete = speciesMembershipSize * static_cast<int>(fToCompetePercent);
	case VERY_LARGE:
		//update 'competing' var to apply the relevant size % multiplier.
		fToCompetePercent *= fVLarge;
		//get final population number to compete by multiplying membership size by percentage to compete value.
		iFinalPopToCompete = speciesMembershipSize * static_cast<int>(fToCompetePercent);
	}

	return iFinalPopToCompete;
}





/*
case CRITICAL:
	//critical == 60% of population experiences a reduction of available energy, as competing for food.
	//effects split between creature sizes, smallest taking biggest brunt, largest the least.
	//V.Small = 45% of total | Small = 25% | Medium = 15% | Large = 10% | V.Large = 5%
	//these of 60% is...
	//V.Small = 27.0% of total | Small = 15.0% | Medium = 9.0% | Large = 6.0% | V.Large = 3.0%
	float competing = 1.0f * envir[0].fCriticalState;

	break;


case FAMINE:
	//famine == 100% of population experiences a reduction in available energy, as competing for food.
	//which members of population will be effected?
	//effects split between creature sizes, smallest taking biggest brunt, largest the least.
	//V.Small = 45% of total | Small = 25% | Medium = 15% | Large = 10% | V.Large = 5%
	float competing = 1.0f * envir[0].fFamineState;

	break;
*/