/*
#include <gtest/gtest.h>
#include "main.cpp"

TEST()
{

	
}

*/

/* //ESPECIALLY USEFUL FOR COMPARING THE HIGHEST DIFFERENCE TO THE MUTATION INTENSITY.
	//testing mutation chance & intensity functions.
	float testRuns = 1000000;
	int yesMut = 0;
	int noMut = 0;
	float mutChance = 2.5f;
	float mutInten = 1.0f;
	float enMulti = 1.0f;


	if(mutInten > 0.05f)
	{
		//NOTE BELOW LINE ONLY REALLY WORKS IF mutInten is dividable by 0.05f.
		int timesToRun = mutInten / 0.05f;		//should be 20 if mutInten starts at 1.0f.

		for (int i = 0; i < timesToRun; i++)
		{
			float diff = 0.0f;
			float avDiff = 0.0f;
			float highDiff = diff;
			float largeMutList = 0;
			float largeMutPercent = 0.0f;

			for (int j = 0; j < testRuns; j++)
			{
				if (mut.mutationTest(mutChance) == true)
				{
					float element2Mutate = 100.0f;

					mut.mutationIntensity(mutInten, element2Mutate, enMulti);
					diff = element2Mutate - 100.0f;

					//set to a positive value if negative.
					if (diff < 0.0f)
						diff = diff * -1.0f;

					//check if a large change.
					if (diff >= 1.0f)
						largeMutList = largeMutList + 1.0f;

					//tally up the avDiff.
					avDiff += diff;

					//check if new diff is larger than highDiff, if so, set highDiff to the diff value.
					if (diff > highDiff)
						highDiff = diff;
					//std::cout << "new mutated element value is: " << element2Mutate << std::endl;
					yesMut++;
				}
				else
					noMut++;
			}
			std::cout << "MUTATION INTENSITY IS: " << mutInten << std::endl;
			std::cout << "highest difference is: " << highDiff << std::endl;

			avDiff = avDiff / testRuns;
			std::cout << "average difference is: " << avDiff << std::endl;

			largeMutPercent = largeMutList / testRuns;
			std::wcout << "percentage of mutations over 1% change is: " << largeMutPercent << std::endl << std::endl;

			mutInten = mutInten - 0.05f;
		}

		//std::cout << "Over " << testRuns << " tests, number of YES mutations is: " << yesMut << " and number of NO mutations is: " << noMut << std::endl;
	}
*/