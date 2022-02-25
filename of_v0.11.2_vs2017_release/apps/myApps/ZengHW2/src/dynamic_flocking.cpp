#include "dynamic_flocking.h"

DynamicFlocking::~DynamicFlocking()
{
	delete dynamicSeperation;
	delete dynamicArrive;
	delete dynamicVelocityMatch;
}

DynamicSteeringOutput DynamicFlocking::getSteering()
{
	DynamicSteeringOutput result;
	glm::vec2 centroidPos, centroidVel;

	centroid = new RigidBody();
	centroid->mass = 0;
	
	// Calculate Total Mass Of The Flock
	for (auto it = flock.begin(); it != flock.end(); it++) {
		centroid->mass += (*it)->mass;
	}

	// Calculate Centroid Position and Velocity
	centroid->position += characterRB->position * characterRB->mass / centroid->mass;
	centroid->velocity += characterRB->velocity * characterRB->mass / centroid->mass;
	for (auto it = flock.begin(); it != flock.end(); it++) {
		centroid->position += (*it)->position * (*it)->mass / centroid->mass;
		centroid->velocity += (*it)->velocity * (*it)->mass / centroid->mass;
	}

	// Delegate to Seperation
	dynamicSeperation = new DynamicSeperation(characterRB, flock, maxPrediction, maxAcceleration, safeRadius, decayCoef);
	result = dynamicSeperation->getSteering();

	// Delegate to Velocity Match
	dynamicVelocityMatch = new DynamicVelocityMatch(characterRB, centroid, maxAcceleration);
	result += dynamicVelocityMatch->getSteering();

	// Delegate to Arrive
	dynamicArrive = new DynamicArrive(characterRB, centroid, maxAcceleration, maxSpeed, targetRadius, slowRadius);
	result += dynamicArrive->getSteering();

	// Check if the acceleration is too fast.
	if (glm::length(result.linearAccel) > maxAcceleration) {
		result.linearAccel = glm::normalize(result.linearAccel) * maxAcceleration;
	}

	return result;
}
