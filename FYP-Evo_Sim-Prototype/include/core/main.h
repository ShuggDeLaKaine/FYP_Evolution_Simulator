/**\file main.h */
#pragma once

#include <iostream>
#include <vector>
#include "core/headerList.h"


//reference to classes.
FullFitnessTest ft;
CreatureCreation cc;
CreatureSettings cs;
EnvironmentCreation ec;
Species sp;
SpeciesInfo si;
AllSpecies as;
Mutation mut;
Display ds;
std::shared_ptr<GeneralFunctions> genFunc;

const int SEED_POP = 10000;
const int MAX_SPECIES = 10000;
const int LIFE_CYCLES = 5;
const float seedMutIntensity = 0.5f;

uint32_t isAlive = 0;
uint32_t isDead = 0;

uint32_t totalMutTests = 0;
uint32_t totalNumberMut = 0;

uint32_t tempPosition = 0;

Creature    seedPopulationPool[SEED_POP];
SpeciesInfo speciesPool[MAX_SPECIES];
AllSpecies  allSpeciesList[1];
Environment envir[10];

std::vector<Creature> vecCurrentPopulation;
std::vector<Creature> vecTempPopulation;

std::vector<float> tempGeneStack;
