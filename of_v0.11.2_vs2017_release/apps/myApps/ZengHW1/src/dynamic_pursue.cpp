#include "dynamic_pursue.h"

DynamicPursue::~DynamicPursue()
{
	delete explicitTarget;
	delete dynamicSeek;
}

DynamicSteeringOutput DynamicPursue::getSteering()
{
	DynamicSteeringOutput result;
	glm::vec2 direction;
	float distance, speed, prediction;

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

	// Delegate to Seek.
	dynamicSeek = new DynamicSeek(characterRB, explicitTarget, maxAcceleration);
	result = dynamicSeek->getSteering();

	return result;
}


