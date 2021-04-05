/**\file species.cpp */
#include "creatures/species.h"

Species::Species()
{
	//as.fullSpeciesList.clear();
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
	//pop the species onto the back of the target species vector.
	speciesVector.push_back(species);
	//update species count.
	allSpecies.speciesCount = allSpecies.fullSpeciesList.size();
}

void Species::addCreatureToSpecies(Creature creature, SpeciesInfo & species)
{
	//push creature onto the species vector.
	species.speciesMembership.push_back(creature);
	species.currentMembers++;
	species.totalMembers++;
}

void Species::updateSpeciesMembership(SpeciesInfo& species)
{
	species.currentMembers = species.speciesMembership.size();
	species.totalMembers += species.currentMembers;
}

void Species::checkSpeciesDivergence()
{
	//check each member of the species populations gene stack element values against the species gene stack. 

	//if the member has diverged from the the main species gene stack, consider making a sub-species or new species.

	//NOTE ***TODO*** 
	//work out what distance between a diverging member and the population average would be considered as diverging.
	//this will need testing.

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
