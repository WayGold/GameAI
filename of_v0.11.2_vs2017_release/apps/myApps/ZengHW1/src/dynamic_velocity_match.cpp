#include "dynamic_velocity_match.h"

DynamicSteeringOutput DynamicVelocityMatch::getSteering()
{
	DynamicSteeringOutput result;

	// Acceleration tries to get to the target velocity.
	result.linearAccel = targetRB->velocity - characterRB->velocity;
	result.linearAccel /= timeToTarget;

	// Check if the acceleration is too fast.
	if (glm::length(result.linearAccel) > maxAcceleration) {
		result.linearAccel = glm::normalize(result.linearAccel) * maxAcceleration;
	}

	result.rotAccel = 0;

	return result;
}
