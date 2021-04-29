/**\file selection.h  */
#pragma once
#include "core/generalFunctions.h"
#include "creatures/species.h"
#include "creatures/creature.h"
#include "reproduction/crossover.h"


/* \struct greater
*  \brief Struct greater that is used in sorting table to be descending value without having to worry about different types used for the number (float, int, long etc)
*/
struct greater
{
	template<class T>
	bool operator()(T const &a, T const &b) const { return a > b; }
};

/*	\class Selection
*	\brief Class...
*/
class Selection
{
public:
	
	Selection() {};			//!< constructor.
	~Selection() {};		//!< deconstructor.

	std::vector<std::pair<float, std::vector<float>>> parentSelection(SpeciesInfo species);

	void fillSelectionTable(SpeciesInfo species);
	void fillReproductionTable(std::vector<std::pair<float, std::vector<float>>> selectTable, uint32_t numToReprod);

	uint32_t getSelectionPercent(std::vector<std::pair<float, std::vector<float>>> selectTable);
	inline void setSelectionPercentage(uint32_t desiredPercentage) { selectionPercentage = desiredPercentage; };

	float selectionPercentage = 30.0f;
private:
	Crossover cross;			//!< ref to Crossover class.

	std::vector<std::pair<float, std::vector<float>>> selectionTable;	//!< vector of pairs, contains a float (for the threshold score) and another vector of floats (for the gene stack of the creature). 
	std::vector<std::pair<float, std::vector<float>>> toReproduceTable;	//!< vector of floats vectors, containing the gene stack information for those creatures which will reproduce.
	
	uint32_t percentToReproduce;
};