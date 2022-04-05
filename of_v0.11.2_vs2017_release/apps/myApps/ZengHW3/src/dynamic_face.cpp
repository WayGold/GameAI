#include "dynamic_face.h"

DynamicFace::~DynamicFace()
{
	delete explicitTarget;
	delete dynamicAlign;	
}

DynamicSteeringOutput DynamicFace::getSteering()
{
	DynamicSteeringOutput result;
	glm::vec2 direction;

	// 1. Calculate the target to delegate to align
	//  Work out the direction to target.
	direction = targetRB->position - characterRB->position;

	// Check for a zero direction, and make no change if so.
	if (glm::length(direction) < 0.001) {
		result.linearAccel = glm::vec2(0.0f, 0.0f);
		result.rotAccel = 0.0f;
		return result;
	}

	// Put the target together.
	explicitTarget->orientation = atan2(direction.y, direction.x);

	// 2. Delegate to align.
	dynamicAlign = new DynamicAlign(characterRB, explicitTarget, maxAngularAcceleration,
									maxRotation, targetRadius, slowRadius);
	result = dynamicAlign->getSteering();

	return result;
}
