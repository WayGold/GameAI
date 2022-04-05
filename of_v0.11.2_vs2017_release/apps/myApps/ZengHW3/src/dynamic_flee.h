#pragma once
#include "rigidBody.h"
#include "dynamic_steering.h"

class DynamicFlee {
public:
	RigidBody* characterRB;
	RigidBody* targetRB;

	float maxAcceleration;

	DynamicFlee(RigidBody* i_character, RigidBody* i_target, float i_maxAcceleration) :
		characterRB(i_character), targetRB(i_target), maxAcceleration(i_maxAcceleration) {};

	~DynamicFlee() {};

	DynamicSteeringOutput getSteering();
};