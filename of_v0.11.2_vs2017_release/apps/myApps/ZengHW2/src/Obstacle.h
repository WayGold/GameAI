#pragma once
#include "ofGraphics.h"
#include "ofMain.h"
#include "rigidBody.h"

class Obstacle {
public:
	RigidBody* obstacleRB;
	float width, height;
	ofColor obstacleColor;

	glm::vec2 top_left;
	glm::vec2 top_right;
	glm::vec2 bottom_left;
	glm::vec2 bottom_right;

	Obstacle();
	Obstacle(glm::vec2 i_pos, float i_width, float i_height, ofColor i_Color);
	~Obstacle();

	void draw();

};