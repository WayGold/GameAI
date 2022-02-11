#include "dynamic_look_where_you_are_going.h"

DynamicLookWhereYouAreGoing::~DynamicLookWhereYouAreGoing()
{
	delete targetRB;
	delete dynamicAlign;
}

DynamicSteeringOutput DynamicLookWhereYouAreGoing::getSteering()
{
	DynamicSteeringOutput result;
	glm::vec2 velocity;

	// 1. Calculate the target to delegate to align
	// Check for a zero direction, and make no change if so.
	velocity = characterRB->velocity;
	if (glm::length(velocity) < 0.001) {
		result.linearAccel = glm::vec2(0.0f, 0.0f);
		result.rotAccel = 0.0f;
		return result;
	}

	// Otherwise set the target based on the velocity.
	targetRB = new RigidBody();
	targetRB->orientation = atan2(velocity.y, velocity.x);

	// 2. Delegate to align.
	dynamicAlign = new DynamicAlign(characterRB, targetRB, maxAngularAcceleration,
									maxRotation, targetRadius, slowRadius);
	result = dynamicAlign->getSteering();

	return result;
}
