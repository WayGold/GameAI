#pragma once
#include "ofGraphics.h"
#include "rigidBody.h"
#include "ofMain.h"

class Boid {
public:
	RigidBody* boidRB;
	float width, radius;
	ofColor boidColor;

	Boid();
	Boid(glm::vec2 i_pos, float i_width, float i_radius, ofColor i_boidColor, float i_mass = 5);
	~Boid();

	void draw();
};