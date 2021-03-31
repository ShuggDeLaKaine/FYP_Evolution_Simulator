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
	~Mutation() {};				//!< deconstructor.
	bool mutationTest(float mutationChance);		//!< test to result true/false whether a creatures var should mutate.
	void mutationIntensity(float mutPercent, float &eleToMut, float envirMulti);	//!< function to result strength of mutation...

private:
	void setEnvironModifier(float envirMulti) { envMod = envirMulti; }		//!< set the environmental modifier.

	float mutIntensity;		//!< value of the intensity of the mutation, the range in which a value can mutate.
	float mutChance;		//!< chance of the mutation taking place.
	float envMod;			//!< modifying value of any environmental impacts.

	std::shared_ptr<GeneralFunctions> genFunc;	//!< pointer ref to general functions class.	
	Environment envir;							//!< ref to Environment struct.
};