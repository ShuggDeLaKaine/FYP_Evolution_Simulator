/** \file generalFunctions.cpp */
#include "generalFunctions.h"
#include <chrono>



//initialising...
//setting shared pointer to nullptr.
std::shared_ptr<std::mt19937> UsefulFunctions::s_generator = nullptr;

//setting the number distributors between min and max of int32.
std::uniform_int_distribution<int32_t> UsefulFunctions::s_uniformInt = std::uniform_int_distribution<int32_t>(std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max());
std::uniform_real_distribution<float> UsefulFunctions::s_uniformFloat = std::uniform_real_distribution<float>(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());

//setting the ranges for int and float from max and min of their 32bit numeric limits.
float UsefulFunctions::s_intRange = static_cast<float>(std::numeric_limits<int32_t>::max() - (float)std::numeric_limits<int32_t>::min());
float UsefulFunctions::s_floatRange = std::numeric_limits<float>::max() - std::numeric_limits<float>::min();


void UsefulFunctions::start(SystemSignal init, ...)
{
	//when start, need to seed random number generator.
	//will reset the generator using the time now.
	auto timeNow = std::chrono::high_resolution_clock::now();
	s_generator.reset(new std::mt19937(timeNow.time_since_epoch().count()));
}

void UsefulFunctions::stop(SystemSignal close, ...)
{
	s_generator.reset();
}

int32_t UsefulFunctions::uniformIntBetween(int32_t min, int32_t max)
{
	//***PROBLEM HERE*** 
	//if 0 to 100, all fine...
	//if -100 to 0, all fine...
	//if -100 to 100 !!!PROBLEM!!! --- all negatives...???
	return min + (fabs(static_cast<float>(s_uniformInt(*s_generator))) / s_intRange) * (max - min);
}

float UsefulFunctions::uniformFloatBetween(float min, float max)
{
	float result = min + (fabs(s_uniformFloat(*s_generator)) / s_floatRange) * (max - min);
	result = roundFloat(result);
	return result;
}

int32_t UsefulFunctions::normalIntBetween(float c, float sigma)
{
	std::normal_distribution<float> distribution(c, sigma);
	return static_cast<int32_t>(distribution(*s_generator));
}

float UsefulFunctions::normalFloatBetween(float c, float sigma)
{
	std::normal_distribution<float> distribution(c, sigma);
	return distribution(*s_generator);
}

float UsefulFunctions::roundFloat(float val)
{
	//example: 
	//5.88888 * 100 = 588.888
	//588.888 + 0.5 = 589.388	//for rounding off the value
	//type cast to int = 589
	//divide by 100 = 5.89
	float value = (int)(val * 100 + 0.5f);
	return (float)value / 100;
}