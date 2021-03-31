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
Mutation mut;
Display ds;
std::shared_ptr<GeneralFunctions> genFunc;

const int SEED_POP = 10000;
const int LIFE_CYCLES = 5;
const float seedMutIntensity = 0.5f;

Creature seedPopulationPool[SEED_POP];
Environment envir[10];

std::vector<Creature> vecCurrentPopulation;
std::vector<Creature> vecTempPopulation;

std::vector<float> tempGeneStack;
