/** \file display.cpp */
#pragma once
#include "creatures/creature.h"
#include "core/generalFunctions.h"


/*	\class Display
*	\brief Class...
*/
class Display
{
public:
	void displayCreatureVariables(Creature creat[], int element);					//!< 
	void displaySeedPopulationPoolResult(int alive, int dead);						//!< 
	void displayFirstPopulation(const Creature creat[], int pop);					//!< 
	void displayFirstPopulation(const std::vector<Creature> creat);					//!< 
	void displaySurvivedPercentage(const Environment envir, int alive, int popSize);//!< 

private:
	CreatureCreation cc;
	std::shared_ptr<GeneralFunctions> genFunc;
};