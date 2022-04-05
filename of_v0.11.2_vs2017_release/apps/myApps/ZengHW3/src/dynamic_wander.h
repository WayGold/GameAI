#pragma once
#include "dynamic_face.h"
#include "dynamic_seek.h"
#include "dynamic_look_where_you_are_going.h"
#include <random>

class DynamicWander {
public:
	DynamicLookWhereYouAreGoing* dynamicLookWhereYouAreGoing = nullptr;
	DynamicFace* dynamicFace = nullptr;
	DynamicSeek* dynamicSeek = nullptr;
	
	RigidBody* characterRB;
	RigidBody* explicitTarget = nullptr;

	float maxAngularAcceleration;
	float maxRotation;
	float maxAcceleration;

	float targetRadius;
	float slowRadius;
	float timeToTarget;
	float wanderOffset;
	float wanderRate;

	DynamicWander(RigidBody* i_character, float i_maxAngularAcceleration, float i_maxRotation, 
		float i_maxAcceleration, float i_targetRadius, float i_slowRadius,
		float i_wanderOffset, float i_wanderRate, float i_timeToTarget = 0.1) :
		characterRB(i_character), maxAngularAcceleration(i_maxAngularAcceleration),
		maxRotation(i_maxRotation), maxAcceleration(i_maxAcceleration), targetRadius(i_targetRadius), 
		slowRadius(i_slowRadius), timeToTarget(i_timeToTarget), wanderOffset(i_wanderOffset), 
		wanderRate(i_wanderRate){};
	~DynamicWander();

	// Flag false -> delegate DynamicLookWhereYouAreGoing, else delegate DynamicFace
	DynamicSteeringOutput getSteering(bool flag = false);

	inline float randomBinomial() {
		return static_cast<float>(rand()) / static_cast<float>(RAND_MAX) -
			static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	}
};