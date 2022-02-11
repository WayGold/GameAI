#pragma once
#include "ofGraphics.h"

// Bounding Box Collider
class Collider {
public:
	float width;
	float height;
	glm::vec2 center;

	Collider(float i_width, float i_height, glm::vec2 i_center);
	~Collider();
};