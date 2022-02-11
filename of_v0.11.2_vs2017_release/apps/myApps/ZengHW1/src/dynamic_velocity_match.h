#pragma once
#include "rigidBody.h"
#include "dynamic_steering.h"

class DynamicVelocityMatch {
public:
	RigidBody* characterRB;
	RigidBody* targetRB;

	float maxAcceleration;
	float timeToTarget;

	DynamicVelocityMatch(RigidBody* i_character, RigidBody* i_target, float i_maxAcceleration, float i_timeToTarget = 0.1) :
		characterRB(i_character), targetRB(i_target), maxAcceleration(i_maxAcceleration), timeToTarget(i_timeToTarget) {};

	~DynamicVelocityMatch() {};

	DynamicSteeringOutput getSteering();
};