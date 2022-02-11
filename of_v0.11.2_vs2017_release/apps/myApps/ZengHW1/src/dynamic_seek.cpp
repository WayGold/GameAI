#include "dynamic_seek.h"

DynamicSteeringOutput DynamicSeek::getSteering()
{
	DynamicSteeringOutput result;

	// Get the direction to the target.
	result.linearAccel = targetRB->position - characterRB->position;

	// Give full acceleration along this direction.
	result.linearAccel = glm::normalize(result.linearAccel);
	result.linearAccel *= maxAcceleration;
	
	result.rotAccel = 0;

	return result;
}
