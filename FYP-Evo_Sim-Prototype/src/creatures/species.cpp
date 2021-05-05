/**\file species.cpp */
#include "creatures/species.h"

Species::Species()
{
	
}

void Species::createNewSpecies(SpeciesInfo & species, std::vector<float> & geneStack, uint32_t creatureID)
{
	//first set the speciesID to the creatureID.
	species.speciesID = creatureID;

	//set the size of the seedGeneStack to the size of the params geneStack.
	species.seedGeneStack.reserve(geneStack.size());

	//assign that over into the reserved space. 
	species.seedGeneStack.assign(geneStack.begin(), geneStack.end());
}

void Species::assignSpeciesToAllSpeciesVector(SpeciesInfo species, std::vector<SpeciesInfo> & speciesVector, AllSpecies & allSpecies)
{
	speciesVector.push_back(species);
}

void Species::addCreatureToSpecies(Creature creature, SpeciesInfo & species)
{
	species.speciesMembership.push_back(creature);
	species.currentMembers = species.speciesMembership.size();
}

void Species::updateSpeciesMembershipCounts(SpeciesInfo& species)
{
	//set previous and current memberships.
	species.previousMembers = species.currentMembers;
	species.currentMembers = species.speciesMembership.size();
}

void Species::checkSpeciesDivergence()
{
	//check each member of the species populations gene stack element values against the species gene stack. 

	//if the member has diverged from the the main species gene stack, consider making a sub-species or new species.

	//NOTE ***TODO*** 
	//work out what distance between a diverging member and the population average would be considered as diverging.
	//this will need testing.

}

void Species::startCycleMemberships(AllSpecies &allSpec)
{
	for (int i = 0; i < allSpec.aliveSpeciesVec.size(); i++)
		allSpec.aliveSpeciesVec.at(i).startCycleMembers = allSpec.aliveSpeciesVec.at(i).speciesMembership.size();
}

void Species::endCycleMemberships(AllSpecies &allSpec)
{
	for (int i = 0; i < allSpec.aliveSpeciesVec.size(); i++)
		allSpec.aliveSpeciesVec.at(i).endCycleMembers = allSpec.aliveSpeciesVec.at(i).speciesMembership.size();
}

void Species::resetCycleCounts(AllSpecies & allSpec)
{
	//reset all the cycle counters as a new cycle about to begin.
	for(int i = 0; i < allSpec.aliveSpeciesVec.size(); i++)
	{
		allSpec.aliveSpeciesVec.at(i).cycleTotalDeadCount = 0;
		allSpec.aliveSpeciesVec.at(i).cycleFailedFitnessDeadCount = 0;
		allSpec.aliveSpeciesVec.at(i).cycleOldAgeDeadCount = 0;
	}
}

std::vector<float>  Species::getSeedGeneStack(SpeciesInfo species)
{
	std::vector<float> result;
	result.reserve(species.seedGeneStack.size());
	result.assign(species.seedGeneStack.begin(), species.seedGeneStack.end());
	return result;
}

std::vector<float>  Species::getSpeciesGeneStack(SpeciesInfo species)
{
	std::vector<float> result;
	result.reserve(species.speciesGeneStack.size());
	result.assign(species.speciesGeneStack.begin(), species.speciesGeneStack.end());
	return result;
}

//void Species::updateSpeciesGeneStack(std::vector<Creature> speciesMembership, std::vector<float> & speciesGeneStack)
void Species::updateSpeciesGeneStack(SpeciesInfo & species)
{
	//ensure speciesGeneStack has values
	if (species.speciesGeneStack.size() == 0)
		species.speciesGeneStack.resize(species.speciesMembership.at(0).geneStack.size());

	//iterate through membership of species for each gene element of the their species gene stack.
	for (int i = 0; i < species.speciesMembership.size(); i++)
	{
		//iterate through gene stack of species member.
		for (int j = 0; j < species.speciesMembership.at(i).geneStack.size(); j++)
		{
			//add the gene stack values of each member to the species overall average gene stack. 
			species.speciesGeneStack.at(j) = species.speciesGeneStack.at(j) + species.speciesMembership.at(i).geneStack.at(j);
		}
	}

	//now average each element of the species gene stack by the size of the species membership.
	for (int i = 0; i < species.speciesGeneStack.size(); i++)
	{
		float result = species.speciesGeneStack.at(i);
		result = genFunc->roundFloat(result / species.speciesMembership.size());
		species.speciesGeneStack.at(i) = result;
	}
}

void Species::updateAllSpecies(AllSpecies& allSpecies)
{
	//clear aliveSpecies as this will be repopulated.
	//allSpecies.aliveSpeciesVec.clear();

	//first iterate through fullSpecies list, run its speciesAliveCheck
	for (int i = 0; i < allSpecies.aliveSpeciesVec.size(); i++)
	{
		//run species alive check on element i in fullSpecies.
		allSpecies.aliveSpeciesVec.at(i).speciesAliveCheck();
		bool result = allSpecies.aliveSpeciesVec.at(i).speciesAlive;

		//species deeeeaaad...
		if (!result)
		{
			//place species into extinctSpecies
			allSpecies.extinctSpeciesVec.push_back(allSpecies.aliveSpeciesVec.at(i));
			allSpecies.aliveSpeciesVec.erase(allSpecies.aliveSpeciesVec.begin() + i);
			i--;
		}
	}
	//finish up by updating all the species counts.
	updateAllSpeciesCounts(allSpecies);
}

void Species::updateAllSpeciesCounts(AllSpecies& allSpecies)
{
	allSpecies.aliveSpeciesCount = allSpecies.aliveSpeciesVec.size();
	allSpecies.extinctSpeciesCount = allSpecies.extinctSpeciesVec.size();
	allSpecies.totalSpeciesCount = allSpecies.aliveSpeciesCount + allSpecies.extinctSpeciesCount;
}
