/** file randomNumberGenerator.h */
#pragma once

#include <random>
#include "system.h"


/*	\class GeneralFunctions
*	\brief Class...
*/
class	GeneralFunctions : public System
{
public:
	virtual void start(SystemSignal init = SystemSignal::None, ...);	//!< start the system.
	virtual void stop(SystemSignal close = SystemSignal::None, ...);	//!< stop the system.

	static int32_t uniformIntBetween(int32_t min, int32_t max);			//!< get an int between min and max params.
	static float   uniformFloatBetween(float min, float max);			//!< get a float between min and max params.

	static int32_t normalIntBetween(float c, float sigma);				//!< get an int from a gaussian distribution described by C & sigma.
	static float   normalFloatBetween(float c, float sigma);			//!< get an float from a gaussian distribution described by C & sigma.

	static float roundFloat(float val);									//!< func to round a float to 2 decimal floats.

private:
	static std::shared_ptr<std::mt19937> s_generator;					//!< random number generating engine.
	static std::uniform_int_distribution<int32_t> s_uniformInt;			//!< uniform int distribution.
	static std::uniform_real_distribution<float> s_uniformFloat;		//!< uniform float distribution.
	static float s_intRange;											//!< range of int32.
	static float s_floatRange;											//!< range of float.
};