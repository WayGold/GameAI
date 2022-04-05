#pragma once
#include "ofMain.h"

struct KinematicSteeringOutput {
	glm::vec2 linearVelocity;
	float rotVelocity;

	inline KinematicSteeringOutput operator+=(const KinematicSteeringOutput& rhs) {
		linearVelocity += rhs.linearVelocity;
		rotVelocity += rhs.rotVelocity;
		return *this;
	}
};