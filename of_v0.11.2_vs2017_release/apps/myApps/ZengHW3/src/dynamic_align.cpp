#include "dynamic_align.h"

DynamicSteeringOutput DynamicAlign::getSteering()
{
	DynamicSteeringOutput result;
	float rotation, rotationSize, targetRotation, angularAcceleration;

	// Get the naive direction to the target.
	rotation = targetRB->orientation - characterRB->orientation;

	// Map the result to the (-pi, pi) interval.
	rotation = mapToRange(rotation);
	rotationSize = glm::abs(rotation);

	// Check if we are there, return no steering.
	if (rotationSize < targetRadius) {
		result.linearAccel = glm::vec2(0, 0);
		result.rotAccel = 0;
		return result;
	}

	// If we are outside the slowRadius, then use maximum rotation.
	if (rotationSize > slowRadius) {
		targetRotation = maxRotation;
	}
	// Otherwise calculate a scaled rotation.
	else {
		targetRotation = maxRotation * rotationSize / slowRadius;
	}

	// The final target rotation combines speed (already in the variable) and direction.
	targetRotation *= rotation / rotationSize;

	// Acceleration tries to get to the target rotation.
	result.rotAccel = (targetRotation - characterRB->rotVelocity) / timeToTarget;

	// Check if the acceleration is too great. Clamp to maxAngularAccel if too great.
	angularAcceleration = glm::abs(result.rotAccel);
	if (angularAcceleration > maxAngularAcceleration) {
		result.rotAccel /= angularAcceleration;
		result.rotAccel *= maxAngularAcceleration;
	}

	result.linearAccel = glm::vec2(0, 0);

	return result;
}

float DynamicAlign::mapToRange(float i_rotation)
{
	constexpr float pi = glm::pi<float>();

	while (i_rotation > pi) {
		i_rotation -= 2 * pi;
	}

	while (i_rotation < -pi) {
		i_rotation += 2 * pi;
	}

	return i_rotation;
}
