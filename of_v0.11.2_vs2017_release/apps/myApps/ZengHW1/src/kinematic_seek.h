#pragma once
#pragma once
#include "rigidBody.h"
#include "kinematic_steering.h"

class KinematicSeek {
public:
	RigidBody* characterRB;
	RigidBody* targetRB;

	float maxSpeed;

	KinematicSeek(RigidBody* i_character, RigidBody* i_target, float i_maxSpeed) :
		characterRB(i_character), targetRB(i_target), maxSpeed(i_maxSpeed) {};

	~KinematicSeek() {};

	KinematicSteeringOutput getSteering();
};