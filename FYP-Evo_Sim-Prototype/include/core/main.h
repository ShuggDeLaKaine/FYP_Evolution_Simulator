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
Competition comp;								//!< ref to Competition class.

SpeciesInfo si;									//!< ref to Species Info struct.
AllSpecies as;									//!< ref to All Species struct.
CreatureSettings cs;							//!< ref to Creature Settings struct.

std::shared_ptr<GeneralFunctions> genFunc;		//!< ptr to General Functions class.

const uint32_t SEED_POP = 15000;				//!< number of creatures for the seed stage.
const uint32_t MAX_SPECIES = 10000;				//!< max number of species.
uint32_t LIFE_CYCLES = 20;						//!< number of life cycles to iterate through.
const uint32_t STARTING_POP = 100;				//!< once creatures chosen after seed stage, number of creatures in each species to start with.
const float seedMutIntensity = 0.5f;			//!< mutation intensity during the seed stage, used for first populations of creatures.
bool bSuccessfulSeed = false;					//!< bool to take whether the seed stage has been successful.

float mutChance = 2.5f;
float mutInten = 2.5f;

uint32_t tempPosition = 0;						//!< holds the position within an array or vector.

Creature    seedPopulationPool[SEED_POP];		//!< a pool for the seed population.
SpeciesInfo speciesPool[MAX_SPECIES];			//!< a pool for species set as max species.
AllSpecies  allSpecies;							//!< contains the details of all the species.
Environment envir[10];							//!< array of environments.

std::vector<Creature> vecCurrentPopulation;		//!< current storage of populations of Creatures.
std::vector<Creature> vecOffspringPopulation;	//!< storage for populations of offspring Creatures.
std::vector<Creature> vecTempPopulation;		//!< temp storage for populations of Creatures.

std::vector<Creature> tempCreatsToAdd;			//!< temp storage for creatures to be added to the next generation.
std::vector<std::pair<float, std::vector<float>>> tempReproduce;	//!< temp storage for gene stacks to be reproduced.
std::vector<float> tempGeneStack;				//!< takes and holds a gene stack whilst moving the data.
