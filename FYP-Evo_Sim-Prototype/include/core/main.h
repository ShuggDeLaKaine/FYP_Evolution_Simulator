/**\file main.h */
#pragma once

#include <iostream>
#include <vector>
#include "core/headerList.h"


//reference to classes.
FullFitnessTest ft;								//!< ref to Full Fitness Test class.
CreatureCreation cc;							//!< ref to Creature Creation class.
EnvironmentCreation ec;							//!< ref to Environment Creation class.
Species sp;										//!< ref to Species class.
Mutation mut;									//!< ref to Mutation class.
Selection sel;									//!< ref to Selection class.
Crossover cross;								//!< ref to Crossover class.
Display ds;										//!< ref to Display class.

SpeciesInfo si;									//!< ref to Species Info struct.
AllSpecies as;									//!< ref to All Species struct.
CreatureSettings cs;							//!< ref to Creature Settings struct.

std::shared_ptr<GeneralFunctions> genFunc;		//!< ptr to General Functions class.

const uint32_t SEED_POP = 10000;				//!< number of creatures for the seed stage.
const uint32_t MAX_SPECIES = 10000;				//!< max number of species.
const uint32_t LIFE_CYCLES = 5;					//!< number of life cycles to iterate through.
const uint32_t STARTING_POP = 12;				//!< once creatures chosen after seed stage, number of creatures in each species to start with.
const float seedMutIntensity = 0.5f;			//!< mutation intensity during the seed stage, used for first populations of creatures.
bool bSuccessfulSeed = false;					//!< bool to take whether the seed stage has been successful.

uint32_t isAlive = 0;							//!< TESTING - count of 'alive' creatures from the seed population.
uint32_t isDead = 0;							//!< TESTING - count of 'dead' creatures from seed population.
uint32_t totalMutTests = 0;						//!< TESTING - count of total mutation tests.
uint32_t totalNumberMut = 0;					//!< TESTING - count of number of mutations.

uint32_t tempPosition = 0;						//!< holds the position within an array or vector.

Creature    seedPopulationPool[SEED_POP];		//!< a pool for the seed population.
SpeciesInfo speciesPool[MAX_SPECIES];			//!< a pool for species set as max species.
AllSpecies  allSpeciesList[1];					//!< single array to contain details of all the species in the sim.
Environment envir[10];							//!< array of environments.

std::vector<Creature> vecCurrentPopulation;		//!< current storage of populations of Creatures.
std::vector<Creature> vecTempPopulation;		//!< temp storage for populations of Creatures.

std::vector<float> tempGeneStack;				//!< takes and holds a gene stack whilst moving the data.
