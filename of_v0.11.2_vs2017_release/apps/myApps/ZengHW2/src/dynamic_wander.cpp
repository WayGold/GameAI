#include "dynamic_wander.h"

DynamicWander::~DynamicWander()
{
	if(explicitTarget)
		delete explicitTarget;
	if (dynamicFace)
		delete dynamicFace;
	if (dynamicSeek)
		delete dynamicSeek;
	if (dynamicLookWhereYouAreGoing)
		delete dynamicLookWhereYouAreGoing;
}

DynamicSteeringOutput DynamicWander::getSteering(bool flag)
{
	DynamicSteeringOutput result;
	float targetOrient;
	glm::vec2 direction, targetDirection;

	// Calc character orientation unit vector with orientation
	direction.x = cosf(characterRB->orientation);
	direction.y = sinf(characterRB->orientation);
	direction = glm::normalize(direction);

	// Calc target orientation and orientation unit vector
	targetOrient = abs(wanderRate - characterRB->orientation) * randomBinomial();
	targetDirection.x = cosf(targetOrient);
	targetDirection.y = sinf(targetOrient);
	targetDirection = glm::normalize(targetDirection);

	// Put up the wander target
	explicitTarget = new RigidBody();
	explicitTarget->orientation = targetOrient;
	explicitTarget->position = direction * wanderOffset + targetDirection + characterRB->position;

	// delegate to seek
	dynamicSeek = new DynamicSeek(characterRB, explicitTarget, maxAcceleration);
	result.linearAccel = dynamicSeek->getSteering().linearAccel;

	if (flag) {
		// delegate to face
		dynamicFace = new DynamicFace(characterRB, explicitTarget, maxAngularAcceleration, maxRotation, targetRadius, slowRadius);
		result.rotAccel = dynamicFace->getSteering().rotAccel;
	}
	else {
		// delegate to LookWhereYouAreGoing
		dynamicLookWhereYouAreGoing = new DynamicLookWhereYouAreGoing(characterRB, maxAngularAcceleration, maxRotation, targetRadius, slowRadius);
		result.rotAccel = dynamicLookWhereYouAreGoing->getSteering().rotAccel;
	}

	return result;
}
