/**\file species.cpp */
#include "creatures/species.h"

Species::Species()
{
	//reserve the space required in the species vectors. 
	as.fullSpeciesList.reserve(as.MAX_SPECIES);
}

void Species::createNewSpecies(SpeciesInfo species, std::vector<float> geneStack, uint32_t creatureID)
{
	//first set the speciesID to the creatureID.
	species.speciesID = creatureID;

	//set the size of the seedGeneStack to the size of the params geneStack.
	species.seedGeneStack.reserve(geneStack.size());
	//assign that over into the reserved space. 
	species.seedGeneStack.assign(geneStack.begin(), geneStack.end());


}

void Species::updateSpeciesMembership()
{

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

void Species::updateSpeciesGeneStack(std::vector<float>& geneStack)
{
	//iterate through membership of species for each gene element of the their species gene stack.
	//take an average of each gene and assign that to the relevant element in the species gene stack.
	//then move on and do the same to the next element in the species gene stack.
}
