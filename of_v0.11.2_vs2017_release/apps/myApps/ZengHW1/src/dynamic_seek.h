#pragma once
#include "rigidBody.h"
#include "dynamic_steering.h"

class DynamicSeek {
public:
	RigidBody* characterRB;
	RigidBody* targetRB;

	float maxAcceleration;

	DynamicSeek(RigidBody* i_character, RigidBody* i_target, float i_maxAcceleration) :
		characterRB(i_character), targetRB(i_target), maxAcceleration(i_maxAcceleration) {};

	~DynamicSeek() {};

	DynamicSteeringOutput getSteering();
};