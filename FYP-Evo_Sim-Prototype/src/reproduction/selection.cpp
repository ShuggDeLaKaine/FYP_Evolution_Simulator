/**\file selection.cpp */
#include "reproduction/selection.h"


void Selection::parentSelection(SpeciesInfo species)
{
	//fill the selection table with paired scores and geneStacks of the creatures from the passed in species.
	fillSelectionTable(species);

	//sort the table in descending order using the first of pair, ie the scores.
	std::sort(selectionTable.begin(), selectionTable.end(), greater());

	//take the n% to be used for reproduction.
	percentToReproduce = getSelectionPercent(selectionTable);

	//populate reproduction table with selected from selection table.
	fillReproductionTable(selectionTable, percentToReproduce);

	//send toReproduce gene stacks over to the crossover class.
	//cross.getGeneStacks(toReproduceTable);
	cross.fullCrossover(toReproduceTable);

	//clear the selection and reproduction tables ready for the next species and set percentToReproduce back to 0;
	selectionTable.clear();
	toReproduceTable.clear();
	percentToReproduce = 0;
}

void Selection::fillSelectionTable(SpeciesInfo species)
{
	//fail safe, if filling with a new species data, the selectionTable should be clear, check that...
	if (selectionTable.size() == 0)
	{
		//get the size of species membership.
		uint32_t size = species.speciesMembership.size();
		//reserve this space in the selection table, more efficient than increasing size one element at a time in the below loop.
		selectionTable.reserve(size);
		//fill the selection table with the paired variables of the creatures threshold score and their gene stacks.
		for (int i = 0; i < size; i++)
			selectionTable.push_back(std::make_pair(species.speciesMembership.at(i).thresholdScore, species.speciesMembership.at(i).geneStack));
	}
	else
		std::cout << "WARNING - SELECTION - fillSelectionTable() - trying to add two different species to same selectionTable" << std::endl;
}

void Selection::fillReproductionTable(std::vector<std::pair<float, std::vector<float>>> selectTable, uint32_t numToReprod)
{
	//fail safe, if filling with a new species data the toReproduceTable should be clear, check that...
	if (toReproduceTable.size() == 0)
	{
		//reserve the size of the toReproduceTable to percentToReproduce as we know it's this size and more efficient than just adding an element each time.
		toReproduceTable.reserve(numToReprod);
		//take the gene stacks from the selectionTable up to the percentageToReproduce value element.
		for (int i = 0; i < numToReprod; i++)
			toReproduceTable.push_back(selectTable.at(i));
	}
	else
		std::cout << "WARNING - SELECTION - fillReproductionTable() - trying to add two different species to same toReproduceTable" << std::endl;
}

uint32_t Selection::getSelectionPercent(std::vector<std::pair<float, std::vector<float>>> selectTable)
{
	//get the % of the selected table.
	uint32_t result = static_cast<int>((selectTable.size() * 0.01f) * selectionPercentage);
	//need an even number of creatures to pair up, check percentage is even, if not, add 1 to make so.
	if (result % 2 != 0)
		result += 1;
	//return the result.
	return result;
}
