#include "rigidBody.h"

RigidBody::RigidBody()
{
	this->position = glm::vec2(0.0f, 0.0f);
	this->orientation = 0.0f;
	this->velocity = glm::vec2(0.0f, 0.0f);
	this->rotVelocity = 0;
	this->mass = 0;
}

RigidBody::~RigidBody()
{
}

void RigidBody::update(DynamicSteeringOutput i_steering, float i_maxSpeed, float i_maxRotation, float i_time)
{
	// Update the position and orientation.
	position += velocity * i_time;
	orientation += rotVelocity * i_time;

	// Update velocity and rotation.
	velocity += i_steering.linearAccel * i_time;
	rotVelocity += i_steering.rotAccel * i_time;

	// Check for speeding and clip.
	if (glm::length(velocity) > i_maxSpeed) {
		velocity = glm::normalize(velocity);
		velocity *= i_maxSpeed;
	}

	// Check for rot speeding and clip.
	if (glm::length(rotVelocity) > i_maxRotation) {
		rotVelocity = i_maxRotation;
	}

	// Check for border of window
	while (position.x > 1024.0f) {
		position.x -= 1024.0f;
	}
	while (position.x < 0.0f) {
		position.x += 1024.0f;
	}
	while (position.y > 768.0f) {
		position.y -= 768.0f;
	}
	while (position.y < 0) {
		position.y += 768.0f;
	}
}

void RigidBody::update(KinematicSteeringOutput i_steering, float i_maxSpeed, float i_maxRotation, float i_time)
{
	// Update the position and orientation.
	position += velocity * i_time;
	orientation = atan2(velocity.y, velocity.x);

	// Update velocity and rotation.
	velocity = i_steering.linearVelocity;
	rotVelocity = i_steering.rotVelocity;

	// Check for speeding and clip.
	if (glm::length(velocity) > i_maxSpeed) {
		velocity = glm::normalize(velocity);
		velocity *= i_maxSpeed;
	}

	// Check for rot speeding and clip.
	if (glm::length(rotVelocity) > i_maxRotation) {
		rotVelocity = i_maxRotation;
	}

	// Check for border of window
	while (position.x > 1024.0f) {
		position.x -= 1024.0f;
	}
	while (position.x < 0.0f) {
		position.x += 1024.0f;
	}
	while (position.y > 768.0f) {
		position.y -= 768.0f;
	}
	while (position.y < 0) {
		position.y += 768.0f;
	}
}

