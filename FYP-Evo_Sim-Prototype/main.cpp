/** \file main.cpp */

#include <iostream>


struct Environment
{
	float energy_available;
	float temperature;
};

struct Creature
{
	float energy_demand;
	float ideal_temperature;
	float temperature_range;
	bool alive;
};






int main()
{

	struct Environment envir[1];
	struct Creature creat[7];

	envir[0].energy_available = 500.0f;
	envir[0].temperature = 12.0f;

#pragma region TEST ENERGY AVAILABLE.
	//creature 0 - should be ideally suited to environment 0.
	creat[0].energy_demand		= 400.0f;		//in range of environ energy.
	creat[0].ideal_temperature	= 12.0f;		//same as environ temp.
	creat[0].temperature_range	= 1.0f;
	creat[0].alive = true;

	//creature 1 - should NOT be suited to environment 0.
	creat[1].energy_demand		= 650.0f;		//over the range, not even environ energy.
	creat[1].ideal_temperature	= 12.0f;		//same as environ temp.
	creat[1].temperature_range	= 1.0f;
	creat[1].alive = true;
#pragma endregion

#pragma region TEST TEMPERATURE.
	//creature 2 - should NOT be suited to environment 0.
	creat[2].energy_demand = 650.0f;		//over the range, not even environ energy.
	creat[2].ideal_temperature = 12.0f;		//same as environ temp.
	creat[2].temperature_range = 1.0f;
	creat[2].alive = true;

	//creature 2 - should NOT be suited to environment 0.
	creat[3].energy_demand = 650.0f;		//over the range, not even environ energy.
	creat[3].ideal_temperature = 12.0f;		//same as environ temp.
	creat[3].temperature_range = 1.0f;
	creat[3].alive = true;
#pragma endregion

	//TEST TEMPERATURE TOLERANCE RANGES.
	//creature  - should be survive in environment 0, even with slightly different ideal temp, it is within tolerance range.
	creat[4].energy_demand		= 200.0f;		//in range of environ energy.
	creat[4].ideal_temperature	= 10.0f;		//a little off environ temp.
	creat[4].temperature_range	= 3.0f;			//large range, should keep creature in tolerance temp range.
	creat[4].alive = true;

	//creature  - should be survive in environment 0, even with slightly different ideal temp, it is within tolerance range.
	creat[5].energy_demand		= 200.0f;		//in range of environ energy.
	creat[5].ideal_temperature	= 10.0f;		//a little off environ temp.
	creat[5].temperature_range	= 3.0f;			//large range, should keep creature in tolerance temp range.
	creat[5].alive = true;

	//creature  - should be survive in environment 0, even with slightly different ideal temp, it is within tolerance range.
	creat[6].energy_demand		= 200.0f;		//in range of environ energy.
	creat[6].ideal_temperature	= 10.0f;		//a little off environ temp.
	creat[6].temperature_range	= 3.0f;			//large range, should keep creature in tolerance temp range.
	creat[6].alive = true;




    std::cout << "YOU BUM!!!" << std::endl;

	//std::cout << "Environmental Energy Available is " + 
}



//function to 



//function to



//function to 


