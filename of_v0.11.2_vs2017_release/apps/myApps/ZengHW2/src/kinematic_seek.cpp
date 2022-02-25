#include "kinematic_seek.h"

KinematicSteeringOutput KinematicSeek::getSteering()
{
	KinematicSteeringOutput result;

	// Get the direction to the target.
	result.linearVelocity = targetRB->position - characterRB->position;

	// Give full acceleration along this direction.
	result.linearVelocity = glm::normalize(result.linearVelocity);
	result.linearVelocity *= maxSpeed;

	result.rotVelocity = 0;

	return result;
}
