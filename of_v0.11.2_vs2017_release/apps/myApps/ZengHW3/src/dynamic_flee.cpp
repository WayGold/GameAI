#include "dynamic_flee.h"

DynamicSteeringOutput DynamicFlee::getSteering()
{
	DynamicSteeringOutput result;

	// Get the direction to the target.
	result.linearAccel =  characterRB->position - targetRB->position;

	// Give full acceleration along this direction.
	result.linearAccel = glm::normalize(result.linearAccel);
	result.linearAccel *= maxAcceleration;

	result.rotAccel = 0;

	return result;
}