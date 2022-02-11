#include "dynamic_seperation.h"

DynamicSeperation::~DynamicSeperation()
{
	delete dynamicEvade;
}

DynamicSteeringOutput DynamicSeperation::getSteering()
{
	DynamicSteeringOutput result, accumResult;
	accumResult.linearAccel = glm::vec2(0, 0);
	accumResult.rotAccel = 0;
	
	for (auto it = targetRBs.begin(); it != targetRBs.end(); it++) {
		if (*it == characterRB)
			continue;
		if(dynamicEvade == nullptr)
			dynamicEvade = new DynamicEvade(characterRB, *it, maxPrediction, maxAcceleration, safeRadius, decayCoef);
		else {
			dynamicEvade->characterRB = characterRB;
			dynamicEvade->targetRB = *it;
		}

		result = dynamicEvade->getSteering();
		accumResult.linearAccel += result.linearAccel;
		accumResult.rotAccel += result.rotAccel;
	}

	return accumResult;
}
