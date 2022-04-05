#pragma once
#include "ofMain.h"

struct DynamicSteeringOutput {
	glm::vec2 linearAccel;
	float rotAccel;

	inline DynamicSteeringOutput operator+=(const DynamicSteeringOutput& rhs) {
		linearAccel += rhs.linearAccel;
		rotAccel += rhs.rotAccel;
		return *this;
	}
};