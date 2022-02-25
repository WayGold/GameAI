#pragma once
#include "ofGraphics.h"
#include "dynamic_steering.h"
#include "kinematic_steering.h"

class RigidBody {
public:
	glm::vec2 position;
	float orientation;

	glm::vec2 velocity;
	float rotVelocity;

	float mass;

	RigidBody();
	~RigidBody();

	void update(DynamicSteeringOutput i_steering, float i_maxSpeed, float i_maxRotation, float i_time);
	void update(KinematicSteeringOutput i_steering, float i_maxSpeed, float i_maxRotation, float i_time);
};