#include "dynamic_evade.h"

DynamicEvade::~DynamicEvade()
{
	delete explicitTarget;
	delete dynamicFlee;
}

DynamicSteeringOutput DynamicEvade::getSteering()
{

	DynamicSteeringOutput result;
	glm::vec2 direction, predictDirection;
	float distance, speed, prediction, predictionDistance, strength;

	/* 1. Calculate the target to delegate to seek */
	// Work out the distance to target.
	direction = targetRB->position - characterRB->position;
	distance = glm::distance(targetRB->position, characterRB->position);

	// Work out our current speed.
	speed = glm::length(characterRB->velocity);

	// Check if speed gives a reasonable prediction time.
	if (speed <= distance / maxPrediction) {
		prediction = maxPrediction;
	}
	// Otherwise calculate the prediction time.
	else {
		prediction = distance / speed;
	}

	// Put the target together.
	explicitTarget->position = targetRB->position + targetRB->velocity * prediction;
	
	// Case 1: Outside Safe Radius
	predictDirection = explicitTarget->position - characterRB->position;
	predictionDistance = glm::length(predictDirection);
	if (predictionDistance > safeRadius) {
		strength = 0;
	}
	else {
		// Case 2: Within Radius - Need to Evade
		// Inverse Square to calc strength
		strength = min(decayCoef / predictionDistance * predictionDistance, maxAcceleration);
	}

	// Delegate to Flee.
	dynamicFlee = new DynamicFlee(characterRB, explicitTarget, strength);
	result = dynamicFlee->getSteering();

	return result;
}
