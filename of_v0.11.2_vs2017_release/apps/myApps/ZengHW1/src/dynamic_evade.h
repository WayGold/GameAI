#pragma once
#include "dynamic_flee.h"

class DynamicEvade {
public:
	DynamicFlee* dynamicFlee;
	RigidBody* characterRB;
	RigidBody* targetRB;
	RigidBody* explicitTarget;

	float maxPrediction;
	float maxAcceleration;
	float safeRadius;
	float decayCoef;

	DynamicEvade(RigidBody* i_character, RigidBody* i_target, float i_maxPrediction,
		float i_maxAcceleration, float i_safeRadius, float i_decayCoef) :
		dynamicFlee(nullptr), characterRB(i_character), targetRB(i_target),
		maxPrediction(i_maxPrediction), maxAcceleration(i_maxAcceleration),
		explicitTarget(new RigidBody()), safeRadius(i_safeRadius), decayCoef(i_decayCoef) {};
	~DynamicEvade();

	DynamicSteeringOutput getSteering();
};