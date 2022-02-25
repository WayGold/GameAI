#pragma once
#include "dynamic_evade.h"
#include <vector>

class DynamicSeperation {
public:
	DynamicEvade* dynamicEvade;
	RigidBody* characterRB;
	vector<RigidBody*> targetRBs;

	float maxPrediction;
	float maxAcceleration;
	float safeRadius;
	float decayCoef;

	DynamicSeperation(RigidBody* i_character, vector<RigidBody*> i_targets, float i_maxPrediction,
		float i_maxAcceleration, float i_safeRadius, float i_decayCoef) :
		dynamicEvade(nullptr), characterRB(i_character), targetRBs(i_targets),
		maxPrediction(i_maxPrediction), maxAcceleration(i_maxAcceleration),
		safeRadius(i_safeRadius), decayCoef(i_decayCoef) {};
	~DynamicSeperation();

	DynamicSteeringOutput getSteering();
};