#pragma once
#include "dynamic_arrive.h"

DynamicSteeringOutput DynamicArrive::getSteering()
{
	DynamicSteeringOutput result;
	glm::vec2 targetVelocity;
	float targetSpeed;

	// Get the direction to the target.
	glm::vec2 direction = targetRB->position - characterRB->position;
	float distance = glm::distance(targetRB->position, characterRB->position);

	// Check if we are there, return no steering.
	if (distance < targetRadius) {
		result.linearAccel = glm::vec2(0, 0);
		result.rotAccel = 0;
		return result;
	}
	
	// If we are outside the slowRadius, then move at max speed.
	if (distance > slowRadius) {
		targetSpeed = maxSpeed;
	}
	// Otherwise calculate a scaled speed.
	else {
		targetSpeed = maxSpeed * distance / slowRadius;
	}

	// The target velocity combines speed and direction.
	targetVelocity = glm::normalize(direction);
	targetVelocity *= targetSpeed;

	// Acceleration tries to get to the target velocity.
	result.linearAccel = targetVelocity - characterRB->velocity;
	result.linearAccel /= timeToTarget;

	// Check if the acceleration is too fast.
	if (glm::length(result.linearAccel) > maxAcceleration) {
		result.linearAccel = glm::normalize(result.linearAccel) * maxAcceleration;
	}

	result.rotAccel = 0;
	return result;
}
