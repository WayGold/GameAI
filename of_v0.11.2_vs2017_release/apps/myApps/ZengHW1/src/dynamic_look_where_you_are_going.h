#pragma once
#include "dynamic_align.h"

class DynamicLookWhereYouAreGoing {
public:
	DynamicAlign* dynamicAlign;
	RigidBody* characterRB;
	RigidBody* targetRB;

	float maxAngularAcceleration;
	float maxRotation;

	float targetRadius;
	float slowRadius;
	float timeToTarget;

	DynamicLookWhereYouAreGoing(RigidBody* i_character, float i_maxAngularAcceleration,
		float i_maxRotation, float i_targetRadius, float i_slowRadius, float i_timeToTarget = 0.1) :
		characterRB(i_character), targetRB(nullptr), maxAngularAcceleration(i_maxAngularAcceleration),
		maxRotation(i_maxRotation), targetRadius(i_targetRadius), slowRadius(i_slowRadius),
		timeToTarget(i_timeToTarget), dynamicAlign(nullptr) {};
	~DynamicLookWhereYouAreGoing();

	DynamicSteeringOutput getSteering();
};