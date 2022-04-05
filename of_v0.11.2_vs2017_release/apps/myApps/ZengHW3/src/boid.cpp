#include "boid.h"

Boid::Boid()
{
	boidRB = new RigidBody();
	width = 0.0f;
	radius = 0.0f;
	boidColor = ofColor(0, 0, 0);
}

Boid::Boid(glm::vec2 i_pos, float i_width, float i_radius, ofColor i_boidColor, float i_mass) :
	width(i_width), radius(i_radius), boidColor(i_boidColor) {
	boidRB = new RigidBody();
	boidRB->position = i_pos;
	boidRB->mass = i_mass;
}

Boid::~Boid() {
	delete boidRB;
}

void Boid::draw() {
	ofPushMatrix();

	ofTranslate(boidRB->position.x, boidRB->position.y);
	ofRotateRad(boidRB->orientation);
	ofSetColor(boidColor);

	// Body
	ofDrawCircle(0, 0, radius);

	// Nose
	float x1 = 0;
	float x2 = 0;
	float x3 = width;
	float y1 = -(radius);
	float y2 = (radius);
	float y3 = 0;

	ofDrawTriangle(x1, y1, x2, y2, x3, y3);

	ofPopMatrix();
}