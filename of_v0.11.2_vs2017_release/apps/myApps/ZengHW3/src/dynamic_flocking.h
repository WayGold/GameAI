#pragma once
#include "dynamic_seperation.h"
#include "dynamic_arrive.h"
#include "dynamic_velocity_match.h"
#include <vector>

class DynamicFlocking {
public:
	RigidBody* characterRB;
	RigidBody* centroid = nullptr;
	vector<RigidBody*> flock;

	DynamicSeperation* dynamicSeperation;
	DynamicArrive* dynamicArrive;
	DynamicVelocityMatch* dynamicVelocityMatch;

	float maxPrediction;
	float maxSpeed;
	float maxAcceleration;
	float decayCoef;
	float safeRadius;
	float targetRadius;
	float slowRadius;
	float timeToTarget;

	DynamicFlocking(RigidBody* i_character, vector<RigidBody*> i_targets, float i_maxPrediction,
		float i_maxAcceleration, float i_safeRadius, float i_decayCoef, float i_maxSpeed, 
		float i_targetRadius, float i_slowRadius, float i_timeToTarget = 0.1) :
		dynamicSeperation(nullptr), dynamicArrive(nullptr), dynamicVelocityMatch(nullptr),
		characterRB(i_character), flock(i_targets), maxPrediction(i_maxPrediction), 
		maxAcceleration(i_maxAcceleration), safeRadius(i_safeRadius), decayCoef(i_decayCoef),
		maxSpeed(i_maxSpeed), targetRadius(i_targetRadius), slowRadius(i_slowRadius), timeToTarget(i_timeToTarget) {};
	~DynamicFlocking();

	DynamicSteeringOutput getSteering();
};