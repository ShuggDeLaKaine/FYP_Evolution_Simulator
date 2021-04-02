/** \file mutation.h */
#pragma once
#include <iostream>
#include "core/generalFunctions.h"
#include "environments/environment.h"


/*	\class Mutation
*	\brief Class...
*/
class Mutation
{
public:
	Mutation();					//!< constructor.
	~Mutation();				//!< deconstructor.
	bool mutationTest(float mutationChance);		//!< test to result true/false whether a creatures var should mutate.
	void mutationIntensity(float mutPercent, float &eleToMut, float envirMulti);	//!< function to result strength of mutation...

	uint32_t iPosMuts = 0;		//!< for testing mutations, that they are both positive and negative.
	uint32_t iNegMuts = 0;		//!< for testing mutations, that they are both positive and negative.
	float fPosMutsTally = 0.0f;	//!< for testing mutations, tally of combined total of positive mutation values.
	float fNegMutsTally = 0.0f;	//!< for testing mutations, tally of combined total of negative mutation values.

private:
	void setEnvironModifier(float envirMulti) { envMod = envirMulti; }		//!< set the environmental modifier.

	float mutIntensity;			//!< value of the intensity of the mutation, the range in which a value can mutate.
	float mutChance;			//!< chance of the mutation taking place.
	float envMod;				//!< modifying value of any environmental impacts.

	std::shared_ptr<GeneralFunctions> genFunc;	//!< pointer ref to general functions class.	
	Environment envir;							//!< ref to Environment struct.
};