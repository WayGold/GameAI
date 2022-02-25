#pragma once
#include "dynamic_seek.h"

class DynamicPursue{
public:
	DynamicSeek* dynamicSeek;
	RigidBody* characterRB;
	RigidBody* targetRB;
	RigidBody* explicitTarget;

	float maxPrediction;
	float maxAcceleration;
	
	DynamicPursue(RigidBody* i_character, RigidBody* i_target, float i_maxPrediction, float i_maxAcceleration) :
		dynamicSeek(nullptr), characterRB(i_character), targetRB(i_target), 
		maxPrediction(i_maxPrediction), maxAcceleration(i_maxAcceleration), explicitTarget(new RigidBody()) {};
	~DynamicPursue();

	DynamicSteeringOutput getSteering();
};