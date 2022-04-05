#pragma once
#include "dynamic_align.h"

class DynamicFace {
public:
	DynamicAlign* dynamicAlign;
	RigidBody* characterRB;
	RigidBody* targetRB;
	RigidBody* explicitTarget;

	float maxAngularAcceleration;
	float maxRotation;

	float targetRadius;
	float slowRadius;
	float timeToTarget;

	DynamicFace(RigidBody* i_character, RigidBody* i_target, float i_maxAngularAcceleration,
		float i_maxRotation, float i_targetRadius, float i_slowRadius, float i_timeToTarget = 0.1) :
		characterRB(i_character), targetRB(i_target), maxAngularAcceleration(i_maxAngularAcceleration),
		maxRotation(i_maxRotation), targetRadius(i_targetRadius), slowRadius(i_slowRadius), 
		timeToTarget(i_timeToTarget), dynamicAlign(nullptr), explicitTarget(new RigidBody()){};
	~DynamicFace();

	DynamicSteeringOutput getSteering();
};